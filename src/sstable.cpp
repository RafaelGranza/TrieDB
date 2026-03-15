#include <string>
#include <fstream>
#include <map>
#include <filesystem>
#include "utils.cpp"

class SSTable {
    std::string table_name;
    std::string db_name = "data";
    std::string filepath;
    uint32_t level;

    static std::string generate_name(){
        return generate_timestamp();
    }

public:
    explicit SSTable(const std::string& db_name, const std::string& path) : db_name(db_name), level(0) {
        table_name = path;
        filepath = build_path(db_name, table_name + ".sst");
    }

    SSTable(const SSTable& sst1, const SSTable& sst2) : db_name(sst1.db_name), level(std::max(sst1.level, sst2.level) + 1) {
        table_name = generate_name();
        filepath = build_path(db_name, table_name + ".sst");
        merge(sst1, sst2);
    }

    SSTable(const std::string& db_name, const std::map<std::string, std::string>& data) : db_name(db_name), level(0) {
        table_name = generate_name();
        filepath = build_path(db_name, table_name + ".sst");

        write_to_file(std::move(data));
    }

    void write_to_file(const std::map<std::string, std::string>& data) {
        std::ofstream out(filepath);
        for (const auto& pair : data) {
            out << pair.first << " " << pair.second << "\n";
        }
    }

    bool count(const std::string& key) {
        std::ifstream in(filepath);
        std::string line;
        while (std::getline(in, line)) {
            std::istringstream iss(line);
            std::string k;
            iss >> k;
            if (k == key) {
                return true;
            }
        }
        return false;
    }

    std::string get(const std::string& key) {
        std::ifstream in(filepath);
        std::string line;
        while (std::getline(in, line)) {
            std::istringstream iss(line);
            std::string k, v;
            iss >> k;
            std::getline(iss, v);
            if (!v.empty() && v[0] == ' ') v.erase(0, 1);
            if (k == key) {
                return v;
            }
        }
        return "";
    }

    std::string name(){
        return table_name;
    }

    void remove() {
        std::filesystem::remove(filepath);
    }

private:
    void merge(const SSTable& sst1, const SSTable& sst2) {
    }
};

static std::map<std::string, SSTable> load_sstables(const std::string& name){
    std::map<std::string, SSTable> res;
    std::string dir_path = build_path(name, "");

    std::filesystem::path dir(dir_path);
    if (!std::filesystem::exists(dir) || !std::filesystem::is_directory(dir)) {
        return res;
    }

    for (const auto& entry : std::filesystem::directory_iterator(dir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".sst") {
            std::string table_name = entry.path().stem().string();
            res.emplace(table_name, SSTable(name, table_name));
        }
    }
    return res;
}