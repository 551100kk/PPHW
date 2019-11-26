#include <bits/stdc++.h>
using namespace std;

#include "mpi.h"

int main(int argc, char** argv) {
    int id;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    printf("Hello, world! From process: %d\n", id);
    MPI_Finalize();
}
