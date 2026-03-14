#pragma once

#include <string>
#include <cstdint>
#include <map>

template<class T, uint32_t MAX_NODES = 1<<20, uint32_t ALPHABET_SZ = 1<<8>
class Trie {

    uint32_t trie[MAX_NODES][ALPHABET_SZ];
    T values[MAX_NODES];

    uint32_t nodes_size;
    uint64_t sz;

    int64_t get_index(const std::string& key);

public:

    Trie();

    void insert(const std::string& key, const T& value);

    void update(const std::string& key, const T& value);

    void remove(const std::string& key);

    bool count(const std::string& key);

    T get(const std::string& key);

    std::map<std::string, T> flush();

    void reset();

    uint64_t size();
};

#include "trie.inl"