#pragma once

#include <string>
#include <thread>
#include <utility>
#include <chrono>
#include "triedb.hpp"

class PersistencyManager {
    static constexpr std::size_t THRESHOLD = 1024; // Adjust threshold as needed
    triedb::DB& db;
    std::jthread flush_thread;

    static void flush_thread_func(triedb::DB& db) {
        std::stop_token st;
        while (!st.stop_requested()) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (db.memtable_size() > THRESHOLD) {
                db.flush();
            }
        }
    }

public:
    PersistencyManager(triedb::DB& db)
        : db(db), flush_thread(flush_thread_func, std::ref(this->db)) {}

    PersistencyManager(const PersistencyManager&) = delete;
    PersistencyManager& operator=(const PersistencyManager&) = delete;
};
