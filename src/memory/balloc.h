#ifndef BALLOC_H
#define BALLOC_H

#include <iostream>
#include <vector>
#include <variant>

namespace balloc {

    // device information
    struct deviceInfo {
        char**      name;
        char*       os;
        int         num_cpu_cores;
        int         num_gpu_cores;
        int         num_cpu_nodes;
        int         num_gpu_nodes;
    };

    // instance information
    struct instanceInfo {

    };

    // data information
    typedef enum {
        BA_DATA_SIZE_FIXED,
        BA_DATA_SIZE_VARIABLE,
    } BA_DATA_SIZE_INFO;

    typedef enum {
        BA_DATA_TYPE_INT,
        BA_DATA_TYPE_FLOAT,
        BA_DATA_TYPE_DOUBLE,
    } BA_DATA_TYPE_INFO;

    struct dataInfo {
        const char* name;
        size_t      size;
        BA_DATA_SIZE_INFO mType;
        BA_DATA_TYPE_INFO dType;
    };

    class instance {
        
        public:
            std::vector<void*> ptrs;
            std::vector<size_t> sizes;

            instance(instanceInfo info) { }
    };

    void* allocate(dataInfo info, instance& inst) {
        void* ptr = new int[info.size];

        inst.ptrs.push_back(ptr);
        inst.sizes.push_back(info.size);

        return ptr;
    };

}


#endif BALLOC_H