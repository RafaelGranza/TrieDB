#pragma once

#include <memory>
#include <string>
#include <optional>

namespace triedb {

class DB {
public:
    DB(const std::string& path);
    ~DB();

    void put(const std::string& key, const std::string& value);
    std::string get(const std::string& key);
    void remove(const std::string& key);

private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

}