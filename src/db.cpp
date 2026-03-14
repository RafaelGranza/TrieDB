#include <ranges>
#include "triedb.h"
#include "trie/trie.h"
#include "wal/wal.h"
#include "sstable.cpp"



namespace triedb {

constexpr std::size_t THRESHOLD = 20;

struct DB::Impl {
    Trie<std::string> memtable;
    WAL wal;
    std::map<std::string, SSTable> sstables;

    void check_flush(){
        if(memtable.size() >= THRESHOLD) {
            SSTable sstable(memtable.flush());
            sstables.emplace(sstable.name(), std::move(sstable));
            std::cout << "sstable built" << std::endl;
            memtable.reset();
            wal.reset();
        }
        return;
    }
};

DB::DB(const std::string& name)
    : impl(std::make_unique<Impl>()), name(name)
{
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

}