#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 5

//writeBlock blocks multiple writers
sem_t mutex, writeBlock;
int readCount=0, writeCount=0;

void *readFun(void *arg){
    int i = ((int)arg);
    //Block other read
    sem_wait(&mutex);
    ++readCount;
    //If reading block write
    if(readCount==1)
        sem_wait(&writeBlock);
    sem_post(&mutex);
    printf("Read - Thread %d : Data %d\n",i, writeCount);

    //CS denote by sleep
    sleep(1);
    sem_wait(&mutex);
    readCount--;
    //If no reads allow write operation
    if(readCount==0)
        sem_post(&writeBlock);
    sem_post(&mutex);
}

void *writeFun(void *arg){
    int i = ((int) arg);\
    //Decrements writeBlock semaphore to block other writes
    sem_wait(&writeBlock);//writeBlock
    ++writeCount;
    printf("Write - Thread %d : Data %d\n", i, writeCount);

    //CS denote by sleep
    sleep(1);

    //End CS Code, free for other threads 
    sem_post(&writeBlock);
}

int main(){
    printf("Reader-Writer Problem\n=============================\n");
    pthread_t readTid[THREAD_COUNT], writeTid[THREAD_COUNT];

    //Share mutex between all threads of the process and with inital value 1
    sem_init(&mutex, 0, 1);
    sem_init(&writeBlock, 0, 1);
    int i;
    for(i=0; i < THREAD_COUNT; ++i){
        //Create thread with given buffer ptr, with NULL attribute objects, run custom func with given args
        pthread_create(writeTid + i, NULL, writeFun, (void *) i); 
        pthread_create(readTid + i, NULL, readFun, (void *) i);
    }

    for(i=0; i < THREAD_COUNT; ++i){
        //Calling thread waits for completion of called thread i.e writeBlocks 
        pthread_join(readTid[i], NULL);
        pthread_join(writeTid[i], NULL);        
    }

    return 0;
}
