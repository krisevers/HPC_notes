# Scheduling

Scheduling in HPC determines how computational tasks are assigned to resources (CPUs, GPUs, nodes) to maximize efficiency and throughput.

## Key Concepts

- **Job scheduling:** Assigning jobs to resources in a cluster.
- **Resource allocation:** Reserving CPUs, memory, GPUs, etc., for jobs.
- **Queueing:** Jobs wait in queues until resources are available.
- **Prioritization:** Jobs may have different priorities or QoS levels.
- **Backfilling:** Running smaller jobs ahead of large jobs to improve utilization.
- **Fair-share:** Allocating resources based on user/group quotas.
- **Preemption:** Suspending lower-priority jobs for higher-priority ones.
- **Gang scheduling:** Coordinating parallel tasks to run simultaneously.
- **Node sharing/exclusivity:** Multiple jobs per node vs. exclusive access.
- **Dependencies:** Jobs may depend on the completion of others.

## References
- [*Repo*: Exo Language](https://arxiv.org/pdf/2411.07211)

## Tools & Libraries

- **Slurm:** Widely used open-source workload manager.
    - https://slurm.schedmd.com/
- **Kubernetes:** Container orchestration, sometimes used for HPC workloads.
- **Snakemake/Nextflow:** Workflow managers with job scheduling integration.

## Benchmarking

- **Job throughput:** Number of jobs completed per unit time.
- **Wait time:** Time jobs spend in the queue.
- **Resource utilization:** Percentage of CPU, memory, GPU used.
- **Makespan:** Total time to complete a set of jobs.
- **Turnaround time:** Submission to completion time for jobs.
- **Scheduler overhead:** Time spent in scheduling logic vs. computation.

### Benchmarking Tools

- **Slurm accounting tools:** `sacct`, `squeue`, `sprio`, `sreport`.
- **Jobstats:** Collects job-level resource usage.
- **XDMoD:** HPC metrics and analytics platform.
- **Grafana/Prometheus:** Cluster monitoring and visualization.
- **Custom scripts:** Parse scheduler logs for queue/wait/usage stats.
- **Scheduler simulators:** SimGrid, Batsim for testing scheduling algorithms.

## Best Practices
