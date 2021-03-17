#ifndef __TRIE_ROW_H__
#define __TRIE_ROW_H__
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include "../model/generic_class.h"
#include "utils.h"

class trie_row
{
private:
    
    std::map<char, unsigned> nodes[10000];
    std::map<unsigned, std::string> paths;
    unsigned number_of_nodes = 0;
    void remove_row(const std::string id);
    std::string create_row(const std::string id, generic_class row);
    void build();
public:
    std::string source;
    trie_row() {}
    trie_row(std::string source);
    ~trie_row() {}
    void insert(const std::string id, const generic_class row);
    void load(const std::string id, const std::string path, bool begin = false);
    generic_class get(const std::string id);
    std::vector<generic_class> get_all();
    generic_class pattern();
    void update(const std::string id, const generic_class row);
    void remove(const std::string id);
};
#endif // __TRIE_ROW_H__