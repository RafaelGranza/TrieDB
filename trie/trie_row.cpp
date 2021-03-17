#include "trie_row.h"

void trie_row::insert(const std::string id, const generic_class row) 
{
    unsigned idx = 0;
    for(char c : id)
    {
        if(this->nodes[idx].count(c) == 0) this->nodes[idx][c] = ++this->number_of_nodes;
        idx = this->nodes[idx][c];
    }
    if(!this->paths.count(idx)) 
        this->paths[idx] = create_row(id, row);
    
}

void trie_row::load(const std::string id, const std::string path, bool begin) 
{
    unsigned idx = 0;
    for(char c : id)
    {
        if(this->nodes[idx].count(c) == 0) this->nodes[idx][c] = ++this->number_of_nodes;
        idx = this->nodes[idx][c];
    }
    this->paths[idx] = path;

}

generic_class trie_row::get(const std::string id) 
{
    unsigned idx = 0;
    generic_class none("NULL", "NULL");
    for(char c : id)
    {
        if(this->nodes[idx].count(c) == 0) return none;
        idx = this->nodes[idx][c];
    }
    none.load(this->paths[idx]);
    return none;
}

std::vector<generic_class> trie_row::get_all() 
{
    std::vector<generic_class> list;
    generic_class none("NULL", "NULL");
    for(auto p : this->paths){
        none.load(p.second);
        list.push_back(none);
    }
    return list;
}

generic_class trie_row::pattern() 
{
    generic_class gc("NULL", "NULL");
    gc.load(this->paths.begin()->second);
    gc.reset();
    return gc;
}

std::string trie_row::create_row(const std::string id, generic_class row) 
{
    if(this-> source != "") int v = system(("mkdir -p "+this->source).c_str());
    std::ofstream file;
    std::string  path = this->source + "/" + id + ".json";
    file.open (path);
    file << row.to_string();
    file.close();
    file.open (this->source + "/#Rows.data", std::ios_base::app);
    file << id+"\n";
    file.close();
    return path;
}

void trie_row::update(const std::string id, const generic_class row) 
{
    unsigned idx = 0;
    for(char c : id)
    {
        if(this->nodes[idx].count(c) == 0) return;
        idx = this->nodes[idx][c];
    }
    this->create_row(id, row);
}

void trie_row::remove(const std::string id) 
{
    unsigned idx = 0;
    for(char c : id)
    {
        if(this->nodes[idx].count(c) == 0) return;
        idx = this->nodes[idx][c];
    }
    remove_from_file(this->source + "/#Rows.data", id);
    this->remove_row(this->paths[idx]);
    this->paths.erase(idx);
}

void trie_row::remove_row(const std::string path) 
{
    if(this-> source != "") int v = system(("rm -f "+path).c_str());
    else int v = system(("rm -f "+path).c_str());
}

trie_row::trie_row(std::string source) 
{
    this->source = source;
    this->build();
}

void trie_row::build() 
{
    std::ifstream file;
    file.open (this->source+"/#Rows.data");
    std::string id;
    while(file >> id) this->load(id, this->source + "/" + id + ".json");
    file.close();
}
