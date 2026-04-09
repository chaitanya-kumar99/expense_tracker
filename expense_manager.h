#pragma once
#include <iostream>
#include <string>
#include "database_handler.h"

using namespace std;

class ExpenseManager {
public:
    void addExpenses(int amount, string description);
    void listExpenses();
    void delExpenses(int id);
    int totalExpenses();
    
private:
    DatabaseHandler db;
};