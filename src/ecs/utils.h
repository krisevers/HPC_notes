#include <stdlib.h>
#include <stdint.h>

typedef struct {
    uint16_t*   data;
    size_t      size;
    size_t      capacity;
} vec_i16;

typedef struct {
    vec_i16*  data;
    size_t    size;
    size_t    capacity;      
} mat_i16;

static vec_i16 vec_i16_malloc(size_t n) {
    vec_i16 vec;
    vec.data = (uint16_t*)malloc(n * sizeof(uint16_t *));
    vec.size = n;
    vec.capacity = n;
    return vec;
}

static void vec_i16_free(vec_i16 vec) {
    if (!vec.data) return;
    free(vec.data);
}

static mat_i16 mat_i16_malloc(size_t n, size_t m) {
    
}

static mat_i16 MatrixInt16(size_t n, size_t m) {
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