#include <stdio.h>


struct Process
{
    int pid, at, bt, ct, rt, tat, wt;
  /*  int at;
    int bt;
    int ct;
    int rt;
    int tat;
    int wt;*/
};

int main()
{
    int n, i;

    printf("Enter the number of processes: ");
    scanf("%d",&n);

    struct Process p[n];

    for (i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("\nProcess P%d\n", p[i].pid);

        printf("Arrival Time: ");
        scanf("%d",&p[i].at);

        printf("Burst Time: ");
        scanf("%d",&p[i].bt);

        p[i].rt = p[i].bt;

    }

    int completed = 0;
    int currentTime = 0;

    printf("\nGantt Chart\n");

    printf("|");


    // SJF Scheduling
    while(completed < n)
    {
        int shortest = -1;


        for (i = 0; i < n; i++)
        {
            if (p[i].at <= currentTime && p[i].rt > 0)
            {

                if (shortest == -1 || p[i].bt < p[shortest].bt)
                {
                    shortest = i;
                }

                else if (p[i].rt < p[shortest].rt)
                    shortest = i;

                else if(p[i].rt == p[shortest].rt)
                {
                    if(p[i].at < p[shortest].at)
                        shortest = i;
                }
            }
        }

        if(shortest == -1)
            currentTime++;
        else
        {

            printf(" P%d |", p[shortest].pid);

            p[shortest].rt--;

            currentTime++;

            if(p[shortest].rt == 0)
            {
                p[shortest].ct = currentTime;

                completed++;
            }
        }

    }

    printf("\n");

    float avgWT = 0;
    float avgTAT = 0;


    for (i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;


        p[i].wt = p[i].tat - p[i].bt;

        avgWT += p[i].wt;

        avgTAT += p[i].tat;

    }

    printf("\n");

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");


    printf("\n----------------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }


    printf("\nAverage Turnaround Time: %.2f",(avgTAT/n) );

    printf("\nAverage Waiting Time: %.2f", (avgWT/n));

    return 0;
}
