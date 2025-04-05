#include <stdio.h>

typedef struct
{
    /* data */
    int ts, rs;
} Memory;

void Allocate(int p[], Memory m[], int n, int q)
{
    for (int i = 0; i < n; i++)
    {
        int pr = p[i];
        int mIdx = -1;
        for (int j = 0; j < q; j++)
        {
            if (m[j].rs >= pr)
            {
                mIdx = j;
                break;
            }
        }
        if (mIdx == -1)
        {
            printf("Process with size: %d KB couldnt be allocated\n", pr);
        }
        else
        {
            m[mIdx].rs -= pr;
            printf("Proccess %d KB allocated to memory block %d KB remaining size: %d\n", pr, m[mIdx].ts, m[mIdx].rs);
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