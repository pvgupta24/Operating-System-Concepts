#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define inp(x) scanf("%d",&x)
#define loop(i,n) for(i=0;i<n;++i)
#define N 1000


int mm_size, free_space, n, partition_count, process_count, pid, partid;
int i,j,k;
int parts_allocated=0;

typedef struct Process{
    int pid;
    int req;
    bool allocated;
    int partid;
    int ext_frag;
    int int_frag;
}Process;

typedef struct Partition{
    int partid;
    int size;
    bool allocated; 
    int pid;
}Partition;    

void println(){
    printf("======================================================\n");
}
int alloc(int pid, Partition part[], Process pro[]){
    loop(j,partition_count){
        if(part[j].allocated==false && pro[i].req<=part[j].size){
            //pro i in jth partition
            part[j].allocated=true;
            pro[i].int_frag= part[j].size - pro[i].req;
            part[j].pid = pro[i].pid;
            pro[i].partid = j;
            free_space -= part[j].size;
            printf("%d\t\t%d\t\tInternal = %d\n",i, j, pro[i].int_frag);
            ++parts_allocated;
            return 0;                
        }
    }
    //Could not allocate
    pro[i].ext_frag = free_space;
    if(free_space >= pro[i].req)
        printf("%d\t\t-\t\tExternal = %d\n",i, pro[i].ext_frag);
    else
        printf("%d\t\t-\t\tInsufficient Memory\n",i);
       
}
void first_fit(Partition part[], Process pro[]){
    println();
    loop(i,process_count){
        alloc(i, part, pro);
    }
}
void dealloc(int pid, Process pro[], Partition part[]){
    parts_allocated--;
    partid = pro[pid].partid;
    printf("Freeing Partition %d\n",partid);
    pro[pid].allocated = false;
    if(partid>=0 && partid<partition_count)
    part[partid].allocated = false;
    printf("P%d deallocated.\n",pid);
}
void initialize_pro(int i, Process pro[]){
    printf("Process %d : ", i);
    inp(pro[i].req);
    pro[i].pid = i;
    pro[i].partid = -1;
    pro[i].allocated = false;        
    pro[i].int_frag = -1;
    pro[i].ext_frag = -1;
}
int main(){
    system("clear");
    printf("MFT (First Fit)\n");
    println();
    printf("Enter Main memory size\n");
    inp(mm_size);

    printf("Enter no. of partitions\n");
    inp(partition_count);
    Partition part[partition_count];
    printf("Enter size of each partitions\n");
    free_space = 0;

    loop(i,partition_count){
        printf("Part %d : ",i);
        inp(part[i].size);
        part[i].allocated = false;
        part[i].partid = i;
        part[i].pid = -1;
        free_space += part[i].size;
    }
    println();
    if(free_space != mm_size){
        printf("Sum of partitions does not match MM size\n");
        return -1;
    }

    printf("Enter no. of processes\n");
    inp(process_count);
    printf("Enter memory reqd for \n");
    Process pro[N];
    loop(i,process_count){
        initialize_pro(i, pro);
    }

    println();
    printf("\nPID\t\tPartID\t\tIssues/Fragments\n");
    first_fit(part, pro);
    
    again:
    printf("\nPress 1 to add more : ");
    inp(i);
    println();
    if(i!=1)
        return 0;
    if(parts_allocated == partition_count){
        printf("Partitions Full\nEnter PID to remove from memory : ");
        inp(pid);
        dealloc(pid, pro, part);
    }
    i = process_count++;
    printf("Enter size\n");
    initialize_pro(i,pro);
    alloc(i, part, pro);
    goto again;
    return 0;
}
/*
1450
7
100 250 400 300 200 100 100
6
50 250 150 300 400 200
*/
