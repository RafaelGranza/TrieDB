#include "generic_class.h"


generic_class::generic_class(const std::string tag, const std::string id) 
{
    this->tag = tag;
    this->id = id;
}

generic_class::~generic_class() {}

bool generic_class::is_attribute(const std::string id) 
{
    return this->attributes.count(id);
}

void generic_class::load(const std::string path) 
{
    std::string s, buffer;
    std::ifstream ifs;
    ifs.open(path, std::ifstream::in);
    while (std::getline(ifs, buffer)) s += buffer;
    std::remove( s.begin(), s.end(), '{');
    std::remove( s.begin(), s.end(), '}');
    std::remove( s.begin(), s.end(), ':');
    std::remove( s.begin(), s.end(), ',');
    bool open = false;
    std::string aux, laux;
    int id = 0;
    for(char c : s){
        if(c == '"' && open){
            switch (id)
            {
            case 0:
                this->set_tag(aux);
                break;
            
            case 1:
                break;
            case 2:
                this->set_id(aux);
                break;
            default:
                if(id%2==0) this->push_attribute(laux, aux);
                break;
            }
            id++;
            open = false;
        }else if(c == '"'){
            open = true;
            laux = aux;
            aux = "";
        }else{
            aux += c;
        }
    }
    ifs.close();
}

std::string generic_class::to_string() 
{
    if(this->tag == "NULL") return "";
    std::string s = "{\"";
    s += this->tag;
    s += "\":\n";
    s += "\t{\"id\":\"";
    s += this->id;
    s += "\"";
    for(auto p: this->attributes){
        s += ",\n\t\"";
        s += p.first;
        s += "\":\"";
        s += p.second;
        s += "\"";
    }
    s += "\n\t}\n}";
    return s;
}

void generic_class::set_tag(const std::string tag) 
{
    this->tag = tag;
}

std::string generic_class::get_tag() 
{
    return this->tag;
}

void generic_class::set_id(const std::string id) 
{
    this->id = id;
}

std::string generic_class::get_id() 
{
    return this->id;
}

void generic_class::push_attribute(const std::string tag, const std::string value) 
{
    if(!this->is_attribute(tag))
    {
        this->attributes[tag] = value;
        this->number_of_attributes++; 
    }else
    {
        this->set_attribute(tag, value);
    }
}

std::string generic_class::get_attribute(const std::string tag) 
{
    if(!this->is_attribute(tag))
    {
        return this->attributes[tag];   
    }
    return "";   
}

void generic_class::set_attribute(const std::string tag, const std::string value) 
{
     this->attributes[tag] = value;
}

void generic_class::pop_attribute(const std::string tag) 
{
    this->attributes.erase(tag); 
    this->number_of_attributes--;
}

void generic_class::reset() 
{
    for(auto &att : this->attributes) att.second = "none";
    this->id = "none";
}

generic_class::generic_class() 
{
    
}
