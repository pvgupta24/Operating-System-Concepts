#include <stdio.h> // Basic I/O
// POSIX standards to unify OS  API's 
#include <fcntl.h> // Various file flags and masks to accomapany fcntl() syscall
#include <sys/types.h> // Basic derived datatypes like clock, time, size etc.
#include <unistd.h> // Various symbolic constants & types to support fcntl.h
#include <errno.h>   // Get error codes
#include <string.h>
#include <stdbool.h>

#include <linux/cdrom.h>
#include <sys/ioctl.h>

#define toBool(x) x ? "Yes":"No"
#define LEN 100


extern int errno; 

void printError(char *path){
    printf("\n===> Error Code %d in %s\n\n", errno, path); 
    perror("\n===> The following error occurred"); 
}

void readFile(char *openPath, bool seek, int offset, int origin){
    int openFileDescripter = open(openPath, O_RDONLY);
    //success
    if(openFileDescripter > 0){
        printf("\n===> %s successfully opened for read\n",openPath);

        char readBuf[LEN];
        if(seek)
            lseek(openFileDescripter, offset, origin);
            
        int readSize = read(openFileDescripter, readBuf, LEN);
        if(readSize >= 0){
            readBuf[readSize] = '\0';
            printf("\n===> File Content :\n%s\n\n",readBuf);
        }
        else
            printError(openPath);      

        //Close the fileDescripter
        close(openFileDescripter);
    }
}

void writeFile(char *openPath){

    int openFileDescripter = open(openPath, O_WRONLY);
    //success
    if(openFileDescripter > 0){
        printf("\n===> %s successfully opened for write\n",openPath);
        char writeBuf[LEN];
        printf("Enter text to write");
        getchar();
        gets(writeBuf);
        int writeSize = write(openFileDescripter, writeBuf, strlen(writeBuf));
        if(writeSize >= 0){
            printf("\n==> Successfully written to %s\n", openPath);
        }
        else
            printError(openPath);      
            
        //Close the fileDescripter
        close(openFileDescripter);   
    }
    //fail
    else
        printError(openPath);  
}

void dupFile(char *openPath){

     int openFileDescripter = open(openPath, O_WRONLY);
    //success
    if(openFileDescripter > 0){
        printf("\n==> Using dup to use printf to redirect to %s\n", openPath);
        printf("Enter text");
        char writeBuf[LEN];
        gets(writeBuf);
        
        int stdOut;
        stdOut = dup(1);
        dup2(openFileDescripter, 1);        
        printf(writeBuf);
        dup2(stdOut, 1);
        printf("\nPrinted to file using printf\n");
        close(openFileDescripter);        
                
    }
    else
        printError(openPath);
}
void linkFile(char origPath[],char linkPath[], bool opt){
    int out;
    if(opt)
        out = link(origPath, linkPath);
    else
        out = unlink(linkPath);
    if(out == 0 ){
        printf("\n==> %s %s with %s.\n", linkPath, opt ? "linked":"unlinked", origPath);
    }
    else
        printError(linkPath);

}

int main(char *argc, int argv){

    printf("================================\n     File System Calls in C\n================================\n\n");

//=================================================================================

    char createPath[LEN];
    printf("Enter newfile path\n");
    scanf("%s",createPath);
    //createFileDescripter - stdin(0), stdOut(1) and stderr(2) 
    //S_IRWXO – read , write , execute for user,group others pipelined   
    int createFileDescripter = creat(createPath, S_IRWXU| S_IRWXG| S_IRWXO);

    //success
    if(createFileDescripter > 0){
        printf("\n===> %s successfully created\n\n",createPath);
        //Close the fileDescripter
        close(createFileDescripter);   
    }
    //fail
    else
        printError(createPath);      
    
//=================================================================================
    char openPath[LEN];
    printf("Enter Path of file to open\n");
    scanf("%s",openPath);

    writeFile(openPath);    

    readFile(openPath, false, 0, SEEK_SET);

    printf("Lseek 5 from start\n");
    readFile(openPath, true, 5, SEEK_SET);
    //dupFile(openPath);


//=================================================================================
    
    printf("Enter paths of original, linked file\n");
    char origPath[LEN], linkPath[LEN];
    scanf("%s%s",origPath, linkPath);

    linkFile(origPath, linkPath, true);
    printf("Write to original file\n");    
    writeFile(origPath);
    linkFile(origPath, linkPath, false);

//=================================================================================


    char changeAccessPath[LEN];
    printf("Enter file path to check access & change\n");
    scanf("%s",changeAccessPath);
    printf("Read access: %s\nWrite access:%s\n",
             toBool(!access(changeAccessPath, R_OK)), toBool(!access(changeAccessPath, W_OK)));

    int rP,wP;
    printf("Enter new read, write permissions (1 for yes)\n");
    scanf("%d%d",&rP,&wP);
    mode_t mode = rP ?(wP ? S_IRWXU : S_IRUSR):(wP ? S_IWUSR : S_IXUSR);
    
    if(chmod(changeAccessPath, mode) == 0){
        printf("File permissions changed successfully\n");
        printf("Read access: %s\nWrite access:%s\n",
             toBool(!access(changeAccessPath, R_OK)), toBool(!access(changeAccessPath, W_OK)));
    }
    else
        printError(changeAccessPath);


//=================================================================================
    

    char changeOwnPath[LEN];
    printf("Enter file path to change Ownership\n");
    scanf("%s",changeOwnPath);
    int changeOwnDes = open(changeOwnPath, O_WRONLY);
    struct stat fileInfo;
    stat(changeOwnDes, &fileInfo);
    printf("Original owner -> %d \nGroup -> %d\n", fileInfo.st_uid, fileInfo.st_gid);

    if (chown(changeOwnDes, 25, 0) == 0){
        stat(changeOwnDes, &fileInfo);
        printf("after chown(), owner is %d and group is %d\n",
        fileInfo.st_uid, fileInfo.st_gid);
    }
    else 
        printf("Error in chown. Permission not present\n");

//=================================================================================

    umask(S_IRUSR);
    char maskPath[LEN];
    printf("Enter newfile path\n");
    scanf("%s",maskPath);
    
    int maskFd = creat(maskPath, S_IWUSR|S_IRUSR);
    printf("Read access: %s\nWrite access:%s\n",
             toBool(!access(maskPath, R_OK)), toBool(!access(maskPath, W_OK)));



    char *dev = "/dev/dvd";
    int fd = open(dev, O_RDONLY | O_NONBLOCK);

    if(fd == -1){
        printf("Failed to open '%s'\n", dev);
    }
    else{
        printf("DVD Driver fd :%d\n", fd);
        // Eject the CD-ROM tray 
        ioctl (fd, CDROMEJECT);
        sleep(3);
        printf("Opened DVD Drive\n");
        // Close the CD-ROM tray
        ioctl (fd, CDROMCLOSETRAY);
    }
    close(fd);

    return 0;
}
