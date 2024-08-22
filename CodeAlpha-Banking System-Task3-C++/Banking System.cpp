#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Class for Transactions
class Transaction {
public:
    string type;
    double amount;

    Transaction(string type, double amount) {
        this->type = type;
        this->amount = amount;
    }

    void displayTransaction() {
        cout << "Transaction Type: " << type << ", Amount: " << amount << endl;
    }
};

// Class for Account
class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int accountNumber) {
        this->accountNumber = accountNumber;
        balance = 0.0;
    }

    void deposit(double amount) {
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount));
        cout << "Deposit of " << amount << " successful. New Balance: " << balance << endl;
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            transactions.push_back(Transaction("Withdrawal", amount));
            cout << "Withdrawal of " << amount << " successful. New Balance: " << balance << endl;
        } else {
            cout << "Insufficient balance!" << endl;
        }
    }

    void transfer(Account &toAccount, double amount) {
        if (amount <= balance) {
            balance -= amount;
            toAccount.deposit(amount);
            transactions.push_back(Transaction("Transfer", amount));
            cout << "Transfer of " << amount << " to account " << toAccount.getAccountNumber() << " successful. New Balance: " << balance << endl;
        } else {
            cout << "Insufficient balance!" << endl;
        }
    }

    void viewAccountDetails() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: " << balance << endl;
        cout << "Recent Transactions: " << endl;
        for (Transaction &t : transactions) {
            t.displayTransaction();
        }
    }

    int getAccountNumber() {
        return accountNumber;
    }

    double getBalance() {
        return balance;
    }
};

// Class for Customer
class Customer {
private:
    string name;
    int customerID;
    vector<Account> accounts;

public:
    Customer(string name, int customerID) {
        this->name = name;
        this->customerID = customerID;
    }

    void createAccount(int accountNumber) {
        accounts.push_back(Account(accountNumber));
        cout << "Account " << accountNumber << " created for " << name << endl;
    }

    Account* getAccount(int accountNumber) {
        for (auto &account : accounts) {
            if (account.getAccountNumber() == accountNumber) {
                return &account;
            }
        }
        return nullptr;
    }

    void viewCustomerDetails() {
        cout << "Customer ID: " << customerID << ", Name: " << name << endl;
        cout << "Accounts: " << endl;
        for (auto &account : accounts) {
            account.viewAccountDetails();
        }
    }
};

// Class for Bank
class Bank {
private:
    vector<Customer> customers;

public:
    void addCustomer(string name, int customerID) {
        customers.push_back(Customer(name, customerID));
        cout << "Customer " << name << " added with ID " << customerID << endl;
    }

    Customer* getCustomer(int customerID) {
        for (auto &customer : customers) {
            if (customerID == customerID) {
                return &customer;
            }
        }
        return nullptr;
    }

    void performBankingService() {
        int customerID, accountNumber, toAccountNumber;
        double amount;
        char choice;

        cout << "Enter Customer ID: ";
        cin >> customerID;

        Customer* customer = getCustomer(customerID);
        if (customer == nullptr) {
            cout << "Customer not found!" << endl;
            return;
        }

        cout << "1. Create Account\n2. Deposit\n3. Withdraw\n4. Transfer\n5. View Account Details\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                cout << "Enter Account Number: ";
                cin >> accountNumber;
                customer->createAccount(accountNumber);
                break;

            case '2':
                cout << "Enter Account Number: ";
                cin >> accountNumber;
                cout << "Enter Amount to Deposit: ";
                cin >> amount;
                customer->getAccount(accountNumber)->deposit(amount);
                break;

            case '3':
                cout << "Enter Account Number: ";
                cin >> accountNumber;
                cout << "Enter Amount to Withdraw: ";
                cin >> amount;
                customer->getAccount(accountNumber)->withdraw(amount);
                break;

            case '4':
                cout << "Enter Your Account Number: ";
                cin >> accountNumber;
                cout << "Enter Destination Account Number: ";
                cin >> toAccountNumber;
                cout << "Enter Amount to Transfer: ";
                cin >> amount;
                customer->getAccount(accountNumber)->transfer(*customer->getAccount(toAccountNumber), amount);
                break;

            case '5':
                cout << "Enter Account Number: ";
                cin >> accountNumber;
                customer->getAccount(accountNumber)->viewAccountDetails();
                break;

            default:
                cout << "Invalid choice!" << endl;
                break;
        }
    }
};

int main() {
    Bank bank;

    bank.addCustomer("John Doe", 1001);
    bank.addCustomer("Jane Smith", 1002);

    while (true) {
        bank.performBankingService();
    }

    return 0;
}