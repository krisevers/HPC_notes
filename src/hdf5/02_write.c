#include "utils.h"

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    hid_t plist_id, file_id;
    if (hpcn_openFile("hello.h5", &plist_id, &file_id) != HPCN_SUCCESS) {
        fprintf(stderr, "Opening file failed");
    }

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Each process creates its own data
    int data = rank * 10;

    // Create a dataspace for a 1D array of size 'size'
    hsize_t dims[1] = {size};
    hid_t dataspace_id = H5Screate_simple(1, dims, NULL);

    // Create the dataset
    hid_t dataset_id = H5Dcreate(file_id, "mpi_data", H5T_NATIVE_INT, dataspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // Each process writes its data to its own position
    hsize_t start[1] = {rank};
    hsize_t count[1] = {1};
    hid_t memspace_id = H5Screate_simple(1, count, NULL);
    H5Sselect_hyperslab(dataspace_id, H5S_SELECT_SET, start, NULL, count, NULL);

    hid_t xfer_plist = H5Pcreate(H5P_DATASET_XFER);
    H5Pset_dxpl_mpio(xfer_plist, H5FD_MPIO_INDEPENDENT);

    H5Dwrite(dataset_id, H5T_NATIVE_INT, memspace_id, dataspace_id, xfer_plist, &data);

    // Cleanup
    H5Pclose(xfer_plist);
    H5Sclose(memspace_id);
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);

    if (hpcn_closeFile(&plist_id, &file_id) != HPCN_SUCCESS) {
        fprintf(stderr, "Closing file failed");
    }

    MPI_Finalize();
}