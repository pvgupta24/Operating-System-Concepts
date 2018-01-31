#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#define loop(i,n) for(i=0; i<n; ++i)

#define N 5

sem_t chops[N];
pthread_t philosophers[N];
void *eat(void *x){
    int i = (int)x;
    int j = (i+1) % N;
    // if(i==N)
    //     j = N-1;
    printf("Phlosopher %d is thinking\n", i);
    sem_wait(chops + i);
    
    //sleep(3);//This shows deadlock
    printf("Phlosopher %d picked up chopstick %d\n", i, i);
    sem_wait(chops + j);
    printf("Phlosopher %d picked up chopstick %d\n", i, j);
    //CS here
    {
    printf("Phlosopher %d is eating\n", i);
    sleep(1);
    }
    printf("Phlosopher %d dropped chopstick %d\n", i, i);
    sem_post(chops + i);
    printf("Phlosopher %d dropped chopstick %d\n", i, j);    
    sem_post(chops + j);

    printf("Philosopher %d completed eating!!\n", i);
}
int main(){
    printf("Dining Philosophers Problem %d people\n", N);
    int i;
    loop(i,N)
        sem_init(chops + i, 0, 1);//All chops available at start
    loop(i,N)
        pthread_create(philosophers + i, NULL, eat, (void *)i);//Launch Threads 
    loop(i,N)
        pthread_join(philosophers[i], NULL);//Wait for all threads of process before process termination
    return 0;
}
