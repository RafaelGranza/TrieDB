#include <string>
#include <filesystem>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <random>


static std::string build_path(const std::string& db_name, const std::string& file_name){
    std::filesystem::path storage_dir = "storage";
    std::filesystem::path file_path = storage_dir / db_name / file_name;
    return file_path.string();
}


static std::string generate_random_name() {
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<uint64_t> dist;
    std::stringstream ss;
    ss << std::hex << dist(rng);
    return ss.str();
}

static std::string generate_timestamp() {
    using namespace std::chrono;
    auto now = system_clock::now();
    auto epoch = duration_cast<milliseconds>(now.time_since_epoch()).count();
    return std::to_string(epoch);
}
