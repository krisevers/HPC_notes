#include "utils.h"

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    hid_t plist_id, file_id;
    if (hpcn_openFile("data/hello.h5", &plist_id, &file_id) != HPCN_SUCCESS) {
        fprintf(stderr, "Opening file failed");
    }

    if (hpcn_closeFile(&plist_id, &file_id) != HPCN_SUCCESS) {
        fprintf(stderr, "Closing file failed");
    }

    MPI_Finalize();
}