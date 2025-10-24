#include <stdio.h>

// Function to run the deadlock detection algorithm
void runDetection(int processes, int resources, int available[], int allocation[][resources], int request[][resources]) {
    printf("\n--- Running Deadlock Detection Algorithm ---\n");

    int work[resources];
    int i, j;
    for (i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    int finish[processes];
    for (i = 0; i < processes; i++) {
        // Assume a process is not deadlocked if it has no allocation
        int hasAllocation = 0;
        for(j = 0; j < resources; j++) {
            if (allocation[i][j] != 0) {
                hasAllocation = 1;
                break;
            }
        }
        finish[i] = hasAllocation ? 0 : 1;
    }

    int found;
    do {
        found = 0;
        for (i = 0; i < processes; i++) {
            if (finish[i] == 0) {
                int can_proceed = 1;
                for (j = 0; j < resources; j++) {
                    if (request[i][j] > work[j]) {
                        can_proceed = 0;
                        break;
                    }
                }

                if (can_proceed) {
                    for (j = 0; j < resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
    } while (found);

    // Check for deadlocked processes
    int deadlocked_processes[processes];
    int deadlock_count = 0;
    for (i = 0; i < processes; i++) {
        if (finish[i] == 0) {
            deadlocked_processes[deadlock_count++] = i;
        }
    }

    if (deadlock_count > 0) {
        printf("\nDeadlock detected!\n");
        printf("The following processes are deadlocked: ");
        for (i = 0; i < deadlock_count; i++) {
            printf("P%d ", deadlocked_processes[i]);
        }
        printf("\n");
    } else {
        printf("\nNo deadlock detected. The system is safe.\n");
    }
}