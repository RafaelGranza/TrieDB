#pragma once

#include <string>
#include <fstream>
#include "memtable.cpp"



enum class OP : uint8_t {
    INSERT,
    REMOVE
};

template<typename T>
class WAL {
    std::string path;
    std::fstream wal;

    void open();
public:
    WAL() = default;
    explicit WAL(const std::string& path);
    void operator()(const std::string& path);
    void load_memtable(Memtable<T>& memtable);
    void append(OP op, const std::string& key, const std::string& value = "");
    void reset();
};

#include "wal.inl"