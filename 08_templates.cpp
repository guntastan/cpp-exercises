// exercise 8: templates (generic programming)
// learn: function templates, class templates, template specialization, type parameters

#include <iostream>
#include <string>
#include <vector>

// ==== function templates ====

// basic function template
template <typename T>
T getMax(T a, T b) {
    return (a > b) ? a : b;
}

// function template with multiple type parameters
template <typename T, typename U>
void printPair(T first, U second) {
    std::cout << "(" << first << ", " << second << ")" << std::endl;
}

// function template with non-type parameter
template <typename T, int size>
void printArray(T arr[]) {
    std::cout << "[";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i];
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

// ===== class templates =====

// basic class template: simple container
template <typename T>
class Box {
private:
    T value;

public:
    Box(T val) : value(val) {
        std::cout << "box created with value: " << value << std::endl;
    }

    void setValue(T val) {
        value = val;
    }

    T getValue() const {
        return value;
    }

    void display() const {
        std::cout << "box contains: " << value << std::endl;
    }
};

// class template with multiple parameters
template <typename T, typename U>
class Pair {
private:
    T first;
    U second;

public:
    Pair(T f, U s) : first(f), second(s) {}

    T getFirst() const { return first; }
    U getSecond() const { return second; }

    void display() const {
        std::cout << "pair: (" << first << ", " << second << ")" << std::endl;
    }
};

// more complex class template: simple dynamic array
template <typename T>
class DynamicArray {
private:
    T* data;
    int size;
    int capacity;

    void resize() {
        capacity *= 2;
        T* newData = new T[capacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        std::cout << "array resized to capacity: " << capacity << std::endl;
    }

public:
    DynamicArray() : data(new T[2]), size(0), capacity(2) {
        std::cout << "dynamic array created" << std::endl;
    }

    ~DynamicArray() {
        delete[] data;
        std::cout << "dynamic array destroyed" << std::endl;
    }

    void add(T value) {
        if (size >= capacity) {
            resize();
        }
        data[size++] = value;
    }

    T get(int index) const {
        if (index >= 0 && index < size) {
            return data[index];
        }
        throw std::out_of_range("index out of range");
    }

    int getSize() const { return size; }

    void display() const {
        std::cout << "[";
        for (int i = 0; i < size; i++) {
            std::cout << data[i];
            if (i < size - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
};

// ==== template specialization ====

// primary template
template <typename T>
class Printer {
public:
    void print(T value) {
        std::cout << "generic print: " << value << std::endl;
    }
};

// specialized template for bool
template <>
class Printer<bool> {
public:
    void print(bool value) {
        std::cout << "boolean print: " << (value ? "true" : "false") << std::endl;
    }
};

// specialized template for const char*
template <>
class Printer<const char*> {
public:
    void print(const char* value) {
        std::cout << "string print: \"" << value << "\"" << std::endl;
    }
};

int main() {
    std::cout << "=== function templates ===" << std::endl;
    
    std::cout << "max(10, 20) = " << getMax(10, 20) << std::endl;
    std::cout << "max(5.5, 2.3) = " << getMax(5.5, 2.3) << std::endl;
    std::cout << "max('a', 'z') = " << getMax('a', 'z') << std::endl;
    
    std::cout << "\npairs with different types:" << std::endl;
    printPair(10, 20);
    printPair(3.14, "pi");
    printPair(std::string("hello"), 42);

    std::cout << "\n=== class templates: box ===" << std::endl;
    Box<int> intBox(42);
    intBox.display();
    
    Box<std::string> strBox("hello");
    strBox.display();
    
    Box<double> doubleBox(3.14159);
    doubleBox.display();

    std::cout << "\n=== class templates: pair ===" << std::endl;
    Pair<int, std::string> person(25, "alice");
    person.display();
    
    Pair<std::string, double> product("laptop", 999.99);
    product.display();

    std::cout << "\n=== class templates: dynamic array ===" << std::endl;
    DynamicArray<int> numbers;
    numbers.add(10);
    numbers.add(20);
    numbers.add(30);
    std::cout << "numbers: ";
    numbers.display();
    
    std::cout << "adding more elements (triggers resize):" << std::endl;
    numbers.add(40);
    numbers.add(50);
    std::cout << "numbers: ";
    numbers.display();
    
    std::cout << "\ndynamic array with strings:" << std::endl;
    DynamicArray<std::string> words;
    words.add("hello");
    words.add("world");
    words.add("templates");
    std::cout << "words: ";
    words.display();

    std::cout << "\n=== template specialization ===" << std::endl;
    Printer<int> intPrinter;
    intPrinter.print(42);
    
    Printer<double> doublePrinter;
    doublePrinter.print(3.14);
    
    Printer<bool> boolPrinter;  // uses specialized version
    boolPrinter.print(true);
    boolPrinter.print(false);
    
    Printer<const char*> strPrinter;  // uses specialized version
    strPrinter.print("hello world");

    std::cout << "\n=== templates enable code reuse ===" << std::endl;
    std::cout << "same function/class works with different types!" << std::endl;
    std::cout << "compiler generates specific versions for each type" << std::endl;

    return 0;
}
