#include <stdlib.h>

#include "utils.h"

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    hid_t plist_id, file_id;
    if (hpcn_openFile("data/hello.h5", &plist_id, &file_id) != HPCN_SUCCESS) {
        fprintf(stderr, "Opening file failed");
    }

    hid_t dataset_id = H5Dopen(file_id, "/mpi_data", H5P_DEFAULT);
    if (dataset_id < 0) {
        fprintf(stderr, "Opening dataset failed\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    hid_t dataspace_id = H5Dget_space(dataset_id);
    if (dataspace_id < 0) {
        fprintf(stderr, "Getting dataspace failed\n");
        H5Dclose(dataset_id);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int ndims = H5Sget_simple_extent_ndims(dataspace_id);
    hsize_t dims[ndims];
    H5Sget_simple_extent_dims(dataspace_id, dims, NULL);

    size_t total_elems = 1;
    for (int i = 0; i < ndims; ++i) total_elems *= dims[i];

    double* data = malloc(total_elems * sizeof(double));
    if (!data) {
        fprintf(stderr, "Memory allocation failed\n");
        H5Sclose(dataspace_id);
        H5Dclose(dataset_id);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if (H5Dread(dataset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, data) < 0) {
        fprintf(stderr, "Reading dataset failed\n");
        free(data);
        H5Sclose(dataspace_id);
        H5Dclose(dataset_id);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    printf("Dataset contents:\n");
    for (size_t i = 0; i < total_elems; ++i) {
        printf("%f ", data[i]);
    }
    printf("\n");

    free(data);
    H5Sclose(dataspace_id);
    H5Dclose(dataset_id);

    if (hpcn_closeFile(&plist_id, &file_id) != HPCN_SUCCESS) {
        fprintf(stderr, "Closing file failed");
    }

    MPI_Finalize();
}