// BankAccount.h - Header file with class declaration
#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>

class BankAccount {
private:
    const int accountNumber;
    std::string ownerName;
    double balance;

public:
    // constructor declaration only
    BankAccount(int accNum, std::string owner, double initialBalance = 0.0);
    
    // member function declarations only
    void deposit(double amount);
    void withdraw(double amount);
    void displayAccount() const;
    double getBalance() const;
};

#endif  // BANKACCOUNT_H
