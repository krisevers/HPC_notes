#!/bin/bash -l
#SBATCH --job-name hello
#SBATCH -N $NNODES          # total number of nodes
#SBATCH --time=00:05:00     # max execution time

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

module load singularity

export TF_CPP_MIN_LOG_LEVEL="3"
export DISPLAY=:0

srun singularity run --nv
