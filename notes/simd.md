# SIMD

Single Instruction Multiple Data (SIMD) is a technique where a single instruction operates on multiple data points at once.

## Key Concepts

- **Data parallelism:** Apply the same operation to multiple data elements.
- **Vector registers:** Hold multiple data elements (e.g., 128/256/512 bits wide).
- **Alignment:** Data should be aligned in memory for efficient SIMD access.
- **Auto-vectorization:** Compilers can sometimes convert scalar code to SIMD automatically.
- **Manual vectorization:** Use intrinsics or explicit vector types for more control.
- **Instruction sets:** SSE, AVX (x86), NEON (ARM), AltiVec (PowerPC), SVE (ARM).
- **Masking:** Selectively enable/disable operations on elements in a vector.
- **Gather/scatter:** Load/store non-contiguous data efficiently.

## References
- [*Talk*: Golden Age for Computer Architecture](https://cacm.acm.org/research/a-new-golden-age-for-computer-architecture/)
- [*Article*: Designing a SIMD algorithm from Scratch](https://mcyoung.xyz/2023/11/27/simd-base64/)
- [*Article*: The messy reality of SIMD (vector) functions](https://johnnysswlab.com/the-messy-reality-of-simd-vector-functions/)
- [*Article*: Running Markov Chain Monte Carlo on Modern Hardware and Software](https://arxiv.org/html/2411.04260v1)
- [*Article*: Untangling Lifetimes: The Arena Allocator](https://www.rfleury.com/p/untangling-lifetimes-the-arena-allocator)
- [*Article*: Calling CUDA in 3000 Words](https://ashvardanian.com/posts/less-wrong-cuda-hello-world/)
- [*Repo*: Exo Language](https://github.com/exo-lang/exo/tree/main)
- [*Repo*: Parallel C++](https://github.com/CoffeeBeforeArch/parallel_cpp/tree/main)


## Tools & Libraries

- **Zig:** Create a SIMD vector using the `@Vector()` function.
    - no native async available
    - `MultiArrayList` is a native Struct-of-Arrays container.
    - native C integration.
- **SYCL:** Heterogeneous programming, supports explicit SIMD types (CPU/GPU).
    - compiler: https://github.com/AdaptiveCpp/AdaptiveCpp
- **CUDA:** GPU programming, supports vectorized operations and warp-level parallelism.
    - NVIDIA exclusive
- **HIP:** C++ Runtime API and Kernel Language that allows developers to create portable applications for AMD and NVIDIA GPUs from single source code.
- **OpenMP:** SIMD directives for C/C++/Fortran.
- **Intel Intrinsics:** Fine-grained SIMD control in C/C++.
- **Eigen:** C++ linear algebra, auto-vectorizes many operations.
    - not transparent.
    - auto-vectorization not perfect.
- **Julia:** Packages like `LoopVectorization.jl`, `SIMD.jl`.
- **NumPy:** Uses SIMD internally for many operations.
- **SIMDe:** Portable SIMD intrinsics for C/C++.
- **Vc:** C++ library for portable explicit SIMD programming.
- **Boost.SIMD:** C++ SIMD abstraction layer.

## Benchmarking

- **Execution time:** Wall-clock time for a function or kernel.
- **Throughput:** Data processed per unit time (FLOPS, GB/s).
- **Resource utilization:** Efficiency of registers, memory bandwidth, etc.

### Benchmarking Tools

- **Microbenchmarks:** Isolate SIMD code for focused testing.
    - **Google Benchmark** C++ library for benchmarking code snippets.
- **Profilers:** `perf`, Intel VTune, NVIDIA Nsight, AMD uProf.
- **Python:** `timeit` for timing code snippets.
- **Compiler reports:** Use `-ftree-vectorizer-verbose` (GCC), `-Rpass=vector` (Clang) to check vectorization.

## Best Practices

- Compare SIMD vs scalar versions.
- Align and size data for SIMD width.
- Use compiler flags: `-O3 -march=native` (GCC/Clang).
- Inspect assembly.
- Profile and tune iteratively.
- Watch for memory bottlenecks and alignment issues.
- Prefer SoA (Structure of Arrays) over AoS (Array of Structures) for better vectorization.