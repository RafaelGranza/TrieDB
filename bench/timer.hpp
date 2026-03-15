#pragma once

#include <chrono>

class Timer {
    std::chrono::steady_clock::time_point start;
public:
    Timer() : start(std::chrono::steady_clock::now()) {}

    double elapsed_time() {
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        return elapsed.count();
    }
};