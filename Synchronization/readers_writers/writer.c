#include <sys/ipc.h>
#include<sys/shm.h>
#include <string.h>
#include<stdio.h>

void main(){
    // create a unique key using ftok
    key_t key = ftok("kichu",69);
    
    //CREATE A SHARED Memory segment with word length 1024 bytes and 0666 giving read write permission
    int shmid = shmget(key,1024,0666|IPC_CREAT);

    //attach this shared memeory to this proccess
    char* str = (char *)shmat(shmid,(void *)0,0);
    printf("write data :");
    gets(str);
    printf("Data written in memory : %s\n", str);

    //detach from the memory 
    shmdt(str);
}