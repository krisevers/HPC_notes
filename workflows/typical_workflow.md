# A typical HPC workflow
When developing HPC workflows at some point you would want to move you code and data to a the HPC cluster.

## Login to Cluster

Many clusters use *ssh*. Before this is possible a *ssh* key is required.

Login to the cluster
```bash
ssh <username>@<cluster-address> # e.g. ssh aeinstein@daint.cscs.ch
```
To experiment use a `$SCRATCH`. Such folders will be deleted or remoted after some time.
```bash
cd $SCRATCH
```

## Moving Code
There are several options for moving from a local device to a cluster:
1. Use `git` (e.g. through GitHub): `git clone <repository>.git` on the cluster if possible.
2. Containerize the application and upload a place like `docker hub` which can be accessed from the cluster.
```bash
# on local device
docker build -t <username>/<project>:<tag> . -f - < docker/Dockerfile
docker push <username>/<project>:<tag>

# on cluster
docker pull docker://<username>/<project>:<tag>
singularity pull docker://<username>/<project>:<tag>
```
3. use secure copy command `scp` to securely move the code to the cluster.
```bash
scp <code> <username>@<cluster-address>
```

## Moving data
Often data files (especially on the cluster) are too large to move to the local device using `git` tools.
Use `scp` instead:

```bash
# move data to server from local device
scp file.dat <username>@<cluster-address>:~/                    # from outside cluster
scp file.dat <username>@<cluster-address>:~/$SCRATCH            # from outside cluster

# move data from server to local device
scp <username>@<cluster-address>:~/file.dat ./data              # from outside cluster
scp <username>@<cluster-address>:~/$SCRATHC/file.dat ./data     # from outside cluster
```

## Running Jobs
On many HPC clusters singularity and slurm are installed and you can use load the `singularity` module and pull the within the `srun` command, to schedule the execution of the 
```bash
module load singularity

# using docker hub
srun -C mc --account=<acountname> singularity pull docker://<username>/<project>:<tag>
```

`slurm` takes a list of arguments which one can define in a `run.sh` file:

```bash
#!/bin/bash
# --- run.sh ---

#SBATCH --job-name                  # specify job name
#SBATCH --time=01:00:00             # specify runtime request
#SBATCH --mem=1G                    # specify memory request
#SBATCH --array=1-100               # spacify task parameter range for the job

# load required modules
module load <requirement>

# run executable or script of interest with optional task specific parameter
./<executable/script> $SLURM_ARRAY_TASK_ID
```

Then use `sbatch` to run a batch job.
```batch
sbatch run.sh               # execute with the procedure defined in run.sh
squeue -u ${USER}           # check status
sacct -j <job_id>_<task_id> # job and task information
scancel <job_id>            # cancel job
tail -n 100 slurmlogfile    # check log file
```
For more information on `slurm` commands and job scheduling go to the extended documentation: [https://slurm.schedmd.com/documentation.html](https://slurm.schedmd.com/documentation.html)