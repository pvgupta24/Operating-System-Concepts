#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

typedef struct Process{
    int pid;
    int burst;
    int initialBurst;
    int wait;
    int turn;
    int priority;
    int arrival;
    bool runStatus;
}Process;

int main(){
    printf("High Priority Algorithm-Preemptive\n===============================\n");
    printf("Enter n (No. of processes)\n");
    int n;
    scanf("%d", &n);
    Process p[n];
    int i, j;
    printf("Enter burst time, arrival time, priority for processes\n");
    for(i=0; i<n; ++i){
        printf("Process %d :",i);
        scanf("%d%d%d", &p[i].burst, &p[i].arrival, &p[i].priority);
        p[i].initialBurst = p[i].burst;
        p[i].pid = i;
        p[i].runStatus = true;
        p[i].wait = 0;
        p[i].turn = 0;  
    }
    
    //sort(p,n);

    float avgWait=0.0;
    float avgTurn=0.0;
    int processLeft = n;
    int currTime=0;
    int minPriority,minPid;
    while(processLeft){
        minPriority = INT_MAX;
        minPid = -1;
        for(i=0;i<n;++i)
            if(p[i].runStatus && p[i].arrival <= currTime && p[i].priority < minPriority){
                minPriority = p[i].priority;
                minPid = p[i].pid;
            }
        
        currTime++;
        if(minPid==-1)
            continue;

        p[minPid].burst--;
        if(p[minPid].burst == 0){
            p[minPid].runStatus = false;
            p[minPid].turn = currTime - p[minPid].arrival;
            p[minPid].wait = p[minPid].turn - p[minPid].initialBurst;
            avgTurn += p[minPid].turn;
            avgWait += p[minPid].wait;
            processLeft--;            
        }        
    }
   
    avgWait /= n;
    avgTurn /= n;
    printf("\n====================================================================================================================================");
    printf("\nProcess No.\t\tPriority\tArrival Time\t\tBurst Time\t\tWait Time\t\tTurnaround Time\n");
    printf("====================================================================================================================================\n");
    for(i=0;i<n;++i){
        printf("Process %d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n", p[i].pid, p[i].priority,
         p[i].arrival, p[i].initialBurst,p[i].wait,p[i].turn);
    }
    printf("====================================================================================================================================\n");    
    printf("\nAverage Wait Time = %f\n",avgWait);
    printf("Average Turnaround Time = %f\n",avgTurn);
    printf("=================================================================================================================================\n");
    

    return 0;
}
/*
High Priority Algorithm-Preemptive
===============================
Enter n (No. of processes)
4
Enter burst time, arrival time, priority for processes
Process 0 :8 0 2
Process 1 :4 1 1
Process 2 :9 2 3
Process 3 :5 3 4

====================================================================================================================================
Process No.             Priority        Arrival Time            Burst Time              Wait Time               Turnaround Time
====================================================================================================================================
Process 0               2               0                       8                       4                       12
Process 1               1               1                       4                       0                       4
Process 2               3               2                       9                       10                      19
Process 3               4               3                       5                       18                      23
====================================================================================================================================

Average Wait Time = 8.000000
Average Turnaround Time = 14.500000
=================================================================================================================================
*/
