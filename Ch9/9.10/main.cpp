#include <bits/stdc++.h>
using namespace std;

#include "mpi.h"

#define BLOCK_LOW(id,p,n)  ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) (BLOCK_HIGH(id,p,n)-BLOCK_LOW(id,p,n)+1)
#define BLOCK_OWNER(j,p,n) (((p)*((j)+1)-1)/(n))

const int n = 40;

int check(long long val, long long l, long long r) {
    for (long long i = l; i <= r; i++) {
        if (val % i == 0) {
            return 0;
        }
    }
    return 1; 
}

void solve(int p, int id) {
    long long base = 2;
    for (int i = 0; i < n; i++) {
        base *= 2;
        long long lbase = base - 1;
        long long l = 2;
        long long r = sqrt((long double) lbase) + 1;
        r = min(r, lbase - 1);
        long long newl = BLOCK_LOW((long long) id, (long long) p, r - l + 1) + l;
        long long newr = BLOCK_HIGH((long long) id, (long long) p, r - l + 1) + l;
        // if (id == 1) printf("%lld, %lld\n", newl, newr);
        int res = check(lbase, newl, newr);
        int finalRes;
        MPI_Reduce(&res, &finalRes, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
        if (id == 0 && finalRes) {
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

