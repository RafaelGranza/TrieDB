#pragma once

#include <string>
#include <fstream>
#include "../trie/trie.h"

enum class OP : uint8_t {
    INSERT,
    REMOVE
};

class WAL {
    std::string path;
    std::fstream wal;

    void open();
    std::string build_path(const std::string& path);

public:
    WAL() = default;
    explicit WAL(const std::string& path);
    void operator()(const std::string& path);
    void load_memtable(Trie<std::string>& trie);
    void append(OP op, const std::string& key, const std::string& value = "");
};
