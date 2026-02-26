// exercise 2: constructors and member initialization
// learn: default constructor, parameterized constructor, initialization lists, const members

#include <iostream>
#include <string>

class BankAccount {
private:
    const int accountNumber;  // const member
    std::string ownerName;
    double balance;

public:
    // constructor with initialization list (modern C++ best practice)
    BankAccount(int accNum, std::string owner, double initialBalance = 0.0) 
        : accountNumber(accNum), ownerName(owner), balance(initialBalance) {
        std::cout << "Account created for " << ownerName << std::endl;
    }

    // member functions
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposited: $" << amount << std::endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            std::cout << "Withdrawn: $" << amount << std::endl;
        } else {
            std::cout << "Insufficient funds!" << std::endl;
        }
    }

    void displayAccount() const {  // const member function
        std::cout << "Account #" << accountNumber << std::endl;
        std::cout << "Owner: " << ownerName << std::endl;
        std::cout << "Balance: $" << balance << std::endl;
    }

    double getBalance() const {
        return balance;
    }
};

int main() {
    // creating accounts with different parameters
    BankAccount account1(1001, "john doe", 500.0);
    BankAccount account2(1002, "jane smith");  // uses default balance = 0.0

    std::cout << "\n=== account 1 ===" << std::endl;
    account1.displayAccount();

    std::cout << "\n=== account 2 ===" << std::endl;
    account2.displayAccount();

    std::cout << "\n=== transactions ===" << std::endl;
    account1.withdraw(200.0);
    account1.deposit(100.0);
    account2.deposit(1000.0);

    std::cout << "\n=== updated balances ===" << std::endl;
    account1.displayAccount();
    std::cout << std::endl;
    account2.displayAccount();

    return 0;
}
