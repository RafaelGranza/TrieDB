#pragma once

#include <string>
#include <map>
#include <concepts>

template<typename T>
concept IsMemtableContainer = requires(T v, const std::string& k, const std::string& val) {
    { v.insert(k, val) };
    { v.get(k) } -> std::same_as<std::string>;
    { v.flush() } -> std::same_as<std::map<std::string, std::string>>;
    { v.size() } -> std::same_as<uint64_t>;
};

template<IsMemtableContainer CONTAINER>
class Memtable {
    CONTAINER container;
public:
    Memtable() = default;
    void insert(const std::string& key, const std::string& value) {
        container.insert(key, value);
    }
    void update(const std::string& key, const std::string& value) {
        container.update(key, value);
    }

    void remove(const std::string& key) {
        container.remove(key);
    }

    bool count(const std::string& key) {
        return container.count(key);
    }

    std::string get(const std::string& key) {
        return container.get(key);
    }

    [[nodiscard]] std::map<std::string, std::string> flush() {
        auto data = container.flush();
        container.reset();
        return data;
    }

    void reset() {
        container.reset();
    }

    uint64_t size() {
        return container.size();
    }
};