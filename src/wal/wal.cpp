#include "wal.h"
#include <sstream>
#include <iostream>
#include <filesystem>

void WAL::open() {
    // Ensure the storage directory exists
    std::filesystem::path storage_dir = std::filesystem::path(path).parent_path();
    if (!storage_dir.empty() && !std::filesystem::exists(storage_dir)) {
        std::filesystem::create_directories(storage_dir);
    }

    wal.open(path, std::ios::in | std::ios::out | std::ios::app);
    if(!wal.is_open()) {
        wal.clear();
        wal.open(path, std::ios::out);
        wal.close();
        wal.open(path, std::ios::in | std::ios::out | std::ios::app);
    }
}

std::string WAL::build_path(const std::string& path){
    std::filesystem::path storage_dir = "storage";
    std::filesystem::path name_dir = path;
    std::filesystem::path file_path = storage_dir / name_dir / "wal";
    return file_path.string();
}

WAL::WAL(const std::string& path) : path(path) {
    open();
}

void WAL::operator()(const std::string& p) {
    path = build_path(p);
    open();
}

void WAL::load_memtable(Trie<std::string>& trie) {
    if(!wal.is_open())
        open();

    wal.seekg(0);
    std::string line;
    while(std::getline(wal, line)) {
        if(line.empty())
            continue;
        std::istringstream iss(line);
        char code;
        iss >> code;
        if(code == 'I') {
            std::string key;
            std::string value;
            iss >> key;
            // remainder of line is value (could contain spaces)
            std::getline(iss, value);
            if(!value.empty() && value[0] == ' ') // strip leading space
                value.erase(0,1);
            trie.insert(key, value);
        } else if(code == 'R') {
            std::string key;
            iss >> key;
            trie.remove(key);
        }
    }
    // clear eof flag so subsequent writes/read work
    wal.clear();
}

void WAL::append(OP op, const std::string& key, const std::string& value) {
    if(!wal.is_open())
        open();

    wal.clear();
    wal.seekp(0, std::ios::end);

    if(op == OP::INSERT) {
        wal << 'I' << ' ' << key << ' ' << value << '\n';
    } else if(op == OP::REMOVE) {
        wal << 'R' << ' ' << key << '\n';
    }
    wal.flush();
}
