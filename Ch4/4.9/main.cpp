#include <bits/stdc++.h>
using namespace std;

#include "mpi.h"

#define BLOCK_LOW(id,p,n)  ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) (BLOCK_HIGH(id,p,n)-BLOCK_LOW(id,p,n)+1)
#define BLOCK_OWNER(j,p,n) (((p)*((j)+1)-1)/(n))

const int n = 1000000;
const int gapBound = 500;

int calc(int p, int id) {
    int start = BLOCK_LOW(id, p, n) + 1;
    int end = BLOCK_HIGH(id, p, n) + 1;

    int pn = sqrt(n) + 1;
    vector<bool> is(pn + 1);
    vector<bool> notPrime(end - start + 1 + gapBound);
    for (int i = 2; i <= pn; i++) {
        if (is[i]) continue;
        for (int j = i + i; j <= pn; j += i) {
            is[j] = 1;
        }
        for (int j = max(i * i, (start + i - 1) / i * i); j <= end + gapBound; j += i) {
            if (i == j) continue;
            notPrime[j - start] = 1;
        }
    }
    int gap = 1;
    for (int i = max(start, 3); i <= end; i++) {
        if (notPrime[i - start]) continue;
        for (int j = i + 2; j <= end + gapBound; j += 2) {
            if (notPrime[j - start]) continue;
            gap = max(gap, j - i);
            break;
        }
    }
    return gap;
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
    
    // PP start
    int gap = calc(p, id);
    int maxgap;
    MPI_Reduce(&gap, &maxgap, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    // PP end

    time += MPI_Wtime();
    MPI_Reduce(&time, &maxTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    if (id == 0) {
        printf("Maxgap: %d\n", maxgap);
        printf ("%d processes: %.9f seconds\n", p, maxTime);
    }
    MPI_Finalize();
    return 0;
}

