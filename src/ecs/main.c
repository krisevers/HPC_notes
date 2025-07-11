#include "ecs.h"


int main(int argc, char** argv) {
    
    Model m;
    if (init(&m, 100) != RESULT_SUCCESS) {
        fprintf(stderr, "Failed to initialize model\n");
        return 1;
    }

    size_t x = create(&m);
    size_t y = create(&m);
    size_t z = create(&m);

    size_t p1 = create(&m);
    size_t p2 = create(&m);
    
    printf("==== components ====\n");
    printf("x = %zu\n", x);
    printf("y = %zu\n", y);
    printf("z = %zu\n", z);
    printf("p1 = %zu\n", p1);
    printf("p2 = %zu\n", p2);

    give(&m, p1, x, 10);
    give(&m, p2, x, 100); 
    give(&m, p2, z, 100);

    size_t cloud = assemble(&m, 2, p1, p2);

    printf("==== relations ====\n");
    print(&m);


    printf("cloud = %zu\n", cloud);

    // create methods to assemble model
    // assemble method
    // grow and shrink methods
}