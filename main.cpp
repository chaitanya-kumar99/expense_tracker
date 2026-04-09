#include <iostream>
#include <string>
#include "expense_manager.h"

using namespace std;

void printUsage() {
    cout << "\nExpense Tracker - Usage:" << endl;
    cout << "  ./expense test                    - Test database connection" << endl;
    cout << "  ./expense add <amount> <desc>     - Add expense" << endl;
    cout << "  ./expense list                    - List all expenses" << endl;
    cout << "  ./expense delete <id>             - Delete expense" << endl;
    cout << "  ./expense total                   - Show total expenses" << endl;
    cout << "\nExamples:" << endl;
    cout << "  ./expense add 500 \"Lunch\"" << endl;
    cout << "  ./expense list" << endl;
    cout << "  ./expense delete 1" << endl;
    cout << "  ./expense total\n" << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage();
        return 1;
    }
    
    string command = argv[1];
    ExpenseManager manager;
    
    if (command == "test") {
        DatabaseHandler db;
        db.connect();
        return 0;
    }
    
    if (command == "add") {
        if (argc < 4) {
            cout << "Usage: ./expense add <amount> <description>" << endl;
            return 1;
        }
        
        int amount = stoi(argv[2]);
        string description = argv[3];
        
        manager.addExpenses(amount, description);
        
    } else if (command == "list") {
        manager.listExpenses();
        
    } else if (command == "delete") {
        if (argc < 3) {
            cout << "Usage: ./expense delete <id>" << endl;
            return 1;
        }
        
        int id = stoi(argv[2]);
        manager.delExpenses(id);
        
    } else if (command == "total") {
        int total = manager.totalExpenses();
        cout << "\n💰 Total expenses: $" << total << "\n" << endl;
        
    } else {
        cout << "Unknown command: " << command << endl;
        printUsage();
    }
    
    return 0;
}