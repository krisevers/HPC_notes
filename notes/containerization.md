# Containerization

Containerization in HPC enables packaging applications and their dependencies into portable, reproducible environments that can run consistently across different systems.

## Key Concepts

- **Containers:** Isolated environments for applications.
- **Images:** Snapshots of container file systems, including code and dependencies.
- **Registries:** Repositories for storing and sharing container images.
- **Orchestration:** Managing deployment and scaling of containers (e.g., Kubernetes).
- **Reproducibility:** Ensuring consistent environments across runs and systems.
- **Isolation:** Separating applications and dependencies from the host system.
- **User namespaces:** Running containers without root privileges.
- **Bind mounts/volumes:** Accessing host filesystems from containers.
- **MPI support:** Running parallel applications inside containers.
- **GPU support:** Accessing accelerators from within containers.

## Tools & Libraries

- **Docker:** Widely used container platform (not always supported on HPC).
- **Podman:** Daemonless, rootless container engine (Docker-compatible).
- **Singularity/Apptainer:** Designed for HPC, supports unprivileged users and MPI (Docker-compatible).
- **Charliecloud:** Lightweight, user-space containers for HPC.
- **Shifter:** Container runtime for HPC environments.
- **Enroot:** NVIDIA-focused container runtime for HPC and AI workloads.
- **Kubernetes:** Container orchestration platform.
- **NVIDIA Container Toolkit:** GPU support for containers.

## Benchmarking

- **Startup time:** Time to launch a containerized application.
- **Overhead:** Performance difference vs. native execution.
- **I/O performance:** File system and network access from containers.
- **MPI/GPU performance:** Parallel and accelerator performance inside containers.
- **Scalability:** Running many containers concurrently.

### Benchmarking Tools

- **Hyperfine:** Command-line benchmarking tool for measuring startup/exec time.
- **fio:** I/O benchmarking inside containers.
- **OSU Micro-Benchmarks:** MPI performance testing in containers.
- **NVIDIA nvidia-smi:** GPU access and performance checks.
- **Custom scripts:** Compare native vs. containerized runs.

## Best Practices

- Use Singularity/Apptainer or Podman for HPC compatibility and security.
- Build minimal images with only required dependencies.
- Use bind mounts for large datasets and scratch space.
- Document container build and usage instructions.
- Automate image builds and updates.