#include "database.h"
#include <sstream>
#include <fstream>

Database::Database() {
    accounts["user1"] = 1000;
    accounts["user2"] = 500;
}

Database& Database::getInstance() {
    static Database instance;
    return instance;
}

std::string Database::process(const std::string& request) {
    std::lock_guard<std::mutex> lock(mtx);

    std::stringstream ss(request);
    std::string command;

    ss >> command;

    if (command == "BALANCE") {
        std::string user;
        ss >> user;
        return std::to_string(accounts[user]);
    }

    if (command == "TRANSFER") {
        std::string from, to;
        double amount;

        ss >> from >> to >> amount;

        if (accounts[from] >= amount) {
            accounts[from] -= amount;
            accounts[to] += amount;

            std::ofstream file("data.txt");
            for (auto& acc : accounts) {
                file << acc.first << " " << acc.second << "\n";
            }

            return "OK";
        } else {
            return "INSUFFICIENT";
        }
    }

    return "UNKNOWN COMMAND";
}
