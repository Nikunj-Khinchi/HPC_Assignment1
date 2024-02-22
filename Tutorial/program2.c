#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000000
#define A 2.0

void saxpy_serial(double *x, double *y, double a, int n) {
    for (int i = 0; i < n; ++i) {
        y[i] = a * x[i] + y[i];
    }
}

void saxpy_parallel(double *x, double *y, double a, int n) {
    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        y[i] = a * x[i] + y[i];
    }
}

int main() {
    double *x = (double *)malloc(N * sizeof(double));
    double *y = (double *)malloc(N * sizeof(double));
    double start, end;

    // Check if memory allocation is successful
    if (x == NULL || y == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Initialize vectors
    for (int i = 0; i < N; ++i) {
        x[i] = i * 0.5;
        y[i] = i * 1.5;
    }

    // Serial SAXPY
    start = omp_get_wtime();
    saxpy_serial(x, y, A, N);
    end = omp_get_wtime();
    printf("Serial SAXPY time: %f seconds\n", end - start);

    // Reset y vector
    for (int i = 0; i < N; ++i) {
        y[i] = i * 1.5;
    }

    // Parallel SAXPY
    start = omp_get_wtime();
    saxpy_parallel(x, y, A, N);
    end = omp_get_wtime();
    printf("Parallel SAXPY time: %f seconds\n", end - start);

    // Free dynamically allocated memory
    free(x);
    free(y);

    return 0;
}
