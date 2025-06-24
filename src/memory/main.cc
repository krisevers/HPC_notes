#include <iostream>

#include <balloc.h>

int main(int argc, char** argv) {

    balloc::instanceInfo info;
    balloc::instance instance(info);

    balloc::dataInfo dinfo;
    dinfo.name = "x";
    dinfo.size = 100;
    dinfo.mType = balloc::BA_DATA_SIZE_FIXED;
    dinfo.dType = balloc::BA_DATA_TYPE_DOUBLE;

    auto ptr = balloc::allocate(dinfo, instance);

    std::cout << instance.ptrs[0];
}