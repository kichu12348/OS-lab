#include<stdio.h>
#include<pthread.h>

// Define the buffer size
#define BUFFER_SIZE 10
#define NUM_ITEMS 5


// Define the buffer
int buffer[BUFFER_SIZE];
int in = 0,
    out = 0,
    count = 0;

typedef struct {
    int value;
} Semaphore;


Semaphore mutex = {1};
Semaphore empty = {BUFFER_SIZE};
Semaphore full = {0};

void wait(Semaphore *s) {
    while (s->value <= 0);
    s->value--;
}

void Signal(Semaphore *s) {
    s->value++;
}

void *producer(void *arg) {
    for(int i=0;i<NUM_ITEMS;i++){
        wait(&empty);
        wait(&mutex);
        buffer[in]=i;
        printf("Produced item %d\n",buffer[in]);
        in = (in+1)%BUFFER_SIZE;
        //count
        count++;
        Signal(&mutex);
        Signal(&full);
    }
    pthread_exit(0);
}

void *consumer(void *arg) {
    for(int i=0;i<NUM_ITEMS;i++){
        wait(&full);
        wait(&mutex);
        int item = buffer[out];
        printf("Consumed item %d\n",item);
        out = (out+1)%BUFFER_SIZE;
        count--;
        Signal(&mutex);
        Signal(&empty);
    }
    pthread_exit(0);
}

void main (){
    pthread_t prod,consum;
    pthread_create(&prod,NULL,producer,NULL);
    pthread_create(&consum,NULL,consumer,NULL);
    pthread_join(prod,NULL);
    pthread_join(consum,NULL);
}
