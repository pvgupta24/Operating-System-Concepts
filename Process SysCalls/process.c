#include <stdio.h> // Basic I/O
#include <unistd.h> // Various symbolic constants & types to support fcntl.h
#include <stdlib.h>
#include <signal.h>
# define LEN 100

int sigCount = 2;
// Handler for SIGINT, caused by Ctrl-C at keyboard\

pid_t child_pid = -1;

void kill_child(int sig)
{
    kill(child_pid, SIGKILL);
}

void handleSignal(int sig)
{
    printf("\nCaught signal %d\n", sig);
    --sigCount;
}

int main(){

    printf("================================\n     Process System Calls in C\n================================\n\n");


    printf("Current process ==> %d \n",getpid()); 
    printf("Parent process is ==> %d\n",getppid()); 
    printf("Real user ID of process ==> %d\n",getuid()); 
    printf("Effective user ID of process ==> %d\n",geteuid());  
    printf("Real group ID of process ==> %d\n",getuid()); 
    printf("Effective group ID of process ==> %d\n\n",geteuid()); 


    if (fork()== 0){
        printf("I am child before exit\n");
        execl("./test.out", NULL);    
                       
        exit(0);
        printf("I am child after exit\n");
    }
    else{
        if(fork()==0){
            printf("Hey\n");
        }
        else{
            printf("There\n");
            wait(NULL);
        }
        printf("I am parent. Waiting for child....\n");
        wait(NULL);
        printf("Child has terminated\n");
    }
 
 
    signal(SIGINT, handleSignal);
    while (sigCount);



    signal(SIGALRM,(void (*)(int))kill_child);
    child_pid = fork();

    if (child_pid > 0) {
    //PARENT
        alarm(7);
        wait(NULL);
    }
    else if (child_pid == 0){
        //CHILD
        while(1){
            sleep(2);
            printf("Child Process\n");
        }
    }

    char dir[100];
    printf("%s\n",getcwd(dir,LEN));
    chdir("..");
    printf("%s\n",getcwd(dir,LEN));

    return 0;
}
