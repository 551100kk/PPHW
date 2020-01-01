#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/stat.h>
using namespace std;

#include "mpi.h"

#define BLOCK_LOW(id,p,n)  ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) (BLOCK_HIGH(id,p,n)-BLOCK_LOW(id,p,n)+1)
#define BLOCK_OWNER(j,p,n) (((p)*((j)+1)-1)/(n))

void solve(int p, int id, char **argv) {
    MPI_Comm grid_comm;
    MPI_Comm row_comm;
    MPI_Comm col_comm;
    int grid_size[2] = {};
    int periodic[2] = {};
    int grid_coords[2] = {};
    int grid_id;
    
    // Partition and read files
    MPI_Dims_create(p, 2, grid_size);
    MPI_Cart_create(MPI_COMM_WORLD, 2, grid_size, periodic, 1, &grid_comm);
    MPI_Comm_rank(grid_comm, &grid_id);
    MPI_Cart_coords(grid_comm, grid_id, 2, grid_coords);
    MPI_Comm_split(grid_comm, grid_coords[0], grid_coords[1], &row_comm);
    MPI_Comm_split(grid_comm, grid_coords[1], grid_coords[0], &col_comm);

    FILE *matrix_file = fopen(argv[1], "r");
    FILE *vector_file = fopen(argv[2], "r");
    int n;
    fread(&n, sizeof(int), 1, matrix_file);
    fread(&n, sizeof(int), 1, matrix_file);
    
    int rows = BLOCK_SIZE(grid_coords[0], grid_size[0], n);
    int row_l = BLOCK_LOW(grid_coords[0], grid_size[0], n);
    int cols = BLOCK_SIZE(grid_coords[1], grid_size[1], n);
    int col_l = BLOCK_LOW(grid_coords[1], grid_size[1], n);
    
    double **mat = (double **) malloc(rows * sizeof(double *));
    double *vec = (double *) malloc(rows * sizeof(double));
    double *sum = (double *) malloc(rows * sizeof(double));
    for (int i = 0; i < rows; i++) {
        mat[i] = (double *) malloc(cols * sizeof(double)); 
    }

    fseek(vector_file, 4 + sizeof(double) * col_l, SEEK_SET);
    fread(vec, sizeof(double), cols, vector_file);
    
    for (int i = 0; i < rows; i++) {
        fseek(matrix_file, 8 + sizeof(double) * ((row_l + i) * n + col_l), SEEK_SET);
        fread(mat[i], sizeof(double), cols, matrix_file);
    }

    fclose(matrix_file);
    fclose(vector_file);

    // Matrix multiplication
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum[i] += mat[i][j] * vec[j];
        }
    }

    // Reduction
    double *reduced_sum = (double *) malloc(rows * sizeof(double));
    double *gathered_sum = (double *) malloc(n * sizeof(double));
    MPI_Reduce(sum, reduced_sum, rows, MPI_DOUBLE, MPI_SUM, 0, row_comm);
    
    if (grid_coords[1] == 0) {
        int *block_size = (int *) malloc(grid_size[0] * sizeof(int));
        int *displs = (int *) malloc(grid_size[0] * sizeof(int));
        int offset = 0;
        for (int i = 0; i < grid_size[0]; i++) {
            displs[i] = offset;
            block_size[i] = BLOCK_SIZE(i, grid_size[0], n);
            offset += block_size[i];
        }
        MPI_Gatherv(reduced_sum, rows, MPI_DOUBLE, gathered_sum, block_size, displs, MPI_DOUBLE, 0, col_comm);
        if (grid_coords[0] == 0) {
            for (int i = 0; i < n; i++) {
                printf("%f\n", gathered_sum[i]);
            }    
        }
    }
}

int main(int argc, char** argv) {
    int id;
    int p;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    MPI_Barrier(MPI_COMM_WORLD);
    double time = -MPI_Wtime();
    double maxTime;
    // Do something.
    solve(p, id, argv);
    time += MPI_Wtime();
    MPI_Reduce(&time, &maxTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    if (id == 0) {
        printf ("%d processes: %.9f seconds\n", p, maxTime);
    }
    MPI_Finalize();
    return 0;
}