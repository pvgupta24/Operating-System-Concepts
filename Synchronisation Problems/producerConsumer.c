#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

int bufferSize;
sem_t mutex, fullSlots, emptySlots;
int front = -1, rear = -1;
int *queue;
int items=0;
void push(){
    rear = (rear+1)%bufferSize;
    if(front == -1)
        front++;
    items++;
    printf("Pushing to %d\n",rear);
    //Push to queue here from produce

}
void pop(){
    printf("Popping from %d\n",front);
    front = (front+1)%bufferSize;   
    items--; 
    if(!items)
        front=rear=-1;
    //Consume here
}
void *produceFun(){
    printf("Producer Thread started\n");    
    do{
        sem_wait(&emptySlots);
        // sem_wait(&mutex);

        //CS
        sleep(1);
        push();
        sem_post(&fullSlots);
        // sem_post(&mutex);
        

    }while(true);
}

void *consumeFun(){
    printf("Consumer Thread started\n");
    
    do{
        sem_wait(&fullSlots);
        // sem_wait(&mutex);

        //CS
        sleep(1);
        pop();
        sem_post(&emptySlots);
        // sem_post(&mutex);
        
    }while(true);
}
int main(){
    printf("Producer Consumer Problem\n");
    printf("Enter buffer size\n====================\n");
    scanf("%d", &bufferSize);
    queue = (int *)malloc(bufferSize * sizeof(int));
    pthread_t produceThread, consumeThread;
    //Share mutex between all threads of the process and with inital value 1
    sem_init(&mutex, 0, 1);
    sem_init(&fullSlots, 0, 0);//No full
    sem_init(&emptySlots, 0, bufferSize);//All empty initially

    pthread_create(&produceThread, NULL, produceFun, NULL); 
    pthread_create(&consumeThread, NULL, consumeFun, NULL);

    pthread_join(produceThread, NULL);
    pthread_join(consumeThread, NULL);      
    return 0;
}
