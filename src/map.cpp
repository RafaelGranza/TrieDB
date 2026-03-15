#pragma once

#include <map>
#include <string>

class Map {
    std::map<std::string, std::string> data;
    uint64_t sz = 0;
public:
    Map() = default;

    void insert(const std::string& key, const std::string& value) {
        data[key] = value;
        sz += key.size() + value.size();
    }

    void update(const std::string& key, const std::string& value) {
        auto it = data.find(key);
        if(it != data.end()) {
            sz -= key.size() + it->second.size();
            it->second = value;
            sz += key.size() + value.size();
        }
    }

    void remove(const std::string& key) {
        data.erase(key);
        sz -= key.size();
    }

    std::string get(const std::string& key) const {
        auto it = data.find(key);
        if(it != data.end())
            return it->second;
        return "";
    }

    bool count(const std::string& key) const {
        return data.find(key) != data.end();
    }

    std::map<std::string, std::string> flush() {
        return std::move(data);
    }

    void reset() {
        data.clear();
        sz = 0;
    }
    
    uint64_t size() const {
        return sz;
    }
};