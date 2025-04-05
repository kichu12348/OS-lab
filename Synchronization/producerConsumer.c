#include<stdio.h>
#include<pthread.h>

#define BUFFER_SIZE 10
#define NUM_ITEMS 5

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

/*
ALGORITHM:
1.Start.
2. Define the buffer size and number of items.
3. Define the buffer, in, out, and count variables.
4. Define the Semaphore structure.
5. Define the wait and Signal functions.
6. Define the producer function.
7. Define the consumer function.
8. In the producer function, iterate over the number of items to be produced.
9. Wait for the empty semaphore.
10. Wait for the mutex semaphore.
11. Produce an item and print the message.
12. Update the buffer, in, and count variables.
13. Signal the mutex and full semaphores.
14. In the consumer function, iterate over the number of items to be consumed.
15. Wait for the full semaphore.
16. Wait for the mutex semaphore.
17. Consume an item and print the message.
18. Update the buffer, out, and count variables.
19. Signal the mutex and empty semaphores.
20. Create the producer and consumer threads.
21. Join the producer and consumer threads.
22. End.
*/
