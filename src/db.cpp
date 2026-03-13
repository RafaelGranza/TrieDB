#include "triedb.h"
#include "trie/trie.h"

namespace triedb {

struct DB::Impl {
    Trie<std::string> memtable;
};

DB::DB(const std::string& path)
    : impl(std::make_unique<Impl>())
{}

DB::~DB() = default;

void DB::put(const std::string& key, const std::string& value) {
    impl->memtable.insert(key, value);
}

std::string DB::get(const std::string& key) {
    if(impl->memtable.count(key))
        return std::string(impl->memtable.get(key));

    return "";
}

void DB::remove(const std::string& key) {
    impl->memtable.remove(key);
}

}