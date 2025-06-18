# h5pcc hello.c -o hello
mpicc 01_hello.c -o executables/hello -lhdf5_openmpi
mpicc 02_write.c -o executables/write -lhdf5_openmpi
mpicc 03_read.c  -o executables/read  -lhdf5_openmpi