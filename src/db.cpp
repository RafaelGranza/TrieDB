#include "triedb.h"
#include "trie/trie.h"
#include "wal/wal.h"

namespace triedb {

struct DB::Impl {
    Trie<std::string> memtable;
    WAL wal;
};

DB::DB(const std::string& name)
    : impl(std::make_unique<Impl>()), name(name)
{
    impl->wal(name);
    impl->wal.load_memtable(impl->memtable);
}

DB::~DB() = default;

void DB::put(const std::string& key, const std::string& value) {
    impl->wal.append(OP::INSERT, key, value);
    impl->memtable.insert(key, value);
}

std::string DB::get(const std::string& key) {
    if(impl->memtable.count(key))
        return std::string(impl->memtable.get(key));

    return "";
}

void DB::remove(const std::string& key) {
    impl->wal.append(OP::REMOVE, key);
    impl->memtable.remove(key);
}

}