#include "expense_manager.h"
#include <iostream>
#include <iomanip>

using namespace std; 

void ExpenseManager::addExpenses(int amount, string description) {
    int id = db.insertExpense(amount, description);
    
    if (id > 0) {
        cout << "✓ Expense added successfully!" << endl;
        cout << "  ID: " << id << endl;
        cout << "  Amount: $" << amount << endl;
        cout << "  Description: " << description << endl;
    }
}

void ExpenseManager::listExpenses() {
    vector<Expense> expenses = db.getAllExpenses();
    
    if (expenses.empty()) {
        cout << "\nNo expenses found." << endl;
    } else {
        cout << "\n" << string(70, '-') << endl;
        cout << left 
             << setw(6) << "ID"
             << setw(12) << "Date"
             << setw(12) << "Amount ($)"
             << setw(40) << "Description" << endl;
        cout << string(70, '-') << endl;
        
        for (const Expense& exp : expenses) {
            cout << left
                 << setw(6) << exp.id
                 << setw(12) << exp.date
                 << setw(12) << exp.amount
                 << setw(40) << exp.description << endl;
        }
        
        cout << string(70, '-') << endl;
        cout << "Total: " << expenses.size() << " expense(s)\n" << endl;
    }
}

void ExpenseManager::delExpenses(int id) {
    db.delExpense(id);
}

int ExpenseManager::totalExpenses() {
    return db.getTotalExpenses();
}