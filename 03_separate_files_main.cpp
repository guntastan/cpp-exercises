// 03_separate_files_main.cpp - Main file that uses the class
#include <iostream>
#include "BankAccount.h"

int main() {
    // creating accounts
    BankAccount account1(1001, "john doe", 500.0);
    BankAccount account2(1002, "jane smith");

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
