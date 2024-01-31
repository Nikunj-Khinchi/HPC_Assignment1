#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to allocate memory for the graph
int** allocateMemory(int n) {
    int i;
    int **graph = (int **)malloc((long unsigned)n * sizeof(int *));
    for (i = 0; i < n; i++) {
        graph[i] = (int *)malloc((long unsigned)n * sizeof(int));
    }
    return graph;
}

// Function to read the graph from a file
void readGraphFromFile(FILE *file, int **graph, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }
}

// Function to print the graph
void printGraph(int **graph, int n) {
    printf("The graph is:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

// Function to perform the Floyd-Warshall algorithm
void performFloydWarshall(int **graph, int n) {
    int i, j, k;
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (graph[i][j] > graph[i][k] + graph[k][j])
                    graph[i][j] = graph[i][k] + graph[k][j];
            }
        }
    }
}

// Function to perform Dijkstra's algorithm
void performDijkstra(int **graph, int n) {
    for (int startVertex = 0; startVertex < n; startVertex++) {
        int *distance = (int *)malloc((long unsigned)n * sizeof(int));
        int *visited = (int *)malloc((long unsigned)n * sizeof(int));

        for (int i = 0; i < n; i++) {
            distance[i] = INT_MAX;
            visited[i] = 0;
        }

        distance[startVertex] = 0;

        for (int count = 0; count < n - 1; count++) {
            int minDistance = INT_MAX;
            int minIndex = -1;

            for (int v = 0; v < n; v++) {
                if (!visited[v] && distance[v] <= minDistance) {
                    minDistance = distance[v];
                    minIndex = v;
                }
            }

            visited[minIndex] = 1;

            for (int v = 0; v < n; v++) {
                if (!visited[v] && graph[minIndex][v] &&
                    distance[minIndex] != INT_MAX &&
                    distance[minIndex] + graph[minIndex][v] < distance[v]) {
                    distance[v] = distance[minIndex] + graph[minIndex][v];
                }
            }
        }

        // Print the distances from the start vertex
        // printf("Shortest distances from vertex %d:\n", startVertex);
        // for (int i = 0; i < n; i++) {
        //     printf("To vertex %d: %d\n", i, distance[i]);
        // }

        free(distance);
        free(visited);
        // printf("\n");
    }
}

// Function to free allocated memory
void freeMemory(int **graph, int n) {
    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);
}

int main(void) {
    int n;

    // Open the file for reading
    FILE *file = fopen("graph.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read the number of vertices from the file
    fscanf(file, "%d", &n);

    // Allocate memory for the graph
    int **graph = allocateMemory(n);

    // Read the graph from the file
    readGraphFromFile(file, graph, n);

    // Close the file
    fclose(file);

    // printGraph(graph, n);

    // Perform Floyd-Warshall algorithm
    // performFloydWarshall(graph, n);

    // printGraph(graph, n);

    // Perform Dijkstra's algorithm
    int startVertex = 0; // Change the start vertex as needed
    performDijkstra(graph, n);

    // Free allocated memory
    freeMemory(graph, n);

    return 0;
}



// #include <stdio.h>
// #include <stdlib.h>
// #include <limits.h>

// void performDijkstra(int **graph, int n) {
//     for (int startVertex = 0; startVertex < n; startVertex++) {
//         int *distance = (int *)malloc((long unsigned)n * sizeof(int));
//         int *visited = (int *)malloc((long unsigned)n * sizeof(int));

//         for (int i = 0; i < n; i++) {
//             distance[i] = INT_MAX;
//             visited[i] = 0;
//         }

//         distance[startVertex] = 0;

//         for (int count = 0; count < n - 1; count++) {
//             int minDistance = INT_MAX;
//             int minIndex = -1;

//             for (int v = 0; v < n; v++) {
//                 if (!visited[v] && distance[v] <= minDistance) {
//                     minDistance = distance[v];
//                     minIndex = v;
//                 }
//             }

//             if (minIndex != -1) {
//                 visited[minIndex] = 1;

//                 for (int v = 0; v < n; v++) {
//                     if (!visited[v] && graph[minIndex][v] &&
//                         distance[minIndex] != INT_MAX &&
//                         distance[minIndex] + graph[minIndex][v] < distance[v]) {
//                         distance[v] = distance[minIndex] + graph[minIndex][v];
//                     }
//                 }
//             }
//         }

//         free(distance);
//         free(visited);
//     }
// }

// void performFloydWarshall(int **graph, int n) {
//     for (int k = 0; k < n; k++) {
//         for (int i = 0; i < n; i++) {
//             for (int j = 0; j < n; j++) {
//                 if (graph[i][j] > graph[i][k] + graph[k][j]) {
//                     graph[i][j] = graph[i][k] + graph[k][j];
//                 }
//             }
//         }
//     }
// }

// int main(void) {
//     int n;

//     FILE *file = fopen("graph.txt", "r");

//     if (file == NULL) {
//         perror("Error opening file");
//         return 1;
//     }

//     fscanf(file, "%d", &n);

//     int **graph = (int **)malloc((long unsigned)n * sizeof(int *));
//     for (int i = 0; i < n; i++) {
//         graph[i] = (int *)malloc((long unsigned)n * sizeof(int));
//     }

//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             fscanf(file, "%d", &graph[i][j]);
//         }
//     }

//     fclose(file);

//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             for (int k = 0; k < n; k++) {
//                 graph[i][j] += 1;
//             }
//         }
//     }
 
//     performFloydWarshall(graph, n);
//     performDijkstra(graph, n);

//     for (int i = 0; i < n; i++) {
//         free(graph[i]);
//     }
//     free(graph);

//     return 0;
// }
