#include <stdio.h>

int main() {
    int n, i, time = 0, completed = 0;

    int burst_time[20], arrival_time[20], waiting_time[20], turnaround_time[20], pid[20];
    int is_completed[20] = {0};

    // Gantt chart tracking
    int gantt_pid[20], gantt_start[20], gantt_end[20];
    int gantt_index = 0;

    float avg_waiting_time = 0;
    float avg_turn_around_time = 0;

    printf("Enter the no of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter arrival time of P%d: ", pid[i]);
        scanf("%d", &arrival_time[i]);
        printf("Enter burst time of P%d: ", pid[i]);
        scanf("%d", &burst_time[i]);
    }

    while (completed != n) {
        int index = -1;
        int min_burst_time = 99999;

        for (i = 0; i < n; i++) {
            if (arrival_time[i] <= time && !is_completed[i]) {
                if (burst_time[i] < min_burst_time) {
                    min_burst_time = burst_time[i];
                    index = i;
                }
            }
        }

        if (index == -1) {
            time++;
        } else {
            gantt_pid[gantt_index] = pid[index];
            gantt_start[gantt_index] = time;

            waiting_time[index] = time - arrival_time[index];
            time += burst_time[index];
            turnaround_time[index] = waiting_time[index] + burst_time[index];

            gantt_end[gantt_index] = time;
            gantt_index++;

            is_completed[index] = 1;
            completed++;
        }
    }

    printf("\nPID\tAT\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        avg_waiting_time += waiting_time[i];
        avg_turn_around_time += turnaround_time[i];

        printf("P%d\t%d\t%d\t%d\t%d\n",
               pid[i], arrival_time[i], burst_time[i],
               waiting_time[i], turnaround_time[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_waiting_time / n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_turn_around_time / n);

    // Gantt Chart
    printf("\nGantt Chart:\n");
    printf("-------------------------------------------------\n");

    for (i = 0; i < gantt_index; i++) {
        printf("| P%d ", gantt_pid[i]);
    }
    printf("|\n");

    printf("-------------------------------------------------\n");

    printf("%d", gantt_start[0]);
    for (i = 0; i < gantt_index; i++) {
        printf("    %d", gantt_end[i]);
    }
    printf("\n");

    return 0;
}
