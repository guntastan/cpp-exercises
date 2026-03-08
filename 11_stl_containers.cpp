// exercise 11: STL containers and algorithms
// learn: vector, map, set, algorithms, iterators, lambda functions

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <numeric>

// ==== vector examples ====

void demonstrateVector() {
    std::cout << "\n=== vector (dynamic array) ===" << std::endl;
    
    std::vector<int> numbers;
    
    // adding elements
    numbers.push_back(10);
    numbers.push_back(5);
    numbers.push_back(20);
    numbers.push_back(15);
    
    std::cout << "original: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // sorting
    std::sort(numbers.begin(), numbers.end());
    std::cout << "sorted: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // finding
    auto it = std::find(numbers.begin(), numbers.end(), 15);
    if (it != numbers.end()) {
        std::cout << "found 15 at index: " << (it - numbers.begin()) << std::endl;
    }
    
    // removing
    numbers.erase(numbers.begin() + 1);  // remove element at index 1
    std::cout << "after erase: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

// ==== map examples ====

void demonstrateMap() {
    std::cout << "\n=== map (key-value pairs) ===" << std::endl;
    
    std::map<std::string, int> ages;
    
    // inserting
    ages["alice"] = 25;
    ages["bob"] = 30;
    ages["charlie"] = 22;
    ages.insert({"david", 28});
    
    std::cout << "ages:" << std::endl;
    for (const auto& pair : ages) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    
    // accessing
    std::cout << "\nalice's age: " << ages["alice"] << std::endl;
    
    // checking existence
    if (ages.find("bob") != ages.end()) {
        std::cout << "bob exists in map" << std::endl;
    }
    
    // removing
    ages.erase("charlie");
    std::cout << "\nafter removing charlie:" << std::endl;
    for (const auto& pair : ages) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

// ==== set examples ====

void demonstrateSet() {
    std::cout << "\n=== set (unique sorted elements) ===" << std::endl;
    
    std::set<int> uniqueNumbers;
    
    // inserting (duplicates ignored)
    uniqueNumbers.insert(5);
    uniqueNumbers.insert(2);
    uniqueNumbers.insert(8);
    uniqueNumbers.insert(2);  // duplicate, ignored
    uniqueNumbers.insert(1);
    
    std::cout << "set (automatically sorted): ";
    for (int n : uniqueNumbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // checking existence
    if (uniqueNumbers.count(5) > 0) {
        std::cout << "5 is in the set" << std::endl;
    }
    
    // size
    std::cout << "set size: " << uniqueNumbers.size() << std::endl;
}

// ==== algorithms examples ====

void demonstrateAlgorithms() {
    std::cout << "\n=== STL algorithms ===" << std::endl;
    
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // count_if with lambda
    int evenCount = std::count_if(numbers.begin(), numbers.end(), 
        [](int n) { return n % 2 == 0; });
    std::cout << "even numbers count: " << evenCount << std::endl;
    
    // find_if with lambda
    auto it = std::find_if(numbers.begin(), numbers.end(),
        [](int n) { return n > 5; });
    if (it != numbers.end()) {
        std::cout << "first number > 5: " << *it << std::endl;
    }
    
    // transform (square each element)
    std::vector<int> squared(numbers.size());
    std::transform(numbers.begin(), numbers.end(), squared.begin(),
        [](int n) { return n * n; });
    
    std::cout << "squared: ";
    for (int n : squared) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // accumulate (sum)
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    std::cout << "sum: " << sum << std::endl;
    
    // all_of, any_of, none_of
    bool allPositive = std::all_of(numbers.begin(), numbers.end(),
        [](int n) { return n > 0; });
    std::cout << "all positive: " << (allPositive ? "yes" : "no") << std::endl;
    
    bool anyGreaterThan8 = std::any_of(numbers.begin(), numbers.end(),
        [](int n) { return n > 8; });
    std::cout << "any > 8: " << (anyGreaterThan8 ? "yes" : "no") << std::endl;
}

// ==== iterators examples ====

void demonstrateIterators() {
    std::cout << "\n=== iterators ===" << std::endl;
    
    std::vector<std::string> words = {"hello", "world", "cpp", "stl"};
    
    // forward iteration
    std::cout << "forward: ";
    for (auto it = words.begin(); it != words.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // reverse iteration
    std::cout << "reverse: ";
    for (auto it = words.rbegin(); it != words.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // const iterator
    std::cout << "with const iterator: ";
    for (auto it = words.cbegin(); it != words.cend(); ++it) {
        std::cout << *it << " ";
        // *it = "modified";  // error: cannot modify through const iterator
    }
    std::cout << std::endl;
}

// ==== practical example: student management ====

struct Student {
    std::string name;
    int id;
    double grade;
    
    Student(std::string n, int i, double g) : name(n), id(i), grade(g) {}
};

void demonstratePracticalExample() {
    std::cout << "\n=== practical example: student management ===" << std::endl;
    
    std::vector<Student> students;
    students.push_back(Student("alice", 101, 85.5));
    students.push_back(Student("bob", 102, 92.0));
    students.push_back(Student("charlie", 103, 78.5));
    students.push_back(Student("david", 104, 88.0));
    
    // sort by grade (descending)
    std::sort(students.begin(), students.end(),
        [](const Student& a, const Student& b) {
            return a.grade > b.grade;
        });
    
    std::cout << "students sorted by grade (descending):" << std::endl;
    for (const auto& s : students) {
        std::cout << s.name << " (id: " << s.id << "): " << s.grade << std::endl;
    }
    
    // find student with highest grade
    auto topStudent = std::max_element(students.begin(), students.end(),
        [](const Student& a, const Student& b) {
            return a.grade < b.grade;
        });
    std::cout << "\ntop student: " << topStudent->name 
              << " with grade " << topStudent->grade << std::endl;
    
    // average grade
    double avgGrade = std::accumulate(students.begin(), students.end(), 0.0,
        [](double sum, const Student& s) {
            return sum + s.grade;
        }) / students.size();
    std::cout << "average grade: " << avgGrade << std::endl;
    
    // count students above average
    int aboveAvg = std::count_if(students.begin(), students.end(),
        [avgGrade](const Student& s) {
            return s.grade > avgGrade;
        });
    std::cout << "students above average: " << aboveAvg << std::endl;
}

int main() {
    std::cout << "=== STL containers and algorithms ===" << std::endl;
    
    demonstrateVector();
    demonstrateMap();
    demonstrateSet();
    demonstrateAlgorithms();
    demonstrateIterators();
    demonstratePracticalExample();
    
    std::cout << "\n=== key concepts ===" << std::endl;
    std::cout << "vector: dynamic array, random access" << std::endl;
    std::cout << "map: key-value pairs, sorted by key" << std::endl;
    std::cout << "set: unique elements, automatically sorted" << std::endl;
    std::cout << "algorithms: powerful functions for common operations" << std::endl;
    std::cout << "iterators: generalized pointers for container traversal" << std::endl;
    std::cout << "lambda: inline anonymous functions" << std::endl;
    
    return 0;
}