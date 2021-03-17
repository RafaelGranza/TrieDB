#ifndef __TRIE_TABLE_H__
#define __TRIE_TABLE_H__
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>
#include "trie_row.h"

class trie_table
{
private:
    std::string source;
    std::map<char, unsigned> nodes[10000];
    std::map<unsigned, int> table_index;
    std::vector<trie_row> rows;
    unsigned number_of_nodes = 0;
    unsigned number_of_tables = 0;
    void build(); //TODO
public:
    trie_table() {}
    trie_table(std::string source);
    ~trie_table() {}
    void insert(const std::string tag);
    void load(const std::string tag);
    int get_index(const std::string tag);
    trie_row* get_trie_row(const std::string tag);
    void remove(const std::string tag); //TODO
};
#endif // __TRIE_TABLE_H__