#include <stdio.h>

struct Process
{
    int pid, at, bt, ct, rt, tat, wt;
};

int main()
{
    int n, i, tq;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    struct Process p[n];

    for(i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("\nProcess P%d\n", p[i].pid);

        printf("Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        p[i].rt = p[i].bt;
    }

    int completed = 0;
    int currentTime = 0;

    printf("\nGantt Chart\n");
    printf("|");

    while(completed < n)
    {
        int executed = 0;

        for(i = 0; i < n; i++)
        {
            if(p[i].at <= currentTime && p[i].rt > 0)
            {
                executed = 1;

                printf(" P%d |", p[i].pid);

                if(p[i].rt > tq)
                {
                    currentTime += tq;
                    p[i].rt -= tq;
                }
                else
                {
                    currentTime += p[i].rt;
                    p[i].rt = 0;
                    p[i].ct = currentTime;
                    completed++;
                }
            }
        }

        if(executed == 0)
            currentTime++;
    }

    printf("\n");

    float avgWT = 0;
    float avgTAT = 0;

    for(i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        avgWT += p[i].wt;
        avgTAT += p[i].tat;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    printf("----------------------------------------------------------\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f", avgTAT / n);
    printf("\nAverage Waiting Time: %.2f\n", avgWT / n);

    return 0;
}
