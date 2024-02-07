#include <stdio.h>
#include <limits.h>

struct Process {
    int id;
    int burstTime;
    int priority;
    int arrivalTime;
    int remainingTime;
};

void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n;
    printf("#Processes: ");
    scanf("%d", &n);
    
    int completed = 0;
    int currentTime = 0;
    int highestPriority = INT_MAX;
    int executingProcess = -1;

    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        printf("Arrival, Burst Time, and Priority for Process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrivalTime, &processes[i].burstTime, &processes[i].priority);
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].id = i + 1;
    }
    printf("\nProcess Id\tCT\t\tTAT\t\tWT\n");
    
    while (completed != n) {
        highestPriority = INT_MAX;
        executingProcess = -1; // no process currently selected
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 && processes[i].priority < highestPriority) {
                highestPriority = processes[i].priority;
                executingProcess = i;
            }
        }
        if (executingProcess == -1) {
            currentTime++;
            continue;
        }

        processes[executingProcess].remainingTime--;
        if (processes[executingProcess].remainingTime == 0) {
            completed++;
            int turnaroundTime = currentTime - processes[executingProcess].arrivalTime + 1;
            int waitingTime = turnaroundTime - processes[executingProcess].burstTime;
            int completionTime = currentTime + 1;
            printf("P%d\t\t%d\t\t%d\t\t%d\n", processes[executingProcess].id, completionTime, turnaroundTime, waitingTime);
        }
        currentTime++;
    }
    return 0;
}
