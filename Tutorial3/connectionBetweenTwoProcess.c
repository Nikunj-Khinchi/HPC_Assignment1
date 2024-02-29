#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int process_Rank, size_Of_Cluster;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_Rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size_Of_Cluster);
    if (size_Of_Cluster >= 2) {
        if (process_Rank == 0) {
            int message = 100;
            MPI_Send(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            printf("Process 0 sent message %d to process 1.\n", message);
        } else if (process_Rank == 1) {
            int received_message;
            MPI_Recv(&received_message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process 1 received message %d from process 0.\n", received_message);
        }
    } else {
        printf("This program requires at least 2 processes.\n");
    }
    MPI_Finalize();

    return 0;
}