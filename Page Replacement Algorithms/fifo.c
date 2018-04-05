#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define loop(i,n) for(i=0;i<n;++i)
#define inp(x) scanf("%d", &x)

void println(){
    printf("==========================================================================\n");
}
//====================================================================
int frameCount, req, i, lastIndex = 0, faultCount = 0;
bool fault;

// Search for page
bool search(int table[], int req){
    loop(i,frameCount){
        if(table[i] == req)
            return true;
    }
    return false;
}

void initialize(int table[]){
    loop(i,frameCount)
        table[i] = -1;
}
void printTable(int table[], bool fault){
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
    printf("Fifo Page Replacement\n");
    println();

    printf("Enter frame Count : ");
    inp(frameCount);
    int table[frameCount];
    initialize(table);

    while(true){
        printf("Enter page request (-1 to exit) : ");
        inp(req);
        if(req < 0)
            break;
        fault = false;
        if(!search(table, req)){
            table[lastIndex] = req;
            lastIndex = (lastIndex+1) % frameCount;
            faultCount ++;
            fault = true;
        }
        printTable(table, fault);
    }

    printf("Total faults = %d\n", faultCount);
    println();
    return 0;
}
