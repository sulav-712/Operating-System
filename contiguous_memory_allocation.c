#include <stdio.h>

void firstFit(int block[], int b, int process[], int p)
{
    int allocation[p];
    int i, j;

    for (i = 0; i < p; i++)
        allocation[i] = -1;

    for (i = 0; i < p; i++)
    {
        for (j = 0; j < b; j++)
        {
            if (block[j] >= process[i])
            {
                allocation[i] = j;
                block[j] -= process[i];
                break;
            }
        }
    }

    printf("\nFirst Fit:\n");
    for (i = 0; i < p; i++)
    {
        if (allocation[i] != -1)
            printf("Process %d -> Block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d -> Not Allocated\n", i + 1);
    }
}

void bestFit(int block[], int b, int process[], int p)
{
    int allocation[p];
    int i, j, best;

    for (i = 0; i < p; i++)
        allocation[i] = -1;

    for (i = 0; i < p; i++)
    {
        best = -1;

        for (j = 0; j < b; j++)
        {
            if (block[j] >= process[i])
            {
                if (best == -1 || block[j] < block[best])
                    best = j;
            }
        }

        if (best != -1)
        {
            allocation[i] = best;
            block[best] -= process[i];
        }
    }

    printf("\nBest Fit:\n");
    for (i = 0; i < p; i++)
    {
        if (allocation[i] != -1)
            printf("Process %d -> Block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d -> Not Allocated\n", i + 1);
    }
}

void worstFit(int block[], int b, int process[], int p)
{
    int allocation[p];
    int i, j, worst;

    for (i = 0; i < p; i++)
        allocation[i] = -1;

    for (i = 0; i < p; i++)
    {
        worst = -1;

        for (j = 0; j < b; j++)
        {
            if (block[j] >= process[i])
            {
                if (worst == -1 || block[j] > block[worst])
                    worst = j;
            }
        }

        if (worst != -1)
        {
            allocation[i] = worst;
            block[worst] -= process[i];
        }
    }

    printf("\nWorst Fit:\n");
    for (i = 0; i < p; i++)
    {
        if (allocation[i] != -1)
            printf("Process %d -> Block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d -> Not Allocated\n", i + 1);
    }
}

int main()
{
    int blocks[] = {100, 500, 200, 300, 600};
    int processes[] = {212, 417, 112, 426};

    int b = 5, p = 4;

    firstFit(blocks, b, processes, p);

    int blocks2[] = {100, 500, 200, 300, 600};
    bestFit(blocks2, b, processes, p);

    int blocks3[] = {100, 500, 200, 300, 600};
    worstFit(blocks3, b, processes, p);

    return 0;
}
