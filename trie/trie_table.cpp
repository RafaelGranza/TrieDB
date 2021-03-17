#include "trie_table.h"


void trie_table::insert(const std::string tag) 
{
    unsigned idx = 0;
    for(char c : tag)
    {
        if(this->nodes[idx].count(c) == 0) this->nodes[idx][c] = ++this->number_of_nodes;
        idx = this->nodes[idx][c];
    }
    if(!this->table_index.count(idx)){
        this->table_index[idx] = this->number_of_tables++;
        if(this-> source != "") {
            int v = system(("mkdir -p " + this->source + "/" + tag).c_str());
            this->rows.push_back(trie_row(this->source + "/" + tag));
        }else {
            int v = system(("mkdir -p " + tag).c_str());
            this->rows.push_back(trie_row(tag));
        }
        std::ofstream file;
        file.open (this->source + "/#Tables.data", std::ios_base::app);
        file << tag+"\n";
        file.close();
    }
    
}

void trie_table::load(const std::string tag) 
{
    unsigned idx = 0;
    for(char c : tag)
    {
        if(this->nodes[idx].count(c) == 0) this->nodes[idx][c] = ++this->number_of_nodes;
        idx = this->nodes[idx][c];
    }
    this->table_index[idx] = this->number_of_tables++;
    if(this-> source != "") {
        int v = system(("mkdir -p " + this->source + "/" + tag).c_str());
        this->rows.push_back(trie_row(this->source + "/" + tag));
    }else {
        int v = system(("mkdir -p " + tag).c_str());
        this->rows.push_back(trie_row(tag));
    }
}

int trie_table::get_index(const std::string tag) 
{
    unsigned idx = 0;
    for(char c : tag)
    {
        if(this->nodes[idx].count(c) == 0) return -1;
        idx = this->nodes[idx][c];
    }
    return this->table_index[idx];
}

trie_row* trie_table::get_trie_row(const std::string tag) 
{
    int idx = this->get_index(tag);
    if(idx == -1)return NULL;
    return &rows[idx];
}

void trie_table::remove(const std::string tag) 
{
    unsigned idx = 0;
    for(char c : tag)
    {
        if(this->nodes[idx].count(c) == 0) return;
        idx = this->nodes[idx][c];
    }
    this->table_index[idx] = -1;
    if(this-> source != ""){
        remove_from_file(this->source + "/#Tables.data", tag);
        int v = system(("rm -rf "+this->source+"/"+tag).c_str());
    }else{
        remove_from_file(this->source + "#Tables.data", tag);
        int v = system(("rm -rf "+tag).c_str());
    }
}

trie_table::trie_table(std::string source) 
{
    this->source = source;
    this->build();
}

void trie_table::build() 
{

}
