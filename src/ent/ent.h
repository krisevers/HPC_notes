#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>

#include "utils.h"

typedef enum {
    RESULT_SUCCESS,
    RESULT_FAILURE
} RESULT;

typedef enum {
    DTYPE_INT,
    DTYPE_FLOAT,
    DTYPE_DOUBLE
} DTYPE;

typedef enum {
    MTYPE_FIXED,
    MTYPE_VARIABLE,
} MTYPE;

struct ComponentInfo {
    DTYPE dtype;
    MTYPE mtype;
};

typedef struct
{
    uint16_t size;
    uint16_t capacity;
    uint16_t** relations;
} Model;

static size_t ID(void) {
    static size_t counter = 0;
    return counter++;
}

RESULT init(Model* model, size_t capacity) {
    model->size = 0;
    model->capacity = capacity;
    model->relations = MatrixInt16(model->capacity, model->capacity);
    return RESULT_SUCCESS;
}

RESULT Model_free(Model* model) {
    MatrixInt16_free(model->relations, model->capacity);
    return RESULT_SUCCESS;
}

size_t create(Model* model) {
    model->size++;
    return ID();
}


void give(Model* model, size_t parent, size_t child, uint16_t copies ) {
    model->relations[parent][child] = copies;
}

size_t assemble(Model* model, size_t num_args, ...) {
    va_list args;
    va_start(args, num_args);

    size_t new_id = ID();

    for (size_t i = 0; i < num_args; ++i) {
        size_t arg = va_arg(args, size_t);
        printf("\n\n%zu\n\n", arg);
        model->relations[new_id][arg] = 1;
    }

    va_end(args);
    return new_id;
}


void print(Model* model) {
    printf("parent -> child : copies:\n");
    for (uint16_t i = 0; i < model->capacity; ++i) {
        for (uint16_t j = 0; j < model->capacity; ++j) {
            if (model->relations[i][j] != 0) {
                printf("%u -> %u : %u\n", i, j, model->relations[i][j]);
            }
        }
    }
}



RESULT allocate() {


    return RESULT_SUCCESS;
}