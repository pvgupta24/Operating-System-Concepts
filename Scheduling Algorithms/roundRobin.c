#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Process{
    int pid;
    int initialBurst;
    int burst;
    int wait;
    int turn;
    bool runStatus;
}Process;

int main(){
    printf("Round Robin Algorithm\n===============================\n");
    printf("Enter n (No. of processes)\n");
    int n;
    scanf("%d", &n);

    printf("Enter time quantum\n");
    int tq;
    scanf("%d", &tq);

    Process p[n];
    int i, j;
    printf("Enter burst time for processes\n");
    for(i=0; i<n; ++i){
        printf("Process %d :",i);
        scanf("%d", &p[i].burst);
        p[i].initialBurst = p[i].burst;
        p[i].pid = i;
        p[i].runStatus = true;
        p[i].wait = 0;
        p[i].turn = 0;
    }
    float avgWait = 0.0;
    float avgTurn = 0.0;

    int processLeft = n;
    int currTime=0;
    while(processLeft){
        for(i=0;i<n;++i){
            if(p[i].runStatus){
                if(p[i].burst > tq){
                    currTime += tq;                    
                    p[i].burst -= tq;
                    for(j=0;j<n;++j)
                        if(i!=j && p[j].runStatus)
                            p[j].wait += tq;
                }
                else{
                    currTime += p[i].burst;
                    for(j=0;j<n;++j)
                        if(i!=j && p[j].runStatus)
                            p[j].wait += p[i].burst;
                        
                    p[i].turn = currTime;                    
                    p[i].runStatus=false;
                    avgTurn += p[i].turn;
                    avgWait += p[i].wait;
                    processLeft--;
                }
            }
        }
    }

    avgWait /= n;
    avgTurn /= n;
    printf("\n=============================================================================================");
    printf("\nProcess No.\t\tBurst Time\t\tWait Time\t\tTurnaround Time\n");
    printf("=============================================================================================\n");

    for(i=0;i<n;++i){
        printf("Process %d\t\t%d\t\t\t%d\t\t\t%d\n", p[i].pid, p[i].initialBurst,p[i].wait,p[i].turn);
    }
    printf("=============================================================================================\n");
    printf("\nAverage Wait Time = %f\n",avgWait);
    printf("Average Turnaround Time = %f\n",avgTurn);
    printf("=============================================================================================\n");
    

    return 0;
}
