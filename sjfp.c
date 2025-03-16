#include<stdio.h>


/*
this is not in syllabus apparently 🙂 
    shortest job first pre-emptive

    1. The process with the smallest execution time is selected for execution.
    2. If two processes have the same execution time, the process that arrived first is selected.
    3. The process that arrives first, gets added to the queue first, and runs first.
    4. The process that arrives next, gets added to the queue next, and runs next.
    5. The process that arrives last, gets added to the queue last, and runs last.
     this is pre-emptive
    i will use an array of structs called process
    each struct will have an id, arrival time, burst time, waiting time, and turnaround time and completed default 0 ie false
    i will sort the array of structs by burst time
    then i will calculate the waiting time and turnaround time for each process
*/

// struct to hold process information
typedef struct
{
    int id;  // process id
    int at;  // arrival time
    int bt;  // burst time
    int wt;  // waiting time
    int tat; // turnaround time
    int completed;
} Process;

int hasCompleted = 0;
int time = 0;

// function to sort the array of structs by arrival time using bubble sort
void sort(Process p[], int n)
{
    Process temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].at > p[j].at)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

// function to calculate waiting time and turnaround time
void runProcess(Process p[], int n)
{
    // calculate waiting time and turnaround time for each process
    while (hasCompleted != n)
    {
        int shortest=-1;
        for (int i = 0; i < n; i++)
            if (p[i].at <= time && p[i].completed == 0)
                if(shortest == -1 || p[i].bt < p[shortest].bt) 
                    shortest = i;
        

        if(shortest != -1)
        {
            p[shortest].bt--;
            time++;
            if(p[shortest].bt == 0)
            {
                p[shortest].completed = 1;
                hasCompleted++;
                p[shortest].tat = time - p[shortest].at;
                p[shortest].wt = p[shortest].at + p[shortest].tat -time;
            }
        }
        else time++;
    }
}


// function to print the waiting time and turnaround time for each process
void print(Process p[], int n)
{
    printf("Process ID\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\n", p[i].id, p[i].at, p[i].wt, p[i].tat);
    }
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process p[n];

    // get process information
    for (int i = 0; i < n; i++)
    {
        printf("Enter the arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].id = i + 1;
        p[i].completed = 0;
    }
    sort(p, n);
    runProcess(p, n);
    print(p, n);

    return 0;
}