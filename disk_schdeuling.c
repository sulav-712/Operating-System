// Disk Scheduling: SSTF, LOOK & C-LOOK
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void sstf(int requests[], int n, int head)
{
    int i, j, total = 0;
    int current = head;
    bool visited[100] = {false};

    printf("\nSSTF:\n");
    printf("%d", head);

    for (i = 0; i < n; i++)
    {
        int minDist = 9999, minIndex = -1;

        for (j = 0; j < n; j++)
        {
            if (!visited[j])
            {
                int dist = abs(requests[j] - current);
                if (dist < minDist)
                {
                    minDist = dist;
                    minIndex = j;
                }
            }
        }

        visited[minIndex] = true;
        total += minDist;
        current = requests[minIndex];
        printf(" -> %d", current);
    }

    printf("\nTotal Head Movement = %d\n", total);
}

void look(int requests[], int n, int head)
{
    int i, j, temp, total = 0;
    int sorted[100];

    // Copy and sort requests
    for (i = 0; i < n; i++)
        sorted[i] = requests[i];

    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (sorted[i] > sorted[j])
            {
                temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }

    printf("\nLOOK:\n");
    printf("%d", head);

    // Move towards higher requests first
    for (i = 0; i < n; i++)
    {
        if (sorted[i] >= head)
        {
            total += abs(head - sorted[i]);
            head = sorted[i];
            printf(" -> %d", head);
        }
    }

    // Then reverse and go to lower requests
    for (i = n - 1; i >= 0; i--)
    {
        if (sorted[i] < head)
        {
            total += abs(head - sorted[i]);
            head = sorted[i];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal Head Movement = %d\n", total);
}

void clook(int requests[], int n, int head)
{
    int i, j, temp, total = 0;
    int sorted[100];

    // Copy and sort requests
    for (i = 0; i < n; i++)
        sorted[i] = requests[i];

    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (sorted[i] > sorted[j])
            {
                temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }

    printf("\nC-LOOK:\n");
    printf("%d", head);

    // Service all requests >= head
    for (i = 0; i < n; i++)
    {
        if (sorted[i] >= head)
        {
            total += abs(head - sorted[i]);
            head = sorted[i];
            printf(" -> %d", head);
        }
    }

    // Jump to the smallest request
    if (head != sorted[0])
    {
        printf(" -> %d", sorted[0]);
        total += abs(head - sorted[0]);
        head = sorted[0];
    }

    // Service remaining requests (< original head)
    for (i = 0; i < n; i++)
    {
        if (sorted[i] < requests[0] && sorted[i] != head)
        {
            total += abs(head - sorted[i]);
            head = sorted[i];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal Head Movement = %d\n", total);
}

int main()
{
    int requests[] = {98, 183, 37, 122, 14, 65, 67};
    int n = 7;
    int head = 53;

    sstf(requests, n, head);
    look(requests, n, head);
    clook(requests, n, head);

    return 0;
}
