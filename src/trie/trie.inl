#include <cstring>
#include <cstdint>
#include <string>
#include "trie.h"

template<class T, uint32_t MAX_NODES, uint32_t ALPHABET_SZ>
int64_t Trie<T,MAX_NODES,ALPHABET_SZ>::get_index(const std::string& key){

    uint32_t idx = 0;

    for(const auto& c : key){
        auto k = static_cast<uint8_t>(c);

        if(trie[idx][k] == 0)
            return -1;

        idx = trie[idx][k];
    }

    return idx;
}

template<class T, uint32_t MAX_NODES, uint32_t ALPHABET_SZ>
Trie<T,MAX_NODES,ALPHABET_SZ>::Trie(){
    reset();
}

template<class T, uint32_t MAX_NODES, uint32_t ALPHABET_SZ>
void Trie<T,MAX_NODES,ALPHABET_SZ>::insert(const std::string& key, const T& value){

    uint32_t idx = 0;

    for(const auto& c : key){
        auto k = static_cast<uint8_t>(c);

        if(trie[idx][k] == 0)
            trie[idx][k] = ++nodes_size;

        idx = trie[idx][k];
    }
    
    if(values[idx] != T{}){
        sz -= values[idx].size();
    }
    
    values[idx] = std::move(value);
    sz += value.size();
}

template<class T, uint32_t MAX_NODES, uint32_t ALPHABET_SZ>
void Trie<T,MAX_NODES,ALPHABET_SZ>::update(const std::string& key, const T& value){

    auto idx = get_index(key);

    if(idx != -1){
        sz -= values[idx].size();
        values[idx] = std::move(value);
        sz += values[idx].size();
    }
}

template<class T, uint32_t MAX_NODES, uint32_t ALPHABET_SZ>
void Trie<T,MAX_NODES,ALPHABET_SZ>::remove(const std::string& key){

    auto idx = get_index(key);

    if(idx != -1)
        values[idx] = T{};
}

template<class T, uint32_t MAX_NODES, uint32_t ALPHABET_SZ>
bool Trie<T,MAX_NODES,ALPHABET_SZ>::count(const std::string& key){

    return get_index(key) != -1;
}

template<class T, uint32_t MAX_NODES, uint32_t ALPHABET_SZ>
T Trie<T,MAX_NODES,ALPHABET_SZ>::get(const std::string& key){

    auto idx = get_index(key);

    if(idx == -1)
        return nullptr;

    return values[idx];
}

template <class T, uint32_t MAX_NODES, uint32_t ALPHABET_SZ>
inline std::map<std::string, T> Trie<T, MAX_NODES, ALPHABET_SZ>::flush()
{
    std::string key = "";
    std::map<std::string, T> result;
    auto dfs = [&](auto&& self, uint32_t idx) -> void {
        if(values[idx] != T{}) result[key] = values[idx];
        for(int c = 0; c < ALPHABET_SZ; c++){
            auto next = trie[idx][c];
            if(next != 0){
                key.push_back(static_cast<char>(c));
                self(self, next);
                key.pop_back();
            }
        }
    };

    dfs(dfs, 0);
    return result;
}


template <class T, uint32_t MAX_NODES, uint32_t ALPHABET_SZ>
void Trie<T, MAX_NODES, ALPHABET_SZ>::reset()
{

    std::memset(trie, 0, sizeof(trie));

    for(uint32_t i=0;i<MAX_NODES;i++)
        values[i] = T{};

    nodes_size = 0;
    sz = 0;
}

template <class T, uint32_t MAX_NODES, uint32_t ALPHABET_SZ>
inline uint64_t Trie<T, MAX_NODES, ALPHABET_SZ>::size()
{
    return this->sz;
}
