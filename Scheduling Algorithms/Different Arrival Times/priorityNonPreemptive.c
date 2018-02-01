#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

typedef struct Process{
    int pid;
    int burst;
    int wait;
    int turn;
    int priority;
    int arrival;
    bool runStatus;
}Process;

int main(){
    printf("High Priority Algorithm - Non pre emptive\n===============================\n");
    printf("Enter n (No. of processes)\n");
    int n;
    scanf("%d", &n);
    Process p[n];
    int i, j;
    printf("Enter burst time, arrival time, priority for processes\n");
    for(i=0; i<n; ++i){
        printf("Process %d :",i);
        scanf("%d%d%d", &p[i].burst, &p[i].arrival, &p[i].priority);
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
    int processOrder[n];
    while(processLeft){
        minPriority = INT_MAX;
        minPid = -1;
        for(i=0;i<n;++i)
            if(p[i].runStatus && p[i].arrival <= currTime && p[i].priority < minPriority){
                minPriority = p[i].priority;
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
    printf("\n====================================================================================================================================");
    printf("\nProcess No.\t\tPriority\tArrival Time\t\tBurst Time\t\tWait Time\t\tTurnaround Time\n");
    printf("====================================================================================================================================\n");
    for(i=0;i<n;++i){
        printf("Process %d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n", p[processOrder[i]].pid, p[processOrder[i]].priority,
         p[processOrder[i]].arrival, p[processOrder[i]].burst,p[processOrder[i]].wait,p[processOrder[i]].turn);
    }
    printf("====================================================================================================================================\n");    
    printf("\nAverage Wait Time = %f\n",avgWait);
    printf("Average Turnaround Time = %f\n",avgTurn);
    printf("=================================================================================================================================\n");
    


    return 0;
}
/*

High Priority Algorithm - Non pre emptive
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
Process 0               2               0                       8                       0                       8
Process 1               1               1                       4                       7                       11
Process 2               3               2                       9                       10                      19
Process 3               4               3                       5                       18                      23
====================================================================================================================================

Average Wait Time = 8.750000
Average Turnaround Time = 15.250000
=================================================================================================================================
*/
