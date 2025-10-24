#include <stdio.h>

// Function to check if the system is in a safe state
int isSafe(int processes, int resources, int available[], int max[][resources], int allocation[][resources]) {
    int need[processes][resources];
    int i, j, k;

    // Calculate the need matrix
    for (i = 0; i < processes; i++) {
        for (j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    int finish[processes];
    for (i = 0; i < processes; i++) {
        finish[i] = 0; // 0 means not finished
    }

    int work[resources];
    for (i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    int safeSequence[processes];
    int count = 0;

    while (count < processes) {
        int found = 0;
        for (i = 0; i < processes; i++) {
            if (finish[i] == 0) {
                int can_allocate = 1;
                for (j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = 0;
                        break;
                    }
                }

                if (can_allocate) {
                    for (k = 0; k < resources; k++) {
                        work[k] += allocation[i][k];
                    }
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0) {
            printf("\nSystem is not in a safe state.\n");
            return 0; // Not safe
        }
    }

    printf("\nSystem is in a safe state.\nSafe sequence is: ");
    for (i = 0; i < processes - 1; i++) {
        printf("P%d -> ", safeSequence[i]);
    }
    printf("P%d\n", safeSequence[processes - 1]);

    return 1; // Safe
}

// Main function to run the Banker's Algorithm
void runBankers(int processes, int resources, int available[], int max[][resources], int allocation[][resources]) {
    printf("\n--- Running Banker's Algorithm for Deadlock Avoidance ---\n");
    isSafe(processes, resources, available, max, allocation);
}