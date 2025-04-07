#include <stdio.h>


/*
this code implements the Worst Fit memory allocation algorithm.
this is the non contiguous memory allocation algorithm.
it allocates the largest available memory block that is large enough to satisfy the request.
it is used to minimize the amount of wasted memory space.

working of program:
1. the user is prompted to enter the number of processes and the number of memory blocks.
2. the user is prompted to enter the size of each process and the size of each memory block.
3. the program iterates through each process and finds the largest available memory block that is large enough to satisfy the request.
4. if a suitable memory block is found, it is allocated to the process and the remaining size of the memory block is updated.
5. if no suitable memory block is found, a message is displayed indicating that the process could not be allocated.
6. the program continues until all processes have been allocated or all memory blocks have been used up.
7. the program displays the size of each process, the size of each memory block, and the remaining size of each memory block after allocation.
// 8. the program ends when all processes have been allocated or all memory blocks have been used up.
*/




typedef struct
{
    int ts, rs;
    int isUsed;
} Memory;

void Allocate(int p[], Memory m[], int n, int q)
{
    for (int i = 0; i < n; i++)
    {
        int idx = -1;
        int sm = m[0].rs;
        int pr = p[i];

        for (int j = 0; j < q; j++)
        {
            if (m[j].rs >= pr && m[j].rs > sm && !m[j].isUsed)
            {
                idx = j;
                sm = m[j].rs;
            }
        }

        if (idx == -1)
            printf("Process with size: %d KB couldnt be allocated\n", pr);

        else
        {
            m[idx].rs -= pr;
            m[idx].isUsed=1;
            printf("Proccess %d KB allocated to memory block %d KB remaining size: %d\n", pr, m[idx].ts, m[idx].rs);
        }
    }
}

void main()
{
    int n, q;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of memory blocks: ");
    scanf("%d", &q);
    int p[n];
    Memory m[q];
    printf("Enter size of process\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &p[i]);

    printf("Enter size of memory block\n");

    for (int i = 0; i < q; i++)
    {
        scanf("%d", &m[i].rs);
        m[i].ts = m[i].rs;
    }
    Allocate(p, m, n, q);
}