#include "ent.h"


int main(int argc, char** argv) {
    
    Model m = init(100);

    size_t x = create(&m);
    size_t y = create(&m);
    size_t z = create(&m);

    size_t p1 = create(&m);
    size_t p2 = create(&m);
    
    printf("==== components ====");
    printf("x = %zu\n", x);
    printf("y = %zu\n", y);
    printf("z = %zu\n", z);
    printf("p1 = %zu\n", p1);
    printf("p2 = %zu\n", p2);

    give(&m, p1, x, 10);
    give(&m, p2, x, 100);

    printf("p1:\n");
    printf("%hu\n", m.views[p1][x].begin);
    printf("%hu\n", m.views[p1][x].end);
    printf("p2:\n");
    printf("%hu\n", m.views[p2][x].begin);
    printf("%hu\n", m.views[p2][x].end);

    // create methods to assemble model
    // assemble method
    // grow and shrink methods
}