#include <bits/stdc++.h>
using namespace std;

#include "mpi.h"

#define BLOCK_LOW(id,p,n)  ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) (BLOCK_HIGH(id,p,n)-BLOCK_LOW(id,p,n)+1)
#define BLOCK_OWNER(j,p,n) (((p)*((j)+1)-1)/(n))

int calc(int n, int p, int id) {
    int start = BLOCK_LOW(id, p, n);
    int end = BLOCK_HIGH(id, p, n);

    int pn = sqrt(n) + 1;
    vector<bool> is(pn + 1);
    vector<int> pri;
    for (int i = 2; i <= pn; i++) {
        if (is[i]) continue;
        pri.push_back(i);
        for (int j = i + i; j <= pn; j += i) {
            is[j] = 1;
        }
    }

    if (id == 0) {
        for (int x: pri) {
            printf("%d, ", x);
        }
        puts("");
    }
}

int main(int argc, char** argv) {
    int id;
    int p;
    int n = 1000000;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    MPI_Barrier(MPI_COMM_WORLD);
    double time = -MPI_Wtime();
    double maxTime;
    // Do something.
    int cnt = calc(n, p, id);
    int totalCnt;
    MPI_Reduce(&cnt, &totalCnt, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    time += MPI_Wtime();
    MPI_Reduce(&time, &maxTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    if (id == 0) {
        printf ("%d processes: %.9f seconds\n", p, maxTime);
    }
    MPI_Finalize();
    return 0;
}

