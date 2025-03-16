#include <stdio.h>

typedef struct {
    int id;      // Process ID
    int at;      // Arrival Time
    int bt;      // Burst Time (Original)
    int rt;      // Remaining Time (for preemption)
    int wt;      // Waiting Time
    int tat;     // Turnaround Time
} Process;

void roundRobin(Process p[], int n, int timeQuantum) {
    int time = 0, completed = 0;
    int queue[n], front = 0, rear = 0;
    int visited[n];
    for (int i = 0; i < n; i++) {
        p[i].rt = p[i].bt;
        p[i].wt = 0;
        p[i].tat = 0;
        visited[i] = 0;
    }

    // Find first process to arrive and add it to the queue
    int firstProcess = 0;
    for (int i = 1; i < n; i++) {
        if (p[i].at < p[firstProcess].at) {
            firstProcess = i;
        }
    }

    queue[rear++] = firstProcess;
    visited[firstProcess] = 1;

    while (completed < n) {
        int index = queue[front++];
        
        // Execute the process for at most 'timeQuantum' time
        int executionTime = (p[index].rt > timeQuantum) ? timeQuantum : p[index].rt;
        time += executionTime;
        p[index].rt -= executionTime;

        // Check if process is completed
        if (p[index].rt == 0) {
            completed++;
            p[index].tat = time - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;
        }

        // Add new processes that have arrived
        for (int i = 0; i < n; i++) {
            if (!visited[i] && p[i].at <= time && p[i].rt > 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        // Re-add process to queue if not completed
        if (p[index].rt > 0) {
            queue[rear++] = index;
        }
    }
}

// Function to print results
void print(Process p[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].wt, p[i].tat);
    }
}

int main() {
    int n, timeQuantum;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        p[i].id = i + 1;
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    roundRobin(p, n, timeQuantum);
    print(p, n);

    return 0;
}
