#include <bits/stdc++.h>
using namespace std;

#include "mpi.h"

int main(int argc, char** argv) {
    int id;
    int psize;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &psize);

    int dataSize = 100000;
    int maxRound = 20;
    int avgRound = 10;
    int delRound = 2;

    char *arr = new char[dataSize * maxRound];
    MPI_Status status;

    if (id == 0) {
        for (int round = 1; round <= maxRound; round++) {
            printf("[Info] Round %d started\n", round);
            // get 5 average time
            vector<double> timeArr;
            double avgTime = 0;
            int avgCnt = 0;
            for (int i = 0; i < avgRound; i++) {
                double time = -MPI_Wtime();
                MPI_Send(arr, dataSize * round, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
                MPI_Recv(arr, dataSize * round, MPI_CHAR, 1, 1, MPI_COMM_WORLD, &status);
                time += MPI_Wtime();
                // printf("[Run #%d] Receive size: %d, time elapse %10f\n", i, dataSize * round, time / 2);
                timeArr.push_back(time / 2);
            }
            sort(timeArr.begin(), timeArr.end());
            for (int i = delRound; i < avgRound - delRound; i++) {
                avgTime += timeArr[i];
                avgCnt += 1;
            }
            avgTime /= avgCnt;
            printf("[Average] Receive size: %d, time elapse %.9f\n", dataSize * round, avgTime);
        }
    } else {
        for (int round = 1; round <= maxRound; round++) {
            for (int i = 0; i < avgRound; i++) {
                MPI_Recv(arr, dataSize * round, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
                MPI_Send(arr, dataSize * round, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
            }
        }
    }

    fflush(stdout);
    MPI_Finalize();
    return 0;
}
