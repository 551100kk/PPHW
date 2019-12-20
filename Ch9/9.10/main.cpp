#include <bits/stdc++.h>
using namespace std;

#include "mpi.h"

#define BLOCK_LOW(id,p,n)  ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) (BLOCK_HIGH(id,p,n)-BLOCK_LOW(id,p,n)+1)
#define BLOCK_OWNER(j,p,n) (((p)*((j)+1)-1)/(n))

const int n = 50;

int check(long long val, long long l, long long r) {
    int isPrime = 1;
    for (long long i = l; i <= r && i < val; i++) {
        if (val % i == 0) {
            isPrime = 0;
        }
    }
    return isPrime; 
}

void solve(long long p, long long id) {
    long long base = 2;
    for (int i = 0; i < n; i++) {
        base *= 2;
        long long lbase = base - 1;
        long long block = sqrt(lbase);
        long long l = BLOCK_LOW(id, p, block) + 2;
        long long r = BLOCK_HIGH(id, p, block) + 2;
        int isPrime = check(lbase, l, r);
        int globalIsPrime;
        MPI_Reduce(&isPrime, &globalIsPrime, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
        
        if (id == 0 && globalIsPrime) {
            cout << lbase * base / 2 << endl;
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
    solve(p, id);
    time += MPI_Wtime();
    MPI_Reduce(&time, &maxTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    if (id == 0) {
        printf ("%d processes: %.9f seconds\n", p, maxTime);
    }
    MPI_Finalize();
    return 0;
}

