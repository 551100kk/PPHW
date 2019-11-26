#include <bits/stdc++.h>
using namespace std;

#include "mpi.h"

#define BLOCK_LOW(id,p,n)  ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) (BLOCK_HIGH(id,p,n)-BLOCK_LOW(id,p,n)+1)
#define BLOCK_OWNER(j,p,n) (((p)*((j)+1)-1)/(n))

const int n = 1000000;

long double f(int i) {
    long double x;
    x = (long double) i / (long double) n;
    return 4.0 / (1.0 + x * x);
}

long double calc(int p, int id) {
    int start = BLOCK_LOW(id, p, n / 2) + 1;
    int end = BLOCK_HIGH(id, p, n / 2) + 1;

    long double area = 0;
    if (id == 0) {
        area = f(0) - f(n);
    }
    for (int i = start; i <= end; i++)
        area += 4.0 * f(2 * i - 1) + 2 * f(2 * i);
    area /= (3.0 * n);
    return area;
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
    long double cnt = calc(p, id);
    long double totalCnt;
    MPI_Reduce(&cnt, &totalCnt, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    time += MPI_Wtime();
    MPI_Reduce(&time, &maxTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    if (id == 0) {
        printf("PI: 3.14159265358979323846264338327950288419716939937510582097494459230781 (correct)\n");
        printf("PI: %.30Lf (our)\n", totalCnt);
        printf ("%d processes: %.9f seconds\n", p, maxTime);
    }
    MPI_Finalize();
    return 0;
}

