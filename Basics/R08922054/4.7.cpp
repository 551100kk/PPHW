#include <bits/stdc++.h>
using namespace std;

#include "mpi.h"

int main(int argc, char** argv) {
    int id;
    int psize;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &psize);
    
    int val = id + 1;
    int sum = -1;

    MPI_Reduce (&val, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (id == 0) {
        printf("[Info] Process %d: sum = %d\n", id, sum);
        if (sum == psize * (psize + 1) / 2) {
            printf("Correct sum!\n");
        } else {
            printf("Incorrect sum!\n");
        }
    }

    MPI_Finalize();
    return 0;
}
