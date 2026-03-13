#include <iostream>
#include <string>
#include <sstream>

#include "triedb.h"

int main() {

    triedb::DB db("data");

    std::string line;

    std::cout << "TrieDB CLI\n";
    std::cout << "commands: put key value | get key | del key | exit\n";

    while (true) {

        std::cout << "> ";
        if(!std::getline(std::cin, line))
            break;

        std::stringstream ss(line);

        std::string cmd;
        ss >> cmd;

        if(cmd == "put") {

            std::string key, value;
            ss >> key >> value;

            if(key.empty() || value.empty()) {
                std::cout << "usage: put key value\n";
                continue;
            }

            db.put(key, value);
            std::cout << "OK\n";

        }
        else if(cmd == "get") {

            std::string key;
            ss >> key;

            if(key.empty()) {
                std::cout << "usage: get key\n";
                continue;
            }

            auto v = db.get(key);

            
            std::cout << v << "\n";
        }
        else if(cmd == "del") {

            std::string key;
            ss >> key;

            if(key.empty()) {
                std::cout << "usage: del key\n";
                continue;
            }

            db.remove(key);
            std::cout << "OK\n";
        }
        else if(cmd == "exit" || cmd == "quit") {
            break;
        }
        else {
            std::cout << "unknown command\n";
        }
    }

    return 0;
}