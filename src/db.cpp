#pragma once

#include <ranges>
#include "triedb.hpp"
#include "trie/trie.h"
#include "memtable.cpp"
#include "wal/wal.h"
#include "sstable.cpp"
#include "map.cpp"
#include "hash_map.cpp"
#include "persistency_manager.hpp"



namespace triedb {

constexpr std::size_t THRESHOLD = 1 << 24; // 16MB

struct DB::Impl {
    PersistencyManager persistency_manager;
    Memtable<HashMap> memtable;
    WAL<HashMap> wal;
    std::map<std::string, SSTable> sstables;
    std::string name;

    Impl(DB& db) : persistency_manager(db) {}


    void flush() {
        SSTable sstable(name, memtable.flush());
        sstables.emplace(sstable.name(), std::move(sstable));
        memtable.reset();
        wal.reset();
    }

    void check_flush(){
        if(memtable.size() >= THRESHOLD) {
            flush();
        }
        return;
    }
};

DB::DB(const std::string& name)
    : name(name), impl(std::make_unique<Impl>(*this))
{
    impl->name = name;
    impl->wal(name);
    impl->wal.load_memtable(impl->memtable);
    impl->sstables = load_sstables(name);
}

DB::~DB() = default;

void DB::put(const std::string& key, const std::string& value) {
    impl->check_flush();
    impl->wal.append(OP::INSERT, key, value);
    impl->memtable.insert(key, value);
}

std::string DB::get(const std::string& key) {
    if(impl->memtable.count(key))
        return std::string(impl->memtable.get(key));

    for(auto& [_, sst]: impl->sstables | std::views::reverse){
        if(sst.count(key))
            return sst.get(key);
    }

    return "";
}

void DB::remove(const std::string& key) {
    impl->check_flush();
    impl->wal.append(OP::REMOVE, key);
    impl->memtable.remove(key);
}

void DB::drop() {
    impl->memtable.reset();
    impl->wal.reset();
    for(auto& [_, sst]: impl->sstables){
        sst.remove();
    }
    impl->sstables.clear();
}

void DB::flush() {
    impl->flush();
}

uint64_t DB::memtable_size() {
    return impl->memtable.size();
}

}