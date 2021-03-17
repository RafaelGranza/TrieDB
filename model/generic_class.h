#ifndef __GENERIC_CLASS_H__
#define __GENERIC_CLASS_H__
#include <string>
#include <map>
#include <utility>
#include <algorithm>
#include <iostream>
#include <fstream>

class generic_class
{
private:
    std::string tag;
    std::string id;
    unsigned number_of_attributes;
public:
    generic_class();
    generic_class(const std::string tag,const std::string id = "none");
    ~generic_class();
    std::map<std::string, std::string> attributes;
    bool is_attribute(const std::string tag);
    void load(const std::string path);
    std::string to_string();
    void set_tag(const std::string tag);
    std::string get_tag();
    void set_id(const std::string id);
    std::string get_id();
    void push_attribute(const std::string tag, const std::string value = "none");
    std::string get_attribute(const std::string tag);
    void set_attribute(const std::string tag, const std::string value);
    void pop_attribute(const std::string tag);
    void reset();
};
#endif // __GENERIC_CLASS_H__