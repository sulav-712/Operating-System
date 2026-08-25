#include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int priority;
    int ct;
    int tat;
    int wt;
    int completed;
};

int main() {
    int n, i;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].completed = 0;

        printf("\nProcess P%d\n", p[i].pid);

        printf("Arrival Time: ");
        scanf("%d",&p[i].at);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Priority (smaller number = higher priority): ");
        scanf("%d", &p[i].priority);
    }

    int time = 0;
    int completed = 0;

    float avgWT = 0, avgTAT = 0;

    printf("\nGantt Chart\n");
    printf("|");

    while (completed < n) {
        int selected = -1; /*
         * Select the highest-priority process among the
         * processes that have already arrived.
         */

         for (i = 0; i < n; i++) {
            if (p[i].completed == 0 && p[i].at <= time) {
                if (selected == -1 || p[i].priority < p[selected].priority ||
                    (p[i].priority == p[selected].priority &&
                     p[i].at < p[selected].at) ||
                    (p[i].priority == p[selected].priority &&
                     p[i].at == p[selected].at &&
                     p[i].pid < p[selected].pid))
                        selected = i;
            }
         }

         /*
         * If no process has arrived, move the CPU time
         * forward to the next arrival time.
         */

         if (selected == -1) {
            int nextArrival = -1;

            for (i = 0; i < n; i++) {
                if (p[i].completed == 0) {
                    if (nextArrival == -1 ||
                        p[i].at < nextArrival)
                            nextArrival = p[i].at;
                }
            }

            time = nextArrival;
            continue;
         }

         // Execute the selected process completely
         time = time + p[selected].bt;

         p[selected].ct = time;
         p[selected].tat = p[selected].ct - p[selected].at;
         p[selected].wt = p[selected].tat - p[selected].bt;
         p[selected].completed = 1;

         avgTAT += p[selected].tat;
         avgWT += p[selected].wt;

         printf(" P%d |", p[selected].pid);

         completed++;

    }

    printf("\n");

    printf("\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    printf("-------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].priority,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f", avgTAT / n);
    printf("\nAverage Waiting Time: %.2f", avgWT / n);

    return 0;
}
