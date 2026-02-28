// BankAccount.cpp - Implementation file
#include "BankAccount.h"
#include <iostream>

// constructor implementation
BankAccount::BankAccount(int accNum, std::string owner, double initialBalance)
    : accountNumber(accNum), ownerName(owner), balance(initialBalance) {
    std::cout << "Account created for " << ownerName << std::endl;
}

// member function implementations
void BankAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        std::cout << "Deposited: $" << amount << std::endl;
    }
}

void BankAccount::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        std::cout << "Withdrawn: $" << amount << std::endl;
    } else {
        std::cout << "Insufficient funds!" << std::endl;
    }
}

void BankAccount::displayAccount() const {
    std::cout << "Account #" << accountNumber << std::endl;
    std::cout << "Owner: " << ownerName << std::endl;
    std::cout << "Balance: $" << balance << std::endl;
}

double BankAccount::getBalance() const {
    return balance;
}
