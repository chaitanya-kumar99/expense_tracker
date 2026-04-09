#pragma once
#include <string>
#include <vector>
#include <cstdlib>
#include <pqxx/pqxx>

struct Expense {
    int id;
    int amount;
    std::string description;
    std::string date;
};

class DatabaseHandler {
private:
    std::string connectionString;

    static std::string getEnv(const char* key, const char* fallback) {
        const char* val = std::getenv(key);
        return val ? std::string(val) : std::string(fallback);
    }

public:
    DatabaseHandler();
    void connect();
    int insertExpense(int amount, std::string description);
    std::vector<Expense> getAllExpenses();
    void delExpense(int id);
    int getTotalExpenses();
};