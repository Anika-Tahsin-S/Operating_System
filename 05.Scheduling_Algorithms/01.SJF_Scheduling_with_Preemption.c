#include <stdio.h>
#include <limits.h>

struct Process {
    int id;
    int burstTime;
    int arrivalTime;
    int remainingTime;
};

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int n;
    printf("#Processes: ");
    scanf("%d", &n);

    int completed = 0;
    int currentTime = 0;
    int shortestIndex = 0;
    int shortest = INT_MAX;

    struct Process processes[n]; // declaring array named processes[n]
    for (int i = 0; i < n; i++) {
        printf("Arrival and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].id = i + 1;
    }
    printf("\nProcess Id\tCT\t\tTAT\t\tWT\n");

    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime < shortest && processes[i].remainingTime > 0) {
                shortest = processes[i].remainingTime;
                shortestIndex = i;
            }
        }
        processes[shortestIndex].remainingTime--;

        if (processes[shortestIndex].remainingTime == 0) {
            completed++;
            shortest = INT_MAX;
            int turnaroundTime = currentTime - processes[shortestIndex].arrivalTime + 1;
            int waitingTime = turnaroundTime - processes[shortestIndex].burstTime;
            int completionTime = currentTime + 1;

            printf("P%d\t\t%d\t\t%d\t\t%d\n", processes[shortestIndex].id, completionTime, turnaroundTime, waitingTime);
        }
        currentTime++;
    }
    return 0;
}
