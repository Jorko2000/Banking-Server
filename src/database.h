#pragma once
#include <map>
#include <mutex>
#include <string>

class Database {
private:
    std::map<std::string, double> accounts;
    std::mutex mtx;

    Database();

public:
    static Database& getInstance();
    std::string process(const std::string& request);
};
