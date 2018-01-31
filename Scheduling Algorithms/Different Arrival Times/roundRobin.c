#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Process{
    int pid;
    int initialBurst;
    int burst;
    int arrival;
    int wait;
    int turn;
    bool runStatus;
}Process;

void sort(Process *p, int n){
    Process temp;
    int i,j;
    for(i=0;i<n;++i){
        for(j=0;j<n-1-i;++j){
            if(p[j].arrival>p[j+1].arrival){
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

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
    printf("Enter burst time, arrival time for processes\n");
    for(i=0; i<n; ++i){
        printf("Process %d :",i);
        scanf("%d%d", &p[i].burst, &p[i].arrival);
        p[i].initialBurst = p[i].burst;
        p[i].pid = i;
        p[i].runStatus = true;
        p[i].wait = 0;
        p[i].turn = 0;
    }

    sort(p, n);

    float avgWait = 0.0;
    float avgTurn = 0.0;

    int processLeft = n;
    int currTime=0;
    while(processLeft){

        for(i=0;i<n;++i){
            if(!p[i].runStatus)
                continue;
            if(p[i].arrival > currTime){
                currTime++;//Fix this
                continue;
            }

            if(p[i].burst > tq){
                p[i].burst -= tq;
                for(j=0;j<n;++j)
                    if(p[j].runStatus && i!=j){
                        if(p[j].arrival<=currTime)
                            p[j].wait += tq;
                        else if(p[j].arrival < currTime + tq)
                            p[j].wait += currTime + tq - p[j].arrival;
                    }
                currTime += tq;
            }

            else{

                for(j=0;j<n;++j)
                    if(p[j].runStatus && i!=j){
                        if(p[j].arrival<=currTime)
                            p[j].wait += p[i].burst;
                        else if(p[j].arrival < currTime + p[i].burst)
                            p[j].wait += currTime + p[i].burst - p[j].arrival;
                    }
                currTime += p[i].burst;
                p[i].burst = 0;
                p[i].turn = p[i].initialBurst + p[i].wait;
                p[i].runStatus=false;
                avgTurn += p[i].turn;
                avgWait += p[i].wait;
                processLeft--;
            }
            
        }
    }

    avgWait /= n;
    avgTurn /= n;
    printf("\n========================================================================================================================");
    printf("\nProcess No.\t\tArrival Time\t\tBurst Time\t\tWait Time\t\tTurnaround Time\n");
    printf("========================================================================================================================\n");
    for(i=0;i<n;++i){
        printf("Process %d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n", p[i].pid,p[i].arrival, p[i].initialBurst,p[i].wait,p[i].turn);
    }
    printf("=========================================================================================================================\n");
    printf("\nAverage Wait Time = %f\n",avgWait);
    printf("Average Turnaround Time = %f\n",avgTurn);
    printf("======================================================================================================================\n");


    return 0;
}
