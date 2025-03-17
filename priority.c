#include<stdio.h>

/*
priority scheduling pre-emptive
1. The process with the smallest priority number is selected for execution.
2. If two processes have the same priority number, the process that arrived first is selected.
3. The process that arrives first, gets added to the queue first, and runs first.
4. The process that arrives next, gets added to the queue next, and runs next.
5. The process that arrives last, gets added to the queue last, and runs last.
 this is pre-emptive

i will use an array of structs called process
each struct will have an id, arrival time, burst time, waiting time,
turnaround time and completed default 0 ie false,
priority,
then i will calculate the waiting time and turnaround time for each process
*/


// struct to hold process information
typedef struct
{
    int id;  // process id
    int at;  // arrival time
    int bt;  // burst time
    int rt; //temp burst time
    int wt;  // waiting time
    int tat; // turnaround time
    int completed; // completed flag
    int priority; // priority
} Process;




// function to calculate waiting time and turnaround time
void priorityScheduling(Process p[], int n) {
    int time= 0;
    int completed = 0;

    while(completed<n){
        int highest = 100;
        int idx=-1;
        for(int i=0;i<n;i++){
            if(
                p[i].at<=time &&
                !p[i].completed &&
                p[i].priority<highest
            ){
                highest=p[i].priority;
                idx=i;
            }
        }

        if(idx==-1){
            time++;
            continue;
        }

        p[idx].rt--;
        time++;

        if(p[idx].rt==0){
            p[idx].tat = time - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].completed = 1;
            completed++;
        }
    }
}

// function to print the waiting time and turnaround time for each process

void print(Process p[], int n)
{
    printf("Process ID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].priority, p[i].wt, p[i].tat);
    }
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter the arrival time, burst time and priority for process %d: ", i + 1);
        p[i].id = i + 1;
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].completed = 0;
        p[i].wt = 0;
        p[i].tat = 0;
        p[i].rt = p[i].bt;
    }
    priorityScheduling(p, n);
    print(p, n);
    return 0;
}