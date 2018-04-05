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
    printf("==========================================================================================\n");
}
//====================================================================
int frameCount, req, i, j, faultCount = 0, reqCount, pos = -1;
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

int getPos(int table[], int req[], int currIndex){
    int k, index = 0;
    int maxTime = -2, tim;
    loop(i, frameCount){
        // Traverse through table contents
        if(table[i] == -1)
            return i; // empty

        tim = 0;
        for(k=currIndex+1; k<reqCount;++k){
            if(table[i] == req[k]){
                if(DEBUG) printf("Found\n");
                // tim = k;
                break;
            }
            else{
                if(DEBUG) printf("Time = %d\n", tim);
                tim++;
            }
        }
        if(tim > maxTime){
            maxTime = tim;
            index = i;
        }
    }
    return index;
}

void initialize(int table[]){
    loop(i,frameCount)
        table[i] = -1;
}
void printTable(int table[], bool fault, int req){
    printf("Requested %d\n", req);
    println();
    printf("Table : |");
    loop(i,frameCount)
        table[i] < 0 ? printf("\t--\t|"):printf("\t%d\t|",table[i]);
    if(fault)
        printf("\tPage Fault");
   
    printf("\n");
    println();
}

int main(){
	system("clear");
    println();
    printf("Optimal Page Replacement\n");
    println();

    printf("Enter frame Count : ");
    inp(frameCount);

    printf("Enter page Count : ");
    inp(reqCount);

    int req[reqCount];
    
    int table[frameCount];
    // int useTime[frameCount];// Low value => Closer the usage in future
    initialize(table);

    again:
    loop(j, reqCount){
        printf("Enter page request %d :", j);
        inp(req[j]);
        if(req[j] < 0){
            printf("Negative not allowed\n");
            goto again;
        }
    }
    
    loop(j, reqCount){  
        fault = false;
        if(!search(table, req[j])){
            //Get faraway one and replace
            pos = getPos(table, req, j);
            if(DEBUG)
                printf("Pos = %d\n",pos);
            table[pos] = req[j];
            faultCount ++;
            fault = true;
        }
        
        printTable(table, fault, req[j]);
    }
    // printTable(table, fault);    
    printf("Total faults = %d\n", faultCount);
    println();
    return 0;
}
