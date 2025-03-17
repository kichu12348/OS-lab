#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
/*
Readers writers problem

Readers writers problem is a synchronization problem
 where multiple
 readers and writers are accessing a shared resource. 
The problem is to provide a solution such that no reader is 
kept waiting if the resource is free and no writer is kept waiting if the resource is free.


The problem can be divided into two subproblems:
Readers writers problem with no reader writer priority
Readers writers problem with reader writer priority
In this article, we will discuss the first subproblem.
Readers writers problem with no reader writer priority

In this problem, we have to provide a solution such that no reader is kept waiting if the resource is 
free and no writer is kept waiting if the resource is free.
*/

// Number of readers
#define READERS 5

// Number of writers
#define WRITERS 5

// Number of times a reader reads
#define READ_COUNT 5

// Number of times a writer writes
#define WRITE_COUNT 5

// Shared data
int sharedData = 0;

// Reader count
int readerCount = 0;

typedef struct{
    int val;
} Semaphore;

Semaphore mutex={1}, wrt={1};


void wait(Semaphore *s){
    while(s->val<=0); // starvation of the cpu not at all ideal
    s->val--;
}

void Signal(Semaphore *s){
    s->val++;
}


/*
writer function

This function writes the shared data. It first acquires the write lock.
It then writes the shared data.
It then releases the write lock.

*/

void *writer(void *arg){
        wait(&wrt);
        sharedData++;
        printf("Writer %d writes %d\n",*((int *)arg),sharedData);
        Signal(&wrt);
}


/*
reader function

This function reads the shared data. It first acquires the mutex lock.
It then increments the reader count. If the reader count is 1, it acquires the write lock.
It then releases the mutex lock.
It reads the shared data.
It then acquires the mutex lock.
It decrements the reader count. If the reader count is 0, it releases the write lock.
It then releases the mutex lock.
*/
void *reader(void *arg){
        wait(&mutex);
        readerCount++;
        if(readerCount==1){
            wait(&wrt);
        }
        Signal(&mutex);
        printf("Reader %d reads %d\n",*((int *)arg),sharedData);
        wait(&mutex);
        readerCount--;
        // Last reader
        if(readerCount==0){
            Signal(&wrt);
        }
        Signal(&mutex);
}


int main(){
    pthread_t readers[READERS],writers[WRITERS];
    int i;
    for(i=0;i<READERS;i++){
        int *arg = (int *)malloc(sizeof(int *));
        *arg = i;
        pthread_create(&readers[i],NULL,reader,arg);
    }
    for(i=0;i<WRITERS;i++){
        int *arg = (int *)malloc(sizeof(int *));
        *arg = i;
        pthread_create(&writers[i],NULL,writer,arg);
    }
    for(i=0;i<READERS;i++){
        pthread_join(readers[i],NULL);
    }
    for(i=0;i<WRITERS;i++){
        pthread_join(writers[i],NULL);
    }
    return 0;
}
