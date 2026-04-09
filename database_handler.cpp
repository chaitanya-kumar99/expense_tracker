#include "database_handler.h"
#include <iostream>
#include <sstream>

using namespace std;

DatabaseHandler::DatabaseHandler() {
    std::string host     = getEnv("DB_HOST",     "localhost");
    std::string port     = getEnv("DB_PORT",     "5432");
    std::string dbname   = getEnv("DB_NAME",     "data");
    std::string user     = getEnv("DB_USER",     "postgres");
    std::string password = getEnv("DB_PASSWORD", "");

    ostringstream oss;
    oss << "host=" << host
        << " port=" << port
        << " dbname=" << dbname
        << " user=" << user
        << " password=" << password;
    connectionString = oss.str();
}

void DatabaseHandler::connect() {
    try {
        pqxx::connection conn(connectionString);
        if (conn.is_open()) {
            cout << "✓ Connected to database successfully!" << endl;
        }
    } catch (const exception& e) {
        cerr << "✗ Database connection failed: " << e.what() << endl;
    }
}

int DatabaseHandler::insertExpense(int amount, string description) {
    try {
        pqxx::connection conn(connectionString);
        pqxx::work txn(conn);
        
        string query = "INSERT INTO expenses (amount, description) VALUES (" +
                      txn.quote(amount) + ", " +
                      txn.quote(description) + 
                      ") RETURNING id";
        
        pqxx::result res = txn.exec(query);
        txn.commit();
        
        int insertedId = res[0][0].as<int>();
        cout << "✓ Expense inserted with ID: " << insertedId << endl;
        return insertedId;
        
    } catch (const exception& e) {
        cerr << "✗ Error inserting expense: " << e.what() << endl;
        return -1;
    }
}

vector<Expense> DatabaseHandler::getAllExpenses() {
    vector<Expense> expenses;
    
    try {
        pqxx::connection conn(connectionString);
        pqxx::work txn(conn);
        
        pqxx::result res = txn.exec(
            "SELECT id, amount, description, date FROM expenses ORDER BY date DESC"
        );
        
        for (const auto& row : res) {
            Expense exp;
            exp.id = row["id"].as<int>();
            exp.amount = row["amount"].as<int>();
            exp.description = row["description"].as<string>();
            exp.date = row["date"].as<string>();
            expenses.push_back(exp);
        }
        
        txn.commit();
        
    } catch (const exception& e) {
        cerr << "✗ Error fetching expenses: " << e.what() << endl;
    }
    
    return expenses;
}

void DatabaseHandler::delExpense(int id) {
    try {
        pqxx::connection conn(connectionString);
        pqxx::work txn(conn);
        
        string query = "DELETE FROM expenses WHERE id = " + txn.quote(id);
        pqxx::result res = txn.exec(query);
        
        txn.commit();
        
        if (res.affected_rows() > 0) {
            cout << "✓ Expense #" << id << " deleted successfully!" << endl;
        } else {
            cout << "✗ Expense #" << id << " not found!" << endl;
        }
        
    } catch (const exception& e) {
        cerr << "✗ Error deleting expense: " << e.what() << endl;
    }
}

int DatabaseHandler::getTotalExpenses() {
    try {
        pqxx::connection conn(connectionString);
        pqxx::work txn(conn);
        
        pqxx::result res = txn.exec(
            "SELECT COALESCE(SUM(amount), 0) as total FROM expenses"
        );
        
        txn.commit();
        
        if (!res.empty()) {
            return res[0]["total"].as<int>();
        }
        
    } catch (const exception& e) {
        cerr << "✗ Error calculating total: " << e.what() << endl;
    }
    
    return 0;
}