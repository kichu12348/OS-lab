#include <stdio.h>

/*
Deadlock Detection Algorithm:
1. Let Work and Finish be vectors of length 'm' and 'n' respectively.
    Initialize: Work = Available
    Finish[i] = false for i=1,2,3,...,n

2. Find an i such that both:
    a) Finish[i] = false
    b) Request[i] <= Work
    If no such i exists, go to step 4

3. Work = Work + Allocation[i]
    Finish[i] = true
    Go to step 2

4. If Finish[i] = true for all i,
    then system is in safe state
    else system is not in safe state and deadlock is detected.

5. Print the processes in deadlock.
6. If deadlock is detected, the system is not in a safe state.
*/

void detection(
    int avail[],
    int p[][10],
    int req[][10],
    int n,
    int m)
{
    int work[m];
    for (int i = 0; i < m; i++)
        work[i] = avail[i];

    int count = 0;
    int finish[n];
    for (int i = 0; i < n; i++)
        finish[i] = 0;

    while (count < n)
    {
        int found = 0;
        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                int j;
                for (j = 0; j < m; j++)
                    if (req[i][j] > work[j])
                        break;

                if (j == m)
                {
                    for (int k = 0; k < m; k++)
                        work[k] += p[i][k];
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }

        if (!found)
            break;
    }

    int deadlock = 0;
    printf("Processes in deadlock: ");
    for (int i = 0; i < n; i++)
    {
        if (!finish[i])
        {
            deadlock = 1;
            printf("P%d ", i);
        }
    }
    printf("\n");
    if (deadlock)
    {
        printf("System is not safe deadlock detected\n");
    }
    else
        printf("No deadlock detected\n");
}

void main()
{
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int avail[m];
    printf("Enter the available resources: ");
    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    int p[n][10], req[n][10];
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &p[i][j]);

    printf("Enter the request matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &req[i][j]);

    detection(avail, p, req, n, m);
}