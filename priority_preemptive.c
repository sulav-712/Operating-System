#include <stdio.h>

struct Process {
    int pid, at, bt, rt, priority, ct, tat, wt;
};

int main() {
    int n, i;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (i = 0; i < n; i++) {
        p[i].pid = i +1;

        printf("\nProcess P%d\n", p[i].pid);

        printf("Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Priority (lower number = higher priority): ");
        scanf("%d", &p[i].priority);

        p[i].rt = p[i].bt;
    }

    int time = 0, completed = 0, current = -1;

    int gantt[1000];
    int gantt_len = 0;

    while (completed < n) {
        int highest = -1, idx = -1;

        for (i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                if (highest == -1 || p[i].priority < highest) {
                    highest = p[i].priority;
                    idx = i;
                } else if (p[i].priority == highest) {
                    if (p[i].at < p[idx].at)
                        idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        p[idx].rt--;
        gantt[gantt_len++] = p[idx].pid;

        time++;

        if (p[idx].rt == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
        }

        current = idx;
    }

    printf("\nGantt Chart\n");
    printf("|");
    for (i = 0; i < gantt_len; i++) {
        printf(" P%d |", gantt[i]);
    }
    printf("\n");

    printf("\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    printf("---------------------------------------------------------------\n");


    float avgWT = 0;
    float avgTAT = 0;

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].priority,
               p[i].ct, p[i].tat, p[i].wt);

        avgWT += p[i].wt;
        avgTAT += p[i].tat;
    }

    printf("\nAverage Turnaround Time: %.2f", avgTAT / n);
    printf("\nAverage Waiting Time: %.2f", avgWT / n);

    return 0;
}
