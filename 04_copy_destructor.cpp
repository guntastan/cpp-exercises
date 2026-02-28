// exercise 4: copy constructor, destructor, and object lifetime
// learn: copy constructor, destructor, object copying, resource management

#include <iostream>
#include <string>

class Book {
private:
    std::string title;
    std::string author;
    int* pages;  // using pointer to demonstrate deep copy

public:
    // regular constructor
    Book(std::string t, std::string a, int p) 
        : title(t), author(a), pages(new int(p)) {
        std::cout << "Constructor: Creating book \"" << title << "\"" << std::endl;
    }

    // copy constructor (deep copy)
    Book(const Book& other) 
        : title(other.title), author(other.author), pages(new int(*other.pages)) {
        std::cout << "Copy Constructor: Copying book \"" << title << "\"" << std::endl;
    }

    // destructor
    ~Book() {
        std::cout << "Destructor: Destroying book \"" << title << "\"" << std::endl;
        delete pages;
    }

    // member functions
    void displayInfo() const {
        std::cout << "Title: " << title << std::endl;
        std::cout << "Author: " << author << std::endl;
        std::cout << "Pages: " << *pages << std::endl;
    }

    void setPages(int p) {
        *pages = p;
    }

    std::string getTitle() const {
        return title;
    }
};

// function that takes object by value (triggers copy constructor)
void printBook(Book b) {
    std::cout << "\n--- Inside printBook function ---" << std::endl;
    b.displayInfo();
    std::cout << "--- Leaving printBook function ---" << std::endl;
}

int main() {
    std::cout << "=== Creating book1 ===" << std::endl;
    Book book1("1984", "George Orwell", 328);

    std::cout << "\n=== Creating book2 as copy of book1 ===" << std::endl;
    Book book2 = book1;  // copy constructor called -> pass by value

    std::cout << "\n=== Original book1 ===" << std::endl;
    book1.displayInfo();

    std::cout << "\n=== Copied book2 ===" << std::endl;
    book2.displayInfo();

    std::cout << "\n=== Modifying book2 pages ===" << std::endl;
    book2.setPages(350);
    
    std::cout << "\n=== After modification ===" << std::endl;
    std::cout << "Book1 pages: ";
    book1.displayInfo();
    std::cout << "\nBook2 pages: ";
    book2.displayInfo();

    std::cout << "\n=== Passing book1 to function (by value) ===" << std::endl;
    printBook(book1);

    std::cout << "\n=== Back in main, exiting program ===" << std::endl;
    // destructors will be called automatically here
    
    return 0;
}
