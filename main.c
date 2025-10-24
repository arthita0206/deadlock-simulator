#include <stdio.h>
#include <stdlib.h>

// Include implementation files
#include "banker.c"
#include "detection.c"
#include "rag.c"

// Export Resource Allocation Graph function
void exportRAG(int processes, int resources, int allocation[processes][resources], int need[processes][resources]) {
    FILE *fp = fopen("rag.dot", "w");
    if (!fp) {
        printf("Error opening rag.dot for writing!\n");
        return;
    }
    fprintf(fp, "digraph RAG {\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            // Edge from process to resource (if need/request > 0)
            if (need[i][j] > 0)
                fprintf(fp, "  P%d -> R%d;\n", i, j);
            // Edge from resource to process (if allocated > 0)
            if (allocation[i][j] > 0)
                fprintf(fp, "  R%d -> P%d;\n", j, i);
        }
    }
    fprintf(fp, "}\n");
    fclose(fp);
    printf("Exported Resource Allocation Graph to rag.dot\n");
}

int main() {
    int processes, resources;

    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    // Variable-length arrays
    int available[resources];
    int max[processes][resources];
    int allocation[processes][resources];
    int need[processes][resources];

    // Input available resources
    printf("\nEnter the available instances of each resource:\n");
    for (int i = 0; i < resources; i++) {
        printf("Resource %d: ", i);
        scanf("%d", &available[i]);
    }

    // Input max demand
    printf("\nEnter the maximum demand of each process:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input allocation
    printf("\nEnter the allocated resources for each process:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Calculate and display need matrix
    printf("\nThe current resource needs (Max - Allocation) for each process:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    int choice;
    while (1) {
        printf("\n--- Deadlock Simulator Menu ---\n");
        printf("1. Run Banker's Algorithm (Deadlock Avoidance)\n");
        printf("2. Run Deadlock Detection Algorithm\n");
        printf("3. Run RAG Cycle Detection\n");
        printf("4. Export Resource Allocation Graph\n"); // Visualization option!
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                runBankers(processes, resources, available, max, allocation);
                break;
            case 2:
                runDetection(processes, resources, available, allocation, need);
                break;
            case 3:
                runRAG(processes, resources, allocation, need);
                break;
            case 4:
                exportRAG(processes, resources, allocation, need); // Export function
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
