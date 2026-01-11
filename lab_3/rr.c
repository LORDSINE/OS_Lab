#include <stdio.h>

int main() {
    int n, i, time = 0, tq;
    int burst_time[20], remaining_time[20], arrival_time[20];
    int waiting_time[20] = {0}, turnaround_time[20], pid[20];
    int completed = 0;

    // Gantt chart
    int gantt_pid[100], gantt_time[100];
    int g = 0;

    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter arrival time of P%d: ", pid[i]);
        scanf("%d", &arrival_time[i]);
        printf("Enter burst time of P%d: ", pid[i]);
        scanf("%d", &burst_time[i]);
        remaining_time[i] = burst_time[i];
    }

    while (completed != n) {
        int done = 1;

        for (i = 0; i < n; i++) {
            if (arrival_time[i] <= time && remaining_time[i] > 0) {
                done = 0;

                gantt_pid[g] = pid[i];
                gantt_time[g++] = time;

                if (remaining_time[i] > tq) {
                    time += tq;
                    remaining_time[i] -= tq;
                } else {
                    time += remaining_time[i];
                    waiting_time[i] = time - arrival_time[i] - burst_time[i];
                    remaining_time[i] = 0;
                    completed++;
                }
            }
        }

        if (done)
            time++;
    }

    for (i = 0; i < n; i++) {
        turnaround_time[i] = waiting_time[i] + burst_time[i];
        avg_wt += waiting_time[i];
        avg_tat += turnaround_time[i];
    }

    printf("\nPID\tAT\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               pid[i], arrival_time[i], burst_time[i],
               waiting_time[i], turnaround_time[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);

    // Gantt Chart
    printf("\nGantt Chart:\n");
    for (i = 0; i < g; i++) {
        printf("| P%d ", gantt_pid[i]);
    }
    printf("|\n");

    return 0;
}
