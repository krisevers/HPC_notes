#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

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

typedef struct {
    uint16_t begin;
    uint16_t end;
} View;

typedef struct
{
    uint16_t size;
    uint16_t capacity;
    uint16_t *copies;
    View **views;
} Model;

static size_t ID(void) {
    static size_t counter = 0;
    return counter++;
}

Model init(size_t capacity) {
    Model model;
    model.size = 0;
    model.capacity = capacity;
    model.copies = (uint16_t*)malloc(capacity * sizeof(uint16_t));
    model.views = (View **)malloc(capacity * sizeof(View *));
    for (size_t i = 0; i < capacity; ++i) { 
        model.views[i] = (View *)malloc(capacity * sizeof(View));
        for (size_t j = 0; j < capacity; ++j) {
            model.views[i][j].begin = 0;
            model.views[i][j].end = 0;
        }
    }
    return model;
}

size_t create(Model* model) {
    model->size++;
    return ID();
}


void give(Model* model, size_t parent, size_t child, uint16_t copies ) {
    uint16_t current = model->copies[child];
    
    View temp = {
        .begin = current,
        .end   = current+copies 
    };

    model->copies[child] += copies;
    model->views[parent][child] = temp;
}


size_t assemble() {

    return ID();
}






RESULT allocate() {


    return RESULT_SUCCESS;
}