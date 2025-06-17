#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {

    int size;
    int rank;

    if ( MPI_Init(&argc, &argv) != MPI_SUCCESS ) {
        fprintf(stderr, "MPI_Init() failed");
        return EXIT_FAILURE;
    }
    if( MPI_Comm_size(MPI_COMM_WORLD, &size) != MPI_SUCCESS ) {
        fprintf(stderr, "MPI_Comm_size() failed");
        return EXIT_FAILURE;
    }

    if ( MPI_Comm_rank(MPI_COMM_WORLD, &rank) != MPI_SUCCESS) {
        fprintf(stderr, "MPI_Comm_rank() failed");
        return EXIT_FAILURE;
    }

    fprintf(stdout, "Hello, I am rank %d/%d\n", rank, size);

    MPI_Finalize();

    return EXIT_SUCCESS;

}