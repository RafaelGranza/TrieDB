#include <cstring>
#include <cstdint>
#include <string>

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

    values[idx] = std::move(value);
}

template<class T, uint32_t MAX_NODES, uint32_t ALPHABET_SZ>
void Trie<T,MAX_NODES,ALPHABET_SZ>::update(const std::string& key, const T& value){

    auto idx = get_index(key);

    if(idx != -1)
        values[idx] = std::move(value);
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

template<class T, uint32_t MAX_NODES, uint32_t ALPHABET_SZ>
void Trie<T,MAX_NODES,ALPHABET_SZ>::reset(){

    std::memset(trie, 0, sizeof(trie));

    for(uint32_t i=0;i<MAX_NODES;i++)
        values[i] = T{};

    nodes_size = 0;
    size = 0;
}