// exercise 9: exception handling
// learn: try-catch blocks, throw, standard exceptions, custom exceptions, stack unwinding

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

// ==== custom exception classes ====

// custom exception inheriting from std::exception
class InvalidAgeException : public std::exception {
private:
    std::string message;
    int age;

public:
    InvalidAgeException(int a) : age(a) {
        message = "invalid age: " + std::to_string(age);
    }

    const char* what() const noexcept override {
        return message.c_str();
    }

    int getAge() const { return age; }
};

class InsufficientFundsException : public std::exception {
private:
    double balance;
    double amount;
    std::string message;

public:
    InsufficientFundsException(double bal, double amt) : balance(bal), amount(amt) {
        message = "insufficient funds: balance=" + std::to_string(balance) + 
                  ", requested=" + std::to_string(amount);
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

// ==== classes that throw exceptions ====

class Person {
private:
    std::string name;
    int age;

public:
    Person(std::string n, int a) : name(n) {
        if (a < 0 || a > 150) {
            throw InvalidAgeException(a);
        }
        age = a;
        std::cout << "person created: " << name << ", age " << age << std::endl;
    }

    void setAge(int a) {
        if (a < 0 || a > 150) {
            throw InvalidAgeException(a);
        }
        age = a;
    }

    void display() const {
        std::cout << name << " is " << age << " years old" << std::endl;
    }
};

class BankAccount {
private:
    std::string owner;
    double balance;

public:
    BankAccount(std::string o, double b) : owner(o), balance(b) {
        if (b < 0) {
            throw std::invalid_argument("initial balance cannot be negative");
        }
        std::cout << "account created for " << owner << " with balance $" << balance << std::endl;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("deposit amount must be positive");
        }
        balance += amount;
        std::cout << "deposited $" << amount << ", new balance: $" << balance << std::endl;
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("withdrawal amount must be positive");
        }
        if (amount > balance) {
            throw InsufficientFundsException(balance, amount);
        }
        balance -= amount;
        std::cout << "withdrew $" << amount << ", new balance: $" << balance << std::endl;
    }

    double getBalance() const { return balance; }
};

// safe array with bounds checking
template <typename T>
class SafeArray {
private:
    T* data;
    int size;

public:
    SafeArray(int s) : size(s) {
        if (s <= 0) {
            throw std::invalid_argument("array size must be positive");
        }
        data = new T[size];
        std::cout << "safe array created with size " << size << std::endl;
    }

    ~SafeArray() {
        delete[] data;
        std::cout << "safe array destroyed" << std::endl;
    }

    T& at(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("index " + std::to_string(index) + 
                                   " out of range [0, " + std::to_string(size-1) + "]");
        }
        return data[index];
    }

    int getSize() const { return size; }
};

// ==== functions demonstrating exception handling ====

void demonstrateBasicTryCatch() {
    std::cout << "\n=== basic try-catch ===" << std::endl;
    
    try {
        std::cout << "trying to create person with invalid age..." << std::endl;
        Person p("bob", 200);  // throws InvalidAgeException
        p.display();  // never reached
    }
    catch (const InvalidAgeException& e) {
        std::cout << "caught custom exception: " << e.what() << std::endl;
        std::cout << "invalid age was: " << e.getAge() << std::endl;
    }
}

void demonstrateMultipleCatch() {
    std::cout << "\n=== multiple catch blocks ===" << std::endl;
    
    BankAccount account("alice", 100.0);
    
    try {
        account.deposit(50.0);
        account.withdraw(200.0);  // throws InsufficientFundsException
    }
    catch (const InsufficientFundsException& e) {
        std::cout << "caught insufficient funds: " << e.what() << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "caught invalid argument: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {  // catches any std::exception
        std::cout << "caught general exception: " << e.what() << std::endl;
    }
}

void demonstrateStackUnwinding() {
    std::cout << "\n=== stack unwinding (destructors called) ===" << std::endl;
    
    try {
        SafeArray<int> arr(5);
        arr.at(0) = 10;
        arr.at(1) = 20;
        std::cout << "accessing valid indices works fine" << std::endl;
        
        std::cout << "now accessing invalid index..." << std::endl;
        arr.at(10) = 99;  // throws out_of_range
        
        std::cout << "this line never executes" << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cout << "caught out of range: " << e.what() << std::endl;
        std::cout << "(notice destructor was called during unwinding)" << std::endl;
    }
}

void demonstrateRethrow() {
    std::cout << "\n=== rethrowing exceptions ===" << std::endl;
    
    try {
        try {
            Person p("charlie", -5);
        }
        catch (const InvalidAgeException& e) {
            std::cout << "inner catch: " << e.what() << std::endl;
            std::cout << "rethrowing..." << std::endl;
            throw;  // rethrow the same exception
        }
    }
    catch (const InvalidAgeException& e) {
        std::cout << "outer catch: caught rethrown exception" << std::endl;
    }
}

void demonstrateNoexceptFunction() noexcept {
    std::cout << "\n=== noexcept function ===" << std::endl;
    std::cout << "this function promises not to throw exceptions" << std::endl;
    // if it does throw, std::terminate() is called
}

int main() {
    std::cout << "=== exception handling demonstration ===" << std::endl;

    demonstrateBasicTryCatch();
    demonstrateMultipleCatch();
    demonstrateStackUnwinding();
    demonstrateRethrow();
    demonstrateNoexceptFunction();

    std::cout << "\n=== standard exception hierarchy ===" << std::endl;
    std::cout << "std::exception (base)" << std::endl;
    std::cout << "  ├── std::logic_error" << std::endl;
    std::cout << "  │   ├── std::invalid_argument" << std::endl;
    std::cout << "  │   ├── std::out_of_range" << std::endl;
    std::cout << "  │   └── std::length_error" << std::endl;
    std::cout << "  └── std::runtime_error" << std::endl;
    std::cout << "      ├── std::overflow_error" << std::endl;
    std::cout << "      └── std::underflow_error" << std::endl;

    std::cout << "\n=== best practices ===" << std::endl;
    std::cout << "1. throw by value, catch by const reference" << std::endl;
    std::cout << "2. inherit from std::exception for custom exceptions" << std::endl;
    std::cout << "3. use RAII to ensure cleanup (destructors always run)" << std::endl;
    std::cout << "4. catch specific exceptions before general ones" << std::endl;
    std::cout << "5. don't throw from destructors" << std::endl;

    return 0;
}