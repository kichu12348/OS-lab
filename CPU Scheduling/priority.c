#include<stdio.h>

/*
priority scheduling non preemptive algorithm
1. input the number of processes
2. input the arrival time, burst time and priority for each process
3. find the process with the highest priority or lowest arrival time
4. calculate the waiting time and turnaround time for each process
5. print the waiting time and turnaround time for each process
6. repeat steps 3 to 5 until all processes are completed
*/


// struct to hold process information
typedef struct
{
    int id;  // process id
    int at;  // arrival time
    int bt;  // burst time
    int wt;  // waiting time
    int tat; // turnaround time
    int completed; // completed flag
    int priority; // priority
} Process;




// function to calculate waiting time and turnaround time
void priorityScheduling(Process p[], int n) {
    int time = 0; // current time
    int completed = 0; // number of completed processes
    while(completed<n){
        int idx=-1;
        int minPriority=9999; // large number assuming the highest priority isnt 9999
        // finding the process to execute
        for(int i=0;i<n;i++){
            if(p[i].at<=time && p[i].completed==0){
                if(p[i].priority<minPriority){
                    minPriority=p[i].priority;
                    idx=i;
                }
            }
        }
        if(idx==-1){
            time++;
            continue;
        }
        p[idx].wt=time-p[idx].at;
        time+=p[idx].bt;
        p[idx].tat=time-p[idx].at;
        p[idx].completed=1;
        completed++;
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
    }
    priorityScheduling(p, n);
    print(p, n);
    return 0;
}