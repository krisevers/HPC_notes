#include <stdlib.h>
#include <stdint.h>

// static uint16_t* VectorInt16(size_t n) {
//     return (uint16_t*)malloc(n * sizeof(uint16_t *));
// }

// static void VectorInt16_free(uint16_t* array) {
//     if (!array) return;
//     free(array);
// }

static uint16_t** MatrixInt16(size_t n, size_t m) {
    uint16_t **array = (uint16_t **)malloc(n * sizeof(uint16_t *));
    if (!array) return NULL;
    for (size_t i = 0; i < n; ++i) {
        array[i] = (uint16_t *)calloc(n, sizeof(uint16_t));
        if (!array[i]) {
            // Free already allocated rows on failure
            for (size_t j = 0; j < i; ++j) free(array[j]);
            free(array);
            return NULL;
        }
    }
    return array;
}

static void MatrixInt16_free(uint16_t **array, size_t n) {
    if (!array) return;
    for (size_t i = 0; i < n; ++i) {
        free(array[i]);
    }
    free(array);
}