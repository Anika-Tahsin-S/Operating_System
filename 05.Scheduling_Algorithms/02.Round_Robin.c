#include <stdio.h>

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
    int n, quantum;
    printf("#Processes: ");
    scanf("%d", &n);
    
    int completed = 0;
    int currentTime = 0;

    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        printf("Arrival and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].id = i + 1;
    }

    printf("Time Quantum: ");
    scanf("%d", &quantum);
    printf("\nProcess Id\tCT\t\tTAT\t\tWT\n");

    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remainingTime > 0) {
                int executionTime = min(quantum, processes[i].remainingTime);
                processes[i].remainingTime -= executionTime;
                currentTime += executionTime;

                if (processes[i].remainingTime == 0) {
                    completed++;
                    int turnaroundTime = currentTime - processes[i].arrivalTime;
                    int waitingTime = turnaroundTime - processes[i].burstTime;

                    printf("P%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, currentTime, turnaroundTime, waitingTime);
                }
            }
        }
    }
    return 0;
}
