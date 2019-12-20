#include <bits/stdc++.h>
using namespace std;

#include "mpi.h"

#define BLOCK_LOW(id,p,n)  ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) (BLOCK_HIGH(id,p,n)-BLOCK_LOW(id,p,n)+1)
#define BLOCK_OWNER(j,p,n) (((p)*((j)+1)-1)/(n))

const long long n = 100000000;
const int s = 2;
const double d = 0.3;

void solve(long long p, long long id) {
    double round = n / p;
    double volume = 0;

    srand(time(NULL));
    for (long long i = 0; i < round; i++) {
        double x = (double) rand() / RAND_MAX * s;
        double y = (double) rand() / RAND_MAX * s;
        double z = (double) rand() / RAND_MAX * s;
        double dist = sin(acos((x + y + z) / (sqrt(3) * sqrt(x * x + y * y + z * z)))) * sqrt(x * x + y * y + z * z);
        if (dist > d / 2) volume += 1;
    }

    volume /= round;
    double ans;
    MPI_Reduce(&volume, &ans, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (id == 0) {
        ans /= p;
        printf("%.10f\n", ans * s * s * s);
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
    solve(p, id);
    time += MPI_Wtime();
    MPI_Reduce(&time, &maxTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    if (id == 0) {
        printf ("%d processes: %.9f seconds\n", p, maxTime);
    }
    MPI_Finalize();
    return 0;
}

