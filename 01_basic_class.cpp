// exercise 1: basic class in C++
// learn: class definition, constructor, member variables, member functions

#include <iostream>
#include <string>

class Student {
private:
    std::string name;
    int age;
    double grade;

public:
    // constructor
    Student(std::string n, int a, double g) {
        name = n;
        age = a;
        grade = g;
    }

    // member functions
    void displayInfo() {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Age: " << age << std::endl;
        std::cout << "Grade: " << grade << std::endl;
    }

    void updateGrade(double newGrade) {
        grade = newGrade;
        std::cout << "Grade updated to: " << grade << std::endl;
    }

    // getter
    std::string getName() {
        return name;
    }
};

int main() {
    // create objects
    Student student1("Alice", 20, 85.5);
    Student student2("Bob", 22, 90.0);

    std::cout << "=== student 1 ===" << std::endl;
    student1.displayInfo();

    std::cout << "\n=== student 2 ===" << std::endl;
    student2.displayInfo();

    std::cout << "\n=== updating Grade ===" << std::endl;
    student1.updateGrade(92.5);

    std::cout << "\n=== updated Info ===" << std::endl;
    student1.displayInfo();

    return 0;
}
