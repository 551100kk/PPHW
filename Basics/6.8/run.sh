#!/bin/sh
#PBS -P ACD108147
#PBS -N problem_6.8
#PBS -q ctest
#PBS -l select=1:ncpus=1:mpiprocs=2
#PBS -l place=scatter
#PBS -l walltime=00:00:10
#PBS -j n
module purge
module load intel/2018_u1
cd $PBS_O_WORKDIR
echo $PBS_O_WORKDIR
date
mpirun ./main
