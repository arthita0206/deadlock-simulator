#include <stdio.h>
#include <stdlib.h>
#include "graph.c"

// Recursive function to detect a cycle in a directed graph
int isCyclicUtil(struct Graph* graph, int v, int* visited, int* recursionStack) {
    if (visited[v] == 0) {
        // Mark the current node as visited and part of recursion stack
        visited[v] = 1;
        recursionStack[v] = 1;

        // Recur for all the vertices adjacent to this vertex
        struct AdjListNode* node = graph->array[v].head;
        while (node != NULL) {
            if (!visited[node->dest] && isCyclicUtil(graph, node->dest, visited, recursionStack)) {
                return 1;
            } else if (recursionStack[node->dest]) {
                return 1;
            }
            node = node->next;
        }
    }
    recursionStack[v] = 0; // remove the vertex from recursion stack
    return 0;
}

// Main function to check if a graph contains a cycle
int detectCycle(struct Graph* graph) {
    int V = graph->V;
    int* visited = (int*) calloc(V, sizeof(int));
    int* recursionStack = (int*) calloc(V, sizeof(int));

    // Call the recursive helper function to detect cycle in different DFS trees
    for (int i = 0; i < V; i++) {
        if (isCyclicUtil(graph, i, visited, recursionStack)) {
            free(visited);
            free(recursionStack);
            return 1; // Cycle detected
        }
    }

    free(visited);
    free(recursionStack);
    return 0; // No cycle
}

// Function to build and check the Resource Allocation Graph
void runRAG(int processes, int resources, int allocation[][resources], int request[][resources]) {
    printf("\n--- Running Resource Allocation Graph (RAG) Cycle Detection ---\n");

    int num_nodes = processes + resources;
    struct Graph* graph = createGraph(num_nodes);

    // Add edges from processes to resources (request edge)
    // P_i -> R_j
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            if (request[i][j] > 0) {
                // Process i (node i) requests Resource j (node processes + j)
                addEdge(graph, i, processes + j);
                 printf("Edge: P%d -> R%d (Request)\n", i, j);
            }
        }
    }

    // Add edges from resources to processes (assignment edge)
    // R_j -> P_i
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            if (allocation[i][j] > 0) {
                // Resource j (node processes + j) is allocated to Process i (node i)
                addEdge(graph, processes + j, i);
                 printf("Edge: R%d -> P%d (Allocation)\n", j, i);
            }
        }
    }

    if (detectCycle(graph)) {
        printf("\nCycle detected in the RAG. A deadlock exists.\n");
    } else {
        printf("\nNo cycle detected in the RAG. The system is not deadlocked.\n");
    }
    
    freeGraph(graph);
}
