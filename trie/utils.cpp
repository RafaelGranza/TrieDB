#include "utils.h"



void remove_from_file(std::string path, std::string key) 
{
    std::ifstream read;
    std::string s, aux;
    read.open (path);
    while(read >> aux){
        if(aux != key) s += aux + "\n";
    }
    read.close();
    std::ofstream write;
    write.open (path);
    write << s;
    write.close();
}
