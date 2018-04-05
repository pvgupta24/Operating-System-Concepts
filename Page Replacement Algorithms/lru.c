#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define loop(i,n) for(i=0;i<n;++i)
#define inp(x) scanf("%d", &x)
#define INF 1e9
// #define DEBUG true
#define DEBUG false

void println(){
    printf("==========================================================================\n");
}
//====================================================================
int frameCount, req, i, faultCount = 0, pos = -1;
bool fault;

// Search for page
bool search(int table[], int req){
    loop(i,frameCount){
        if(table[i] == req){
            pos = i;
            return true;
        }
    }
    return false;
}

int getRecent(int table[], int useTime[], int req){
    int max = INT_MIN;
    int index = -1;
    loop(i, frameCount){
        if(max < useTime[i]){
            max = useTime[i];
            index = i;
        }
        useTime[i]++;
    }
    // useTime[pos] = 0;
    // table[pos] = req;
    return index;
}

void initialize(int table[], int useTime[]){
    loop(i,frameCount){
        table[i] = -1;
        useTime[i] = INF;//high value => not changed recently
    }
}
void printTable(int table[],int useTime[], bool fault){
    println();
    printf("Table : |");
    loop(i,frameCount)
        table[i] < 0 ? printf("\t--\t|"):printf("\t%d\t|",table[i]);
    if(fault)
        printf("\tPage Fault");
    if(DEBUG){
        printf("\nUse Time : |");        
        loop(i,frameCount)
            printf("\t%d\t|",useTime[i]);
        printf("Less => More Recent\n");
    }
    
    printf("\n");
    println();
}

int main(){
	system("clear");
    println();
    printf("Least Recently Used Page Replacement\n");
    println();

    printf("Enter frame Count : ");
    inp(frameCount);

    int table[frameCount];
    int useTime[frameCount];// Low value => More recent the usage
    initialize(table, useTime);

    while(true){
        printf("Enter page request (-1 to exit) : ");
        inp(req);
        if(req < 0)
            break;
        fault = false;
        if(search(table, req)){
            //found => Update useTime
            getRecent(table, useTime, req);//Update others
            useTime[pos] = 0;
            
        }
        else{
            pos = getRecent(table, useTime, req);
            useTime[pos] = 0;
            table[pos] = req;
            faultCount ++;
            fault = true;
        }
        printTable(table, useTime, fault);
    }

    printf("Total faults = %d\n", faultCount);
    println();
    return 0;
}
