//This code is written by Rishabh Pathak

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits> 

using namespace std;

struct Expense
{
    string date;
    string description;
    double amount;
};

void addExpense(vector<Expense> &expenses, const string &filename)
{
    Expense newExpense;
    cout << "Enter date (YYYY-MM-DD): ";
    cin >> newExpense.date;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    cout << "Enter description: ";
    getline(cin, newExpense.description);

    while (true)
    {
        cout << "Enter amount: $";
        if (cin >> newExpense.amount)
        {
            break;
        }
        else
        {
            cout << "Invalid input. Please enter a valid amount." << endl;
            cin.clear();                                         
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }

    expenses.push_back(newExpense);

    ofstream file(filename, ios::app); 
    if (file.is_open())
    {
        file << newExpense.date << " | " << newExpense.description << " | $" << fixed << setprecision(2) << newExpense.amount << endl;
        file.close();
        cout << "Expense added successfully!" << endl;
    }
    else
    {
        cerr << "Error: Unable to open the file for writing. Check file permissions or file path." << endl;
    }
}

void displaySummary(const vector<Expense> &expenses)
{
    if (expenses.empty())
    {
        cout << "No expenses recorded yet." << endl;
        return;
    }

    double totalAmount = 0.0;
    for (const Expense &expense : expenses)
    {
        totalAmount += expense.amount;
    }

    cout << "Expense Summary:" << endl;
    cout << "Total expenses: $" << fixed << setprecision(2) << totalAmount << endl;
    cout << "Number of expenses: " << expenses.size() << endl;

    cout << "\nExpense Details:" << endl;
    cout << setw(12) << "Date" << setw(30) << "Description" << setw(12) << "Amount" << endl;
    cout << setfill('-') << setw(54) << "-" << setfill(' ') << endl;
    for (const Expense &expense : expenses)
    {
        cout << setw(12) << expense.date << setw(30) << expense.description << setw(12) << "$" << fixed << setprecision(2) << expense.amount << endl;
    }
}

int main()
{
    const string filename = "expenses.txt"; 

    vector<Expense> expenses; 

    ifstream file(filename); 
    if (file.is_open())
    {
        Expense expense;
        while (getline(file, expense.date, '|') && getline(file, expense.description, '|'))
        {
            file >> expense.amount;
            file.ignore(); 
            expenses.push_back(expense);
        }
        file.close();
    }

    int choice;
    do
    {
        cout << "\nExpense Tracker Menu:" << endl;
        cout << "1. Add an Expense" << endl;
        cout << "2. Display Expense Summary" << endl;
        cout << "3. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addExpense(expenses, filename);
            break;
        case 2:
            displaySummary(expenses);
            break;
        case 3:
            cout << "Exiting the Expense Tracker. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
