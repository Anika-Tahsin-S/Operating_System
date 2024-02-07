#include <stdio.h>
#include <stdbool.h>

void generateSafeSequence(int n, int m, int avail[m], int max[n][m], int alloc[n][m]) {
    int need[n][m];
    bool finish[n];
    int safeSeq[n];
    int count = 0;

    for (int i = 0; i < n; i++) { // start from process 0 index to 5 - 1 index
        finish[i] = false;
        for (int j = 0; j < m; j++) { // start from resources 0 index to 4 - 1 index
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int work[m];
    for (int i = 0; i < m; i++)
        work[i] = avail[i];


    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (finish[i] == false) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == m) {
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[i][k];

                    finish[i] = true;
                    safeSeq[count++] = i;
                    found = true;
                }
            }
        }
        if (found == false) {
            printf("The system is not in a safe state!\n");
            return;
        }
    }

    printf("Safe Sequence: ");
    for (int i = 0; i < n - 1; i++)
        printf("P%d -> ", safeSeq[i]);
    printf("P%d\n", safeSeq[n - 1]); // Prints the last process in the sequence
}

int main() {
    int n = 6; // Number of processes
    int m = 4; // Number of resources
    int alloc[6][4] = {
        {0, 1, 0, 3}, // P0 // Allocation Matrix
        {2, 0, 0, 3}, // P1
        {3, 0, 2, 0}, // P2
        {2, 1, 1, 5}, // P3
        {0, 0, 2, 2}, // P4
        {1, 2, 3, 1}  // P5
    };

    int max[6][4] = {
        {6, 4, 3, 4}, // P0 // MAX Matrix
        {3, 2, 2, 4}, // P1
        {9, 1, 2, 6}, // P2
        {2, 2, 2, 8}, // P3
        {4, 3, 3, 7}, // P4
        {6, 2, 6, 5}  // P5
    };

    int avail[4] = {2, 2, 2, 1}; // Available resources

    generateSafeSequence(n, m, avail, max, alloc);

    return 0;
}

