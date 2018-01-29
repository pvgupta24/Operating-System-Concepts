#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int bufferSize;
//Binary mutual exclusion semaphore
int mutex=1;
int fullSlots=0, emptySlots;
int x=0;

void wait(int *semaphore){
    (*semaphore)--;
}

void signal(int *semaphore){
    (*semaphore)++;
}
void produce(){
    wait(&mutex);
    //Fill a slot
    signal(&fullSlots);
    //Decrease empty slot
    wait(&emptySlots);
    x++;
    printf("Produced P%d\n",x);
    //Increase mutex
    signal(&mutex);
}

void consume(){
    wait(&mutex);
    //Empty an slot
    wait(&fullSlots);
    //Make an empty slot
    signal(&emptySlots);
    printf("Consumed P%d\n",x);
    x--;    
    //Increase mutex
    signal(&mutex);
}

int main(){
    printf("Producer Consumer Problem");
    printf("\nEnter buffer size\n====================\n");
    scanf("%d", &emptySlots);

    while(true){
        int choice;
        printf("Enter choice\n1. Produce\n2. Consume\n3. Exit\n");
        scanf("%d", &choice);
        switch(choice){
            case 1:                
                if(mutex==1 && emptySlots!=0)
                    produce();
                else
                    printf("Buffer Full. Cannot produce\n\n");
                break;

            case 2:
                if(mutex==1 && fullSlots!=0)
                    consume();
                else
                    printf("Buffer empty. Cannot consume\n\n");
                break;
            default: return 0;
        }
    }
    return 0;
}
