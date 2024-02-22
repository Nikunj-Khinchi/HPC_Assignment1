#include <stdio.h>
#include <omp.h>

#define ARRAY_SIZE 1000

int main() {
    int shared_array[ARRAY_SIZE];
    int i;

    // Initialize the array
    for (i = 0; i < ARRAY_SIZE; i++) {
        shared_array[i] = 0;
    }

    // Parallel region where each thread increments elements of the array atomically
    #pragma omp parallel for
    for (i = 0; i < ARRAY_SIZE; i++) {
        #pragma omp atomic
        shared_array[i]++;
    }

    // Print the incremented array
    printf("Array after increment:\n");
    for (i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", shared_array[i]);
    }
    printf("\n");

    return 0;
}
