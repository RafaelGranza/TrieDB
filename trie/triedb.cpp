#include "triedb.h"


triedb::triedb(std::string source) 
{
    this->source = source;
    this->build();
}

void triedb::build()
{
    tt = trie_table(this->source);
    std::ifstream file;
    file.open (this->source + "/#Tables.data");
    std::string s;
    while(file >> s){
        tt.load(s);
    }
    file.close();
}

triedb::triedb() 
{
    this->source = "TrieDB";
    this->build();
}

void triedb::insert_table(const std::string tag) 
{
    tt.insert(tag);
}

void triedb::insert_row(generic_class row) 
{
    trie_row* tr = tt.get_trie_row(row.get_tag());
    if(tr == NULL){
        this->insert_table(row.get_tag());
        tr = tt.get_trie_row(row.get_tag());
    }
    tr->insert(row.get_id(), row);
}

void triedb::insert_random_rows(generic_class row, unsigned number) 
{
    for(int i  = 0; i < number; i++){
        row.set_id(std::to_string((unsigned) rand()));
        for(auto att: row.attributes){
            row.set_attribute(att.first, std::to_string((unsigned) rand()));
        }
        this->insert_row(row);
    }
}

void triedb::update_row(generic_class row) 
{
    trie_row* tr = tt.get_trie_row(row.get_tag());
    tr->update(row.get_id(),row);
}

void triedb::update_attribute(const std::string tag, const std::string id, const std::string name, const std::string value) 
{
    trie_row* tr = tt.get_trie_row(tag);
    generic_class gc = tr->get(id);
    gc.set_attribute(name, value);
    tr->update(id, gc);
}

void triedb::remove_table(const std::string tag) 
{
    tt.remove(tag);
}

void triedb::remove_row(const std::string tag, const std::string id) 
{
    trie_row* tr = tt.get_trie_row(tag);
    tr->remove(id);
}

generic_class triedb::get_row(const std::string tag, const std::string id) 
{
    trie_row* tr = tt.get_trie_row(tag);
    if(tr == NULL) return generic_class("NULL", "NULL");
    return tr->get(id);
}

generic_class triedb::get_row(const std::string tag) 
{
    trie_row* tr = tt.get_trie_row(tag);
    if(tr == NULL) return generic_class("NULL", "NULL");
    return tr->pattern();
}

std::vector<generic_class> triedb::get_all_rows(const std::string tag) 
{
    std::vector<generic_class> list;
    trie_row* tr = tt.get_trie_row(tag);
    if(tr == NULL) return list;
    list = tr->get_all();
    return list;
}

std::string triedb::get_attribute(const std::string tag, const std::string id, const std::string name) 
{
    generic_class gc = this->get_row(tag, id);
    return gc.get_attribute(name);
}

std::string triedb::get_string(const std::string tag, const std::string id) 
{
    generic_class gc = this->get_row(tag, id);
    return gc.to_string();
}

std::string triedb::get_string(const std::string tag) 
{
    generic_class gc = this->get_row(tag);
    return gc.to_string();
}

std::vector<std::string> triedb::get_all_strings(const std::string tag) 
{
    std::vector<generic_class> list = this->get_all_rows(tag);
    std::vector<std::string> strings;
    for(auto r: list){
        strings.push_back(r.to_string());
    }
    return strings;
}