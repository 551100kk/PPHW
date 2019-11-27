#include <bits/stdc++.h>
using namespace std;

#include "mpi.h"

#define BLOCK_LOW(id,p,n)  ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) (BLOCK_HIGH(id,p,n)-BLOCK_LOW(id,p,n)+1)
#define BLOCK_OWNER(j,p,n) (((p)*((j)+1)-1)/(n))

const int n = 1000000;
const int d = 50;
const int base = 100000000;

int *calc(int p, int id) {
    int start = BLOCK_LOW(id, p, n) + 1;
    int end = BLOCK_HIGH(id, p, n) + 1;

    int *val = new int[d];
    for (int i = start; i <= end; i++) {
        long long now = 1;
        for (int j = 0; j < d && now; j++) {
            val[j] += now / i;
            now %= i;
            now *= base;
        }
        for (int j = d - 1; j > 0; j--) {
            val[j - 1] += val[j] / base;
            val[j] %= base;
        }
    }
    
    return val;
}

void addarr(int *in, int *out, int *len, MPI_Datatype *dtype) {
    for (int i = 0; i < *len; i++) {
        out[i] += in[i];
    }
    for (int i = d - 1; i > 0; i--) {
        out[i - 1] += out[i] / base;
        out[i] %= base;
    }
}

void solve(int p, int id) {
    MPI_Op arrsum;
    MPI_Op_create((MPI_User_function *) addarr, 1, &arrsum);

    int *val = calc(p, id);
    int *sum = new int[d];
    MPI_Reduce(val, sum, d, MPI_INT, arrsum, 0, MPI_COMM_WORLD);

    if (id == 0) {
        puts("Python Decimal:\t 14.392726722865723631381127493188587676644800013744311653418433045812958507517995003568298175947219100708359952136079812900264164102586930094633006200549611666639142755843266541572197307829288195140937");
        printf("Our:\t\t %d.", sum[0]);
        for (int i = 1; i < d; i++) {
            printf("%08d", sum[i]);
        }
        puts("");    
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

