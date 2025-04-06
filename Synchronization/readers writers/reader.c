#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>

void main(){
    
    //generate key using same
    key_t key = ftok("kichu",69);

    //get shared memeory id
    int shmid = shmget(key,1024,0666|IPC_CREAT);

    //ATTACH TO SHARED MEMORY
    char* str = (char *)shmat(shmid,(void *)0,0);

    printf("Data read is: %s\n",str);

    shmdt(str); // 
    shmctl(shmid,IPC_RMID,NULL); // DELETES THE DATA
}