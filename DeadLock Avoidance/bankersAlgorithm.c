#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#define loop(i,n) for(i=0; i<n; ++i)
#define inp(x) scanf("%d",&x)
#define PCOUNT 5
#define RCOUNT 3

int processCount , resources , i, j, k;
int available[RCOUNT];
int maxNeed[PCOUNT][RCOUNT];
int need[PCOUNT][RCOUNT];
int allocated[PCOUNT][RCOUNT];
int processesLeft = PCOUNT;
bool completed[PCOUNT];        
int order[PCOUNT];
int k=0;
bool satisfies;
void unsafe(){
    printf("\n\n=============Unsafe============\n\n");
    exit(0);
}
void safety(){
    printf("\nAvailable Resources\n");
    loop(j, RCOUNT)
        printf("R%d = %d\t", j, available[j]);    
    
    k = 0;
    //Till all processes are completed
    while(processesLeft){
        //Find a process whose req can be met
        loop(i, PCOUNT){
            if(completed[i])
                continue;

            satisfies = true;
            //Check individual resources
            loop(j, RCOUNT){
                if(available[j] < need[i][j])
                    satisfies = false;
                }
            if(satisfies){
                {
                    //Run ith program in this block
                    printf("\nRunning P%d\n",i);
                }
                order[k++] = i;
                
                completed[i]=true;
                printf("Available Resources : \n");
                loop(j, RCOUNT){
                    available[j] += allocated[i][j];
                    printf("R%d = %d\t", j, available[j]);    
                }
                processesLeft--;
                continue;
            }
            if(i == PCOUNT -1){
                //Could not complete this.So unsafe
                unsafe();
            }
        }
    }

    printf("\n\n=============Safe============\n\nPossible Order");
    loop(i, PCOUNT)
        printf("P%d\t", order[i]);
    printf("\n");
}
int main(){
    system("clear");

    // printf("Enter no. of processes\n");
    // scanf("%d", &processCount);

    // printf("Enter no. of resource types\n");
    // scanf("%d", &resources);

    printf("Enter available resource amount \n");
    loop(i, RCOUNT){
        printf("R%d : ", i);
        inp(available[i]);
    }

    printf("\n\nEnter max requirement and allocated resources :\n");
    loop(i, PCOUNT){
        completed[i] = false;
        loop(j, RCOUNT){
            printf("P%d R%d\n", i, j);
            inp(maxNeed[i][j]);
            inp(allocated[i][j]);
            need[i][j] = maxNeed[i][j] - allocated[i][j];
            available[j] -= allocated[i][j];

        }
    }

    printf("Enter process requesting resources\n");
    int p;
    inp(p);
    int req[RCOUNT];
    printf("Enter request amount of resources \n");    
    loop(i, RCOUNT){
        printf("R%d : ", i);
        inp(req[i]);
        available[i] -= req[i];
        need[p][i] -= req[i];
        allocated[p][i] += req[i];
        // if(available[i]<0)
        //     unsafe();
    }
    safety();
    return 0;
}
/*
10
5
7

7 0
5 1
3 0
3 2
2 0
2 0
9 3
0 0
2 2
2 2
2 1
2 1
4 0
3 0
3 2

2 3 3 0

1 1 0 2
*/
