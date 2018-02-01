#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

typedef struct Process{
    int pid;
    int burst;
    int wait;
    int turn;
    int arrival;
    bool runStatus;
}Process;

int main(){
    printf("Shortest Job First Algorithm - Non Preemptive\n===============================\n");
    printf("Enter n (No. of processes)\n");
    int n;
    scanf("%d", &n);
    Process p[n];
    int i, j;
    printf("Enter burst time, arrival time for processes\n");
    for(i=0; i<n; ++i){
        printf("Process %d : ",i);
        scanf("%d", &p[i].burst);
        scanf("%d", &p[i].arrival);
        p[i].pid = i;
        p[i].runStatus = true;
        p[i].wait = 0;
        p[i].turn = 0;  
    }
    float avgWait=0.0;
    float avgTurn=0.0;

    int processLeft = n;
    int currTime=0;
    int minBurst,minPid;
    int processOrder[n];
    while(processLeft){
        minBurst = INT_MAX;
        minPid = -1;
        for(i=0;i<n;++i)
            if(p[i].runStatus && p[i].arrival <= currTime && p[i].burst < minBurst){
                minBurst = p[i].burst;
                minPid = p[i].pid;
            }
        
        if(minPid==-1){
            currTime++;
            continue;
        }
        p[minPid].wait = currTime - p[minPid].arrival;
        p[minPid].runStatus = false;
        currTime += p[minPid].burst;
        p[minPid].turn = currTime - p[minPid].arrival;
        avgTurn += p[minPid].turn;
        avgWait += p[minPid].wait;
        processOrder[n-processLeft] = minPid;
        processLeft--;
    }
    
    avgWait /= n;
    avgTurn /= n;
    printf("\n========================================================================================================================");
    printf("\nProcess No.\t\tArrival Time\t\tBurst Time\t\tWait Time\t\tTurnaround Time\n");
    printf("========================================================================================================================\n");
    for(i=0;i<n;++i){
        printf("Process %d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n", p[processOrder[i]].pid,
         p[processOrder[i]].arrival, p[processOrder[i]].burst,p[processOrder[i]].wait,p[processOrder[i]].turn);
    }
    printf("=========================================================================================================================\n");    
    printf("\nAverage Wait Time = %f\n",avgWait);
    printf("Average Turnaround Time = %f\n",avgTurn);
    printf("======================================================================================================================\n");
    

    return 0;
}

/*

Shortest Job First Algorithm - Non Preemptive
===============================
Enter n (No. of processes)
4
Enter burst time, arrival time for processes
Process 0 : 7 0
Process 1 : 4 2
Process 2 : 1 4
Process 3 : 4 5

========================================================================================================================
Process No.             Arrival Time            Burst Time              Wait Time               Turnaround Time
========================================================================================================================
Process 0               0                       7                       0                       7
Process 2               4                       1                       3                       4
Process 1               2                       4                       6                       10
Process 3               5                       4                       7                       11
=========================================================================================================================

Average Wait Time = 4.000000
Average Turnaround Time = 8.000000
======================================================================================================================


*/
