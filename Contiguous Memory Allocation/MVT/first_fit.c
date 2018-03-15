#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define inp(x) scanf("%d",&x)
#define loop(i,n) for(i=0;i<n;++i)
#define N 1000


int mm_size, slot_count = 1, pid = -1, pos=0, free_mem, pid_del;
int i, j, k;
int parts_allocated=0;

typedef struct Process{
    int pid;
    int req;
    bool allocated;
}Process;

typedef struct Slots{
    int pid;
    int start;
    int end;
    int size;
    bool empty;
}Slots;
Slots slots[N];
Process pro[N];

void println(){
    printf("======================================================\n");
}

void mem_table(){
    println();
    printf("Memory Contents\n");
    println();
    printf("Size\t\tContents\t\tRange\n");
    loop(i,slot_count){
        printf("%d\t\t",slots[i].size);
        (slots[i].pid==-1) ? printf("-\t\t\t%d-%d\n",slots[i].start,slots[i].end) : 
        printf("P%d\t\t\t%d-%d\n",slots[i].pid,slots[i].start,slots[i].end);
    
    }
    println();
}
int find_slot(){
    for(i=0; i<slot_count; i++)
		if(slots[i].pid==-1 && slots[i].size >= pro[pid].req)
			return i;

	return -1;
}
void alloc(int pos)
{
    //Move everything to right to create a slot at pos
	for(i=slot_count; i>pos; i--)
		slots[i] = slots[i-1];

	slots[pos].pid = pid;
	slots[pos].size = pro[pid].req;
	pro[pid].allocated = true;
    slots[pos].empty == false;
    slots[pos].start == (pos==0)?0:slots[pos+1].end;
    slots[pos].end= slots[pos].start+ slots[pos].size;
    free_mem -= pro[pid].req;
    //Decrease req from the chosen chunk
	slots[pos+1].size -= pro[pid].req;
	slots[pos+1].start += pro[pid].req;
	slot_count++;
}

int dealloc_merge(int slot_del)
{
    slots[slot_del].empty=true;
    slots[slot_del].pid=-1;
    free_mem += slots[slot_del].size;
    //If right slot free merge
	if(slot_del!=slot_count-1 && slots[slot_del+1].pid==-1)
	{
		slots[slot_del].size += slots[slot_del+1].size;
		for(i=slot_del+1; i<slot_count-1; i++)
			slots[i] = slots[i+1];
		slot_count--;
	}
   //If left slot free merge
	if(slot_del>0 && slots[slot_del-1].pid==-1)
	{
		slots[slot_del-1].size += slots[slot_del].size;
		for(i=slot_del; i<slot_count-1; i++)
			slots[i] = slots[i+1];
		slot_count--;
	}
}
int main(){
    system("clear");
    printf("MVT - First Fit\n");
    println();
    printf("Enter Main memory size\n");
    inp(mm_size);
    free_mem = mm_size;
    //Initially One free chunk of mem
    slots[0].pid = -1;
    slots[0].size = mm_size;
    slots[0].start = 0;
    slots[0].end = mm_size;
    //slots[0].empty = true;
    mem_table();
    again:
    printf("1. Allocate\t\t2. Deallocate\n");
    inp(k);
    if(k==1){
        pid++;
        pro[pid].pid = pid;
        pro[pid].allocated = false;
        printf("Mem for P%d : ", pid);
        inp(pro[pid].req);
        pos = find_slot();
        //printf("Slot %d found for P%d\n",pos,pid);
        if(pos == -1){
            if(free_mem < pro[pid].req)
                printf("Insufficient Memory\n");
            else
                printf("Cannot Allocate\nExternal Fragment = %d\n",free_mem);
        }
        else
            alloc(pos);//At given slot position
    }
    else if(k==2){
        printf("Enter PID to remove : ");
        inp(pid_del);

        loop(i, slot_count)
            if(slots[i].pid == pid_del){
                dealloc_merge(i);
                break;
            }
    }
    else
        return 0;
    mem_table();
    goto again;
    return 0;
}
/*
1000

1 250
1 50
1 300
1 250 
1 100
2 1
1 25

======================================================
Memory Contents
======================================================
Size            Contents                Range
250             P0                      0-250
50              -                       250-300
300             P2                      300-600
250             P3                      600-850
100             P4                      850-950
50              -                       950-1000
======================================================
*/
