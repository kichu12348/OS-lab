#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define READERS 5

#define WRITERS 5

#define MUTEX 0
#define WRT 1

typedef struct {
    int sharedData;
    int readerCount;
} SharedData;

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int init_semaphores() {
    int semid = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }
    
    union semun arg;
    arg.val = 1;  
    if (semctl(semid, MUTEX, SETVAL, arg) == -1) {
        perror("semctl MUTEX");
        exit(1);
    }
    
    arg.val = 1;  // Initialize wrt to 1
    if (semctl(semid, WRT, SETVAL, arg) == -1) {
        perror("semctl WRT");
        exit(1);
    }
    
    return semid;
}

void sem_wait(int semid, int sem_num) {
    struct sembuf sb = {sem_num, -1, 0};
    if (semop(semid, &sb, 1) == -1) {
        perror("semop wait");
        exit(1);
    }
}

void sem_signal(int semid, int sem_num) {
    struct sembuf sb = {sem_num, 1, 0};
    if (semop(semid, &sb, 1) == -1) {
        perror("semop signal");
        exit(1);
    }
}

void writer(int id, SharedData* data, int semid) {
    sem_wait(semid, WRT);
    data->sharedData++;
    printf("Writer %d writes %d\n", id, data->sharedData);
    
    sem_signal(semid, WRT);
}

void reader(int id, SharedData* data, int semid) {
    sem_wait(semid, MUTEX);
    data->readerCount++;
    if (data->readerCount == 1) {
        sem_wait(semid, WRT);
    }
    sem_signal(semid, MUTEX);

    printf("Reader %d reads %d\n", id, data->sharedData);
    
    sem_wait(semid, MUTEX);
    data->readerCount--;
    if (data->readerCount == 0) {
        sem_signal(semid, WRT);
    }
    sem_signal(semid, MUTEX);
}

int main() {
    int shmid, semid, i;
    SharedData* shared_data;
    pid_t pid;
    
    shmid = shmget(IPC_PRIVATE, sizeof(SharedData), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    
    shared_data = (SharedData*)shmat(shmid, NULL, 0);
    if (shared_data == (void*)-1) {
        perror("shmat");
        exit(1);
    }
    shared_data->sharedData = 0;
    shared_data->readerCount = 0;
    semid = init_semaphores();
    for (i = 0; i < READERS; i++) {
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {  
            reader(i, shared_data, semid);
            exit(0);
        }
    }

    for (i = 0; i < WRITERS; i++) {
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        } else if (pid == 0) { 
            writer(i, shared_data, semid);
            exit(0);
        }
    }

    for (i = 0; i < READERS + WRITERS; i++) {
        wait(NULL);
    }

    if (shmdt(shared_data) == -1) {
        perror("shmdt");
    }
    
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
    }

    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl");
    }
    
    return 0;
}
