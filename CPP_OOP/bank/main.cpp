#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

class BankAccount {
private:
    string name;
    int accountNumber;
    string password;
    double balance;

public:
    BankAccount(string n, int accNum, string pass, double initialBal) {
        name = n;
        accountNumber = accNum;
        password = pass;
        balance = initialBal;
    }

    int getAccountNumber() {
        return accountNumber;
    }

    bool login(string pass) {
        return password == pass;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited: $" << amount << endl;
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!" << endl;
        } else {
            balance -= amount;
            cout << "Withdrawn: $" << amount << endl;
        }
    }

    void showInfo() {
        cout << "\nAccount Holder: " << name << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: $" << balance << endl;
    }

    // Save account data to file
    void saveToFile(ofstream &outFile) {
        outFile << accountNumber << " " << name << " " << password << " " << balance << endl;
    }

    // Load account data from file
    static BankAccount loadFromFile(ifstream &inFile) {
        string n, pass;
        int accNum;
        double bal;
        inFile >> accNum >> n >> pass >> bal;
        return BankAccount(n, accNum, pass, bal);
    }
};

// Find account by account number
BankAccount* findAccount(vector<BankAccount>& accounts, int accNum) {
    for (auto& acc : accounts) {
        if (acc.getAccountNumber() == accNum) {
            return &acc;
        }
    }
    return nullptr;
}

// Load all accounts from file
void loadAccounts(vector<BankAccount>& accounts) {
    ifstream inFile("accounts.dat", ios::in);
    if (!inFile) {
        cout << "No existing account data found!" << endl;
        return;
    }

    while (inFile) {
        BankAccount acc = BankAccount::loadFromFile(inFile);
        if (inFile)
            accounts.push_back(acc);
    }
    inFile.close();
}

// Save all accounts to file
void saveAccounts(vector<BankAccount>& accounts) {
    ofstream outFile("accounts.dat", ios::out);
    for (auto& acc : accounts) { // Use reference here
        acc.saveToFile(outFile); // This will modify the object, so it's safe
    }
    outFile.close();
}


int main() {
    vector<BankAccount> accounts;
    loadAccounts(accounts); // Load accounts from file on startup

    int mainChoice;

    do {
        cout << "\n--- Main Menu ---\n";
        cout << "1. Create Account\n2. Login\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        if (mainChoice == 1) {
            // Create new account
            string name, password;
            int accNum;
            double balance;
            cin.ignore(); // clear buffer
            cout << "Enter your name: ";
            getline(cin, name);
            cout << "Enter account number: ";
            cin >> accNum;
            cout << "Set your password: ";
            cin >> password;
            cout << "Enter initial balance: ";
            cin >> balance;

            accounts.push_back(BankAccount(name, accNum, password, balance));
            saveAccounts(accounts); // Save updated accounts to file
            cout << "Account created successfully!" << endl;

        } else if (mainChoice == 2) {
            // Login
            int accNum;
            string password;
            cout << "Enter account number: ";
            cin >> accNum;
            cout << "Enter password: ";
            cin >> password;

            BankAccount* user = findAccount(accounts, accNum);
            if (user && user->login(password)) {
                cout << "Login successful!" << endl;

                int choice;
                double amount;
                do {
                    cout << "\n1. Deposit\n2. Withdraw\n3. Show Info\n4. Logout\n";
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice) {
                        case 1:
                            cout << "Enter amount to deposit: ";
                            cin >> amount;
                            user->deposit(amount);
                            break;
                        case 2:
                            cout << "Enter amount to withdraw: ";
                            cin >> amount;
                            user->withdraw(amount);
                            break;
                        case 3:
                            user->showInfo();
                            break;
                        case 4:
                            cout << "Logged out." << endl;
                            break;
                        default:
                            cout << "Invalid choice!" << endl;
                    }
                } while (choice != 4);
            } else {
                cout << "Login failed. Check credentials!" << endl;
            }

        } else if (mainChoice != 3) {
            cout << "Invalid option!" << endl;
        }

    } while (mainChoice != 3);

    saveAccounts(accounts); // Save accounts before exiting
    cout << "Goodbye!" << endl;
    return 0;
}
