#pragma once

#include <memory>
#include <string>
#include <optional>

namespace triedb {

class DB {
public:
    DB(const std::string& name);
    ~DB();

    void put(const std::string& key, const std::string& value);
    std::string get(const std::string& key);
    void remove(const std::string& key);
    void drop();
    void flush();
    uint64_t memtable_size();
    
private:

    struct Impl;
    std::string name;
    std::unique_ptr<Impl> impl;
};

}