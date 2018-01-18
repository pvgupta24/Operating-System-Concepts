#include<stdio.h>
#include<stdlib.h>

typedef struct Process{
    int pid;
    int burst;
    int arrival;
    int wait;
    int turn;
}Process;

int main(){
    printf("First come First serve Algorithm\n===============================\n");
    printf("Enter n (No. of processes)\n");
    int n;
    scanf("%d", &n);
    int i;

    int burst[n];
    Process p[n];
    printf("Enter burst time for processes\n");
    for(i=0; i<n; ++i){
        printf("Process %d : ",i);
        // printf("Enter burst time\n");
        scanf("%d", &p[i].burst);
        /*printf("Enter arrival time\n");
        scanf("%d", p[i].arrival);*/
        p[i].pid = i;
    }

    int wait[n],turn[n];
    p[0].wait=0;
    p[0].turn=p[0].burst;


    float avgWait = 0.0;
    float avgTurn = 0.0 + p[0].turn;

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
        printf("Process %d\t\t%d\t\t\t%d\t\t\t%d\n", i, p[i].burst,p[i].wait,p[i].turn);
    }
    printf("==================================================================================================\n");    
    printf("\nAverage Wait Time = %f\n",avgWait);
    printf("Average Turnaround Time = %f\n",avgTurn);
    printf("==================================================================================================\n");
    
    return 0;
}
