#include <hdf5/openmpi/hdf5.h>

/*
    High-Performance Computing Notes (hpcn) utilities.
*/

typedef enum {
    HPCN_SUCCESS,
    HPCN_FAILURE
} HPCN_RESULT;

HPCN_RESULT hpcn_openFile(const char* name, hid_t* plist_id, hid_t* file_id) {
    *plist_id = H5Pcreate(H5P_FILE_ACCESS);
    H5Pset_fapl_mpio(*plist_id, MPI_COMM_WORLD, MPI_INFO_NULL);

    *file_id = H5Fcreate(name, H5F_ACC_TRUNC, H5P_DEFAULT, *plist_id);
    return (*file_id >= 0) ? HPCN_SUCCESS : HPCN_FAILURE;
}

HPCN_RESULT hpcn_closeFile(hid_t* plist_id, hid_t* file_id) {
    H5Fclose(*file_id);
    H5Pclose(*plist_id);

    return HPCN_SUCCESS;
}