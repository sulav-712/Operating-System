#include <stdio.h>

#define FRAMES 3

void fifo(int pages[], int n)
{
    int frame[FRAMES] = {-1, -1, -1};
    int index = 0, faults = 0;
    int i, j, found;

    printf("\nFIFO:\n");

    for (i = 0; i < n; i++)
    {
        found = 0;

        for (j = 0; j < FRAMES; j++)
        {
            if (frame[j] == pages[i])
                found = 1;
        }

        if (!found)
        {
            frame[index] = pages[i];
            index = (index + 1) % FRAMES;
            faults++;
        }

        printf("Page %d -> ", pages[i]);

        for (j = 0; j < FRAMES; j++)
            printf("%d ", frame[j]);

        printf("\n");
    }

    printf("Page Faults = %d\n", faults);
}

void lru(int pages[], int n)
{
    int frame[FRAMES] = {-1, -1, -1};
    int recent[FRAMES] = {0, 0, 0};
    int faults = 0, time = 0;
    int i, j, pos, found;

    printf("\nLRU:\n");

    for (i = 0; i < n; i++)
    {
        found = 0;
        time++;

        for (j = 0; j < FRAMES; j++)
        {
            if (frame[j] == pages[i])
            {
                found = 1;
                recent[j] = time;
            }
        }

        if (!found)
        {
            pos = -1;

            for (j = 0; j < FRAMES; j++)
            {
                if (frame[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            if (pos == -1)
            {
                pos = 0;

                for (j = 1; j < FRAMES; j++)
                {
                    if (recent[j] < recent[pos])
                        pos = j;
                }
            }

            frame[pos] = pages[i];
            recent[pos] = time;
            faults++;
        }

        printf("Page %d -> ", pages[i]);

        for (j = 0; j < FRAMES; j++)
            printf("%d ", frame[j]);

        printf("\n");
    }

    printf("Page Faults = %d\n", faults);
}

void lfu(int pages[], int n)
{
    int frame[FRAMES] = {-1, -1, -1};
    int freq[FRAMES] = {0, 0, 0};
    int faults = 0;
    int i, j, pos, found;

    printf("\nLFU:\n");

    for (i = 0; i < n; i++)
    {
        found = 0;

        for (j = 0; j < FRAMES; j++)
        {
            if (frame[j] == pages[i])
            {
                freq[j]++;
                found = 1;
                break;
            }
        }

        if (!found)
        {
            pos = -1;

            for (j = 0; j < FRAMES; j++)
            {
                if (frame[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            if (pos == -1)
            {
                pos = 0;

                for (j = 1; j < FRAMES; j++)
                {
                    if (freq[j] < freq[pos])
                        pos = j;
                }
            }

            frame[pos] = pages[i];
            freq[pos] = 1;
            faults++;
        }

        printf("Page %d -> ", pages[i]);

        for (j = 0; j < FRAMES; j++)
            printf("%d ", frame[j]);

        printf("\n");
    }

    printf("Page Faults = %d\n", faults);
}

int main()
{
    int pages[] = {1, 2, 3, 1, 4, 5, 2, 1, 2, 3};
    int n = 10;

    fifo(pages, n);
    lru(pages, n);
    lfu(pages, n);

    return 0;
}
