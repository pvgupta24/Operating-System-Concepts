#include<stdio.h>
#include<stdlib.h>

typedef struct Process{
    int pid;
    int burst;
    int wait;
    int turn;
}Process;

int main(){
    printf("Shortest Job First Algorithm\n===============================\n");
    printf("Enter n (No. of processes)\n");
    int n;
    scanf("%d", &n);
    Process p[n];
    int i, j;
    printf("Enter burst time for processes\n");
    for(i=0; i<n; ++i){
        printf("Process %d :",i);
        scanf("%d", &p[i].burst);
        p[i].pid = i;
    }
    Process temp;
    for(i=0;i<n;++i){
        for(j=0;j<n-1-i;++j){
            if(p[j].burst>p[j+1].burst){
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }


    p[0].wait=0;
    p[0].turn=p[0].burst;
    float avgWait=0.0;
    float avgTurn=0.0 + p[0].turn;

    for(i=1; i<n; ++i){
        p[i].wait=p[i-1].turn;
        p[i].turn=p[i-1].turn+p[i].burst;
        avgWait += p[i].wait;
        avgTurn += p[i].turn;
    }
    avgWait /= n;
    avgTurn /= n;
    printf("\n==================================================================================================");
    printf("\nProcess No.\t\tBurst Time\t\tWait Time\t\tTurnaround Time\n");
    printf("==================================================================================================\n");

    for(i=0;i<n;++i){
        printf("Process %d\t\t%d\t\t\t%d\t\t\t%d\n", p[i].pid, p[i].burst,p[i].wait,p[i].turn);
    }
    printf("==================================================================================================\n");    
    printf("\nAverage Wait Time = %f\n",avgWait);
    printf("Average Turnaround Time = %f\n",avgTurn);
    printf("==================================================================================================\n");
    

    return 0;
}
