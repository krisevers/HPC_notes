# HPC Notes

This repository provides a set of blueprints, notes, and code snippets for high-performance computing (HPC). The motivation behind this repository is to store and organize my own HPC workflows, tool and make them open source for others to use. The main content is a showcase of HPC tools, best practices, and their usage in applications.

## Content

### Scheduling
- Concepts: job scheduling, resource allocation, queueing, prioritization, backfilling, fair-share, preemption, gang scheduling, dependencies, node sharing/exclusivity.
- [Notes](notes/scheduling.md)

### Data Management
- Concepts: data formats, parallel I/O, metadata, data staging, locality, checkpointing, compression, replication, provenance, access control.
- [Notes](notes/data.md)

### Containerization
- Concepts: containers, images, registries, orchestration, reproducibility, isolation, user namespaces, bind mounts, MPI/GPU support.
- [Notes](notes/containerization.md)

### Parallelization & SIMD
- Concepts: data parallelism, vectorization, instruction sets (SSE, AVX, NEON, SVE), masking, gather/scatter, GPGPU.
- [Notes](notes/simd.md)


## Usage

- Browse the `notes/` directory for topic-specific markdown files.
- See code snippets and workflow examples in the relevant subfolders.
- Use the best practices and benchmarking tips to optimize your own HPC workflows.