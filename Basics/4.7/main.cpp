#include <stdio.h>

#include "mpi.h"

int main(int argc, char** argv) {
    int id;
    int psize;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &psize);
    
    int val = id + 1;
    int sum = -1;
    printf("[Info] Process %d: val = %d\n", id, val);
    fflush(stdout);

    MPI_Reduce (&val, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    printf("[Info] Process %d: sum = %d\n", id, sum);

    if (id == 0) {
        if (sum == psize * (psize + 1) / 2) {
            printf("Correct sum!");
        } else {
            printf("Incorrect sum!");
        }
    }

    fflush(stdout);
    MPI_Finalize();
    return 0;
}
