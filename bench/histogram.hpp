#pragma once

#include <set>
#include <iostream>
#include <numeric>
#include <cmath>


template<class T>
class Histogram {
    public:
    std::multiset<T> hist;
    inline void append(T v){
        hist.insert(v);
    }

    inline T percentile(double p) const{
        if (hist.empty()) return T();
        auto idx = static_cast<uint64_t>(hist.size() * p);
        if (idx >= hist.size()) idx = hist.size() - 1;
        auto it = hist.begin();
        std::advance(it, idx);
        return *it;
    }

    void print() const {
        std::cout << "Latency (us):\n";
        std::cout << "  50th percentile: " << percentile(0.5)*1000000 << " us\n";
        std::cout << "  90th percentile: " << percentile(0.9)*1000000 << " us\n";
        std::cout << "  99th percentile: " << percentile(0.99)*1000000 << " us\n";
        std::cout << "  99.9th percentile: " << percentile(0.999)*1000000 << " us\n";
        std::cout << "  99.99th percentile: " << percentile(0.9999)*1000000 << " us\n";
        std::cout << "  slowest: " << *hist.rbegin()*1000000 << " us\n";
        std::cout << " average: " << (hist.empty() ? 0 : std::accumulate(hist.begin(), hist.end(), T()) / hist.size())*1000000 << " us\n";
        std::cout << " total: " << std::accumulate(hist.begin(), hist.end(), T()) << " s\n";
    }
};