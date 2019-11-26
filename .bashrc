# .bashrc

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

# Uncomment the following line if you don't like systemctl's auto-paging feature:
# export SYSTEMD_PAGER=

# User specific aliases and functions
module load gcc
module load intel/2018_u1

alias bd='mpiicpc main.cpp -o main'
alias rn='qsub run.sh'
alias dl='rm prob*'
alias qq='qstat -u r08922054'
