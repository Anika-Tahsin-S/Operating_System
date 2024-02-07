#include <stdio.h> 
#include <stdbool.h>  // boolean datatype
 
#define n 5 // Number of processes
#define m 4 // Number of resources

bool isSafe(int processes[n], int avail[m], int max[n][m], int alloc[n][m]) {
    int need[n][m];
    bool finish[n];
    int count = 0;

    for (int i = 0; i < n; i++) { // start from process 0 index to 5 - 1 index
        finish[i] = false;
        for (int j = 0; j < m; j++) { // start from resources 0 index to 4 - 1 index
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int work[m];
    for (int i = 0; i < m; i++) { // resource for work
        work[i] = avail[i];
    }

    while (count < n) {  // process count
        bool found = false;
        for (int i = 0; i < n; i++) { // checking process for false true
            if (finish[i] == false) {
                int j; // looking into resource
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == m) {
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[i][k];

                    finish[i] = true;
                    processes[count++] = i;
                    found = true;
                }
            }
        }
        if (found == false) {
            printf("The system is not in a safe state!\n");
            break;
        }
    }
    return (count == n);
}


bool detectDeadlock(int avail[m], int max[n][m], int alloc[n][m]) {
    int processes[n];
    return !isSafe(processes, avail, max, alloc);
}


int main() {
    int alloc[5][4] = {
        {0, 1, 0, 3}, // P0 // Allocation Matrix
        {2, 0, 0, 0}, // P1
        {3, 0, 2, 0}, // P2
        {2, 1, 1, 5}, // P3
        {0, 0, 2, 2}  // P4
    };

    int max[5][4] = {
        {6, 4, 3, 4}, // P0 // MAX Matrix
        {3, 2, 2, 1}, // P1
        {9, 1, 2, 6}, // P2
        {2, 2, 2, 8}, // P3
        {4, 3, 3, 7}  // P4
    };

    int avail[4] = {3, 3, 2, 1}; // Available resources

    bool deadlock = detectDeadlock(avail, max, alloc);

    printf(deadlock ? "Deadlock Ahead!\n" : "Safe here\n");
    return 0;
}

