#include <stdio.h>
    
    int main() {
        int n, i, time = 0, completed = 0;
        int burst_time[20], remaining_time[20], arrival_time[20];
        int waiting_time[20], turnaround_time[20], pid[20];
        int is_completed[20] = {0};
    
        // Gantt chart
        int gantt_pid[100], gantt_time[100];
        int g = 0;
    
        float avg_wt = 0, avg_tat = 0;
    
        printf("Enter number of processes: ");
        scanf("%d", &n);
    
        for (i = 0; i < n; i++) {
            pid[i] = i + 1;
            printf("Enter arrival time of P%d: ", pid[i]);
            scanf("%d", &arrival_time[i]);
            printf("Enter burst time of P%d: ", pid[i]);
            scanf("%d", &burst_time[i]);
            remaining_time[i] = burst_time[i];
        }
    
        while (completed != n) {
            int index = -1;
            int min_rt = 99999;
    
            for (i = 0; i < n; i++) {
                if (arrival_time[i] <= time && remaining_time[i] > 0) {
                    if (remaining_time[i] < min_rt) {
                        min_rt = remaining_time[i];
                        index = i;
                    }
                }
            }
    
            if (index == -1) {
                time++;
            } else {
                gantt_pid[g] = pid[index];
                gantt_time[g++] = time;
    
                remaining_time[index]--;
                time++;
    
                if (remaining_time[index] == 0) {
                    completed++;
                    turnaround_time[index] = time - arrival_time[index];
                    waiting_time[index] = turnaround_time[index] - burst_time[index];
                }
            }
        }
    
        printf("\nPID\tAT\tBT\tWT\tTAT\n");
        for (i = 0; i < n; i++) {
            avg_wt += waiting_time[i];
            avg_tat += turnaround_time[i];
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
