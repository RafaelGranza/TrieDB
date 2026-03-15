#pragma once

#include <ctime>
#include <filesystem>
#include "histogram.hpp"
#include "workload.hpp"
#include <fstream>
#include <iomanip>
#include <numeric>
#include <string>

namespace csv {

const std::string VERSION = "v2_hashmap_threaded";

std::string get_current_date() {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    char date_buf[16];
    std::strftime(date_buf, sizeof(date_buf), "%Y-%m-%d", &tm);
    return std::string(date_buf);
}

std::string extract_config_name(const std::string& name) {
    auto last_slash = name.find_last_of("/\\");
    std::string config_name = (last_slash != std::string::npos) ? name.substr(last_slash + 1) : name;
    auto dot = config_name.find_last_of('.');
    if (dot != std::string::npos)
        config_name = config_name.substr(0, dot);
    return config_name;
}

std::string compose_filename(const std::string& date, const std::string& config_name, const std::string& version) {
    return "bench/results/" + date + "-" + config_name + "-" + version + ".csv";
}

bool file_needs_header(const std::string& filename) {
    std::ifstream in(filename);
    return !in.good() || in.peek() == std::ifstream::traits_type::eof();
}

void write_header(std::ofstream& out) {
    out << "operation_type,num_ops,key_size,value_size,50th_percentile,90th_percentile,99th_percentile,99.9th_percentile,99.99th_percentile, 99.999th_percentile,slowest,average,total\n";
}

void write_result_fields(std::ofstream& out, const Histogram<double>& hist, const Workload& wl) {
    auto write_field = [&](auto value) {
        out << std::setprecision(9) << value << ",";
    };
    write_field(static_cast<int>(wl.type));
    write_field(wl.num_ops);
    write_field(wl.key_size);
    write_field(wl.value_size);
    write_field(hist.percentile(0.5));
    write_field(hist.percentile(0.9));
    write_field(hist.percentile(0.99));
    write_field(hist.percentile(0.999));
    write_field(hist.percentile(0.9999));
    write_field(hist.percentile(0.99999));
    write_field(hist.hist.empty() ? 0 : *hist.hist.rbegin());
    write_field(hist.hist.empty() ? 0 : std::accumulate(hist.hist.begin(), hist.hist.end(), 0.0) / hist.hist.size());
    out << std::accumulate(hist.hist.begin(), hist.hist.end(), 0.0) << "\n";
}

void record_result(const std::string& config_path, const Histogram<double>& hist, const Workload& wl) {
    std::string date = get_current_date();
    std::string config_name = extract_config_name(config_path);
    std::string filename = compose_filename(date, config_name, VERSION);

    std::filesystem::create_directories("bench/results");

    std::ofstream out;
    bool need_header = file_needs_header(filename);
    out.open(filename, std::ios::app);

    if (need_header) {
        write_header(out);
    }

    write_result_fields(out, hist, wl);
}

}