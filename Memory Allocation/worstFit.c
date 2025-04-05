#include <stdio.h>

typedef struct
{
    int ts, rs;
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
            if (m[j].rs >= pr && m[j].rs > sm)
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