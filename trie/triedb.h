#ifndef __TRIEDB_H__
#define __TRIEDB_H__
#include "trie_table.h"

class triedb
{
private:
    std::string source;
    trie_table tt;
    void build();
public:
    triedb();
    triedb(std::string source);
    ~triedb() {}
    
    void insert_table(const std::string tag);
    void insert_row(generic_class row);
    void insert_random_rows(generic_class row, unsigned number = 50);

    void update_row(generic_class row);
    void update_attribute(const std::string tag, const std::string id, const std::string name, const std::string value);

    void remove_table(const std::string tag);
    void remove_row(const std::string tag, const std::string id);

    generic_class get_row(const std::string tag, const std::string id);
    generic_class get_row(const std::string tag);
    std::vector<generic_class> get_all_rows(const std::string tag);
    std::string get_attribute(const std::string tag, const std::string id, const std::string name);
    std::string get_string(const std::string tag, const std::string id);
    std::string get_string(const std::string tag);
    std::vector<std::string> get_all_strings(const std::string tag);


};
#endif // __TRIEDB_H__