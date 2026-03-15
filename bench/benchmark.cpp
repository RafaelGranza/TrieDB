#include <string>
#include <vector>

#include "timer.hpp"
#include "histogram.hpp"
#include "workload.hpp"
#include "triedb.hpp"
#include "csv.hpp"

triedb::DB db("bench");

static uint64_t rng = 88172645463325252ULL;

inline uint64_t fast_rand() {
    rng ^= rng << 7;
    rng ^= rng >> 9;
    return rng;
}

void generate_key(const Workload& wl, std::string& key, uint64_t i) {

    key.resize(wl.key_size);

    if (wl.type == Workload::TYPE::FILLSEQ) {

        for (int j = wl.key_size - 1; j >= 0; j--) {
            key[j] = 'a' + (i % 26);
            i /= 26;
        }

    } else {

        for (int j = 0; j < wl.key_size; j++) {
            key[j] = 'a' + (fast_rand() % 26);
        }

    }
}

void generate_value(const Workload& wl, std::string& data) {
    data.assign(wl.value_size, 'x');
}

inline void run_op(const Workload& wl,
                   const std::string& key,
                   const std::string& value)
{
    switch (wl.type) {

        case Workload::TYPE::FILLSEQ:
        case Workload::TYPE::FILLRAND:
            db.put(key, value);
            break;

        case Workload::TYPE::READRAND:
            db.get(key);
            break;
    }
}

int main(int argc, char* argv[]) {

    
    if (argc != 2)
        throw std::runtime_error("Pass config file");
    
    std::cout << "Starting benchmark...\n";
    db.drop();

    Workload wl(argv[1]);

    Histogram<double> hist;

    std::string key;
    std::string value;

    key.reserve(wl.key_size);
    value.reserve(wl.value_size);
    generate_value(wl, value);

    uint64_t warmup = wl.num_ops / 10;

    std::cout << "Warming up with " << warmup << " operations...\n";

    for (uint64_t i = 0; i < warmup; i++) {

        generate_key(wl, key, i);
        run_op(wl, key, value);
    }

    std::cout << "Running " << wl.num_ops << " operations...\n";

    for (uint64_t i = 0; i < wl.num_ops; i++) {

        if(i % (wl.num_ops / 10) == 0) {
            std::cout << (i * 100) / wl.num_ops << "% completed...\n";
        }

        generate_key(wl, key, i);

        Timer t;
        run_op(wl, key, value);
        hist.append(t.elapsed_time());
    }

    db.drop();

    hist.print();
    csv::record_result(argv[1], hist, wl);
}

