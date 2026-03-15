#pragma once

#include <unordered_map>
#include <map>
#include <string>

class HashMap {
    std::unordered_map<std::string, std::string> data;
    uint64_t sz = 0;
public:
    HashMap(){
        reset();
    }

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
        std::map<std::string, std::string> ordered_map;
        for (auto& [key, value] : data) {
            ordered_map.emplace(std::move(key), std::move(value));
        }
       return ordered_map;
    }

    void reset() {
        data.clear();
        sz = 0;
        data.reserve(1 << 20);
    }
    
    uint64_t size() const {
        return sz;
    }
};