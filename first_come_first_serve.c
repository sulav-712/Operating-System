#include <stdio.h>

struct Process
{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
};

int main()
{
    int n;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    struct Process p[n];

    int i;

    for (i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("\nProcess P%d\n",p[i].pid);

        printf("Arrival Time: ");
        scanf("%d",&p[i].at);

        printf("Burst Time: ");
        scanf("%d",&p[i].bt);
    }


    // Sorting
    for (i = 0; i < n - 1; i++){
        int j;

        for(j = i + 1; j < n; j++) {
            if(p[i].at > p[j].at){
                struct Process temp;

                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int time = 0;

    printf("\nGantt Chart\n");

    printf("|");

    // Completion Time
    for (i = 0; i < n; i++) {
        if(time < p[i].at)
            time = p[i].at;

        time = time + p[i].bt;

        p[i].ct = time;

        printf(" P%d |", p[i].pid);
    }

    printf("\n");


    // Calculate TAT & WT

    float avgWT = 0;
    float avgTAT = 0;


    for (i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;       //TAT = CT - AT

        p[i].wt = p[i].tat - p[i].bt;       //WT = TAT - BT


        avgWT = avgWT + p[i].wt;

        avgTAT = avgTAT + p[i].tat;
    }


    printf("\n");

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");


    printf("\n----------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }


    printf("\nAverage Turnaround Time: %.2f",(avgTAT/n) );

    printf("\nAverage Waiting Time: %.2f", (avgWT/n));

    return 0;
}
