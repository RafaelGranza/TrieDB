#include "wal.h"
#include "utils.cpp"
#include <sstream>
#include <iostream>
#include <filesystem>

template<typename T>
void WAL<T>::open() {
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

template<typename T>
WAL<T>::WAL(const std::string& path) : path(path) {
    open();
}

template<typename T>
void WAL<T>::operator()(const std::string& p) {
    path = build_path(p, "wal");
    open();
}

template<typename T>
void WAL<T>::load_memtable(Memtable<T>& memtable) {
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
            memtable.insert(key, value);
        } else if(code == 'R') {
            std::string key;
            iss >> key;
            memtable.remove(key);
        }
    }
    // clear eof flag so subsequent writes/read work
    wal.clear();
}

template<typename T>
void WAL<T>::append(OP op, const std::string& key, const std::string& value) {
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

template<typename T>
void WAL<T>::reset() {
    if (!wal.is_open())
        open();

    wal.close();
    wal.open(path, std::ios::out | std::ios::trunc);
    wal.close();
    wal.open(path, std::ios::in | std::ios::out | std::ios::app);
}
