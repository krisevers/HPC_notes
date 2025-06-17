# Installation HPC Tools

## Singularity
1. install system dependencies.
2. install `go`.
3. install `singularity`

All implemented in [`install_singularity.sh`](./src/install/install_singularity.sh). Execute to install system dependencies, `go` and `singularity` on the host (be sure to check the right versions).

## Slurm
1. install `munge` for authentication ([`install_munge.sh`](./src/install/install_munge.sh)).
2. install `slurm` for job scheduling ([`install_slurm.sh`](.src/install/install_slurm.sh)).

## OpenMPI
1. install OpenMPI (`ompi`) for parallel compute ([`install_ompi`](./src/install/install_ompi.sh)).