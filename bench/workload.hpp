#pragma once

#include <cstdint>
#include <string>
#include <fstream>


struct Workload {
    uint32_t num_ops;
    uint32_t key_size;
    uint32_t value_size;
    
    enum class TYPE: uint8_t {
        FILLSEQ,
        FILLRAND,
        READRAND,
    };

    TYPE type;

    Workload(const std::string& path) {
        std::ifstream in(path);
        if(!in){
            throw std::runtime_error(path + " does not name a valid file.");
        }
        
        int type_int;
        in >> num_ops >> key_size >> value_size >> type_int;

        type = static_cast<TYPE>(type_int);
    }

};