// exercise 12: move semantics and rvalue references
// learn: move constructor, move assignment, std::move, rvalue references, performance optimization

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cstring>

// ==== class demonstrating move semantics ====

class Buffer {
private:
    int* data;
    size_t size;

public:
    // constructor
    Buffer(size_t s) : size(s), data(new int[s]) {
        std::cout << "constructor: allocated " << size << " ints" << std::endl;
        for (size_t i = 0; i < size; i++) {
            data[i] = i;
        }
    }

    // copy constructor (expensive)
    Buffer(const Buffer& other) : size(other.size), data(new int[other.size]) {
        std::cout << "copy constructor: copying " << size << " ints" << std::endl;
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    // move constructor (cheap)
    Buffer(Buffer&& other) noexcept : size(other.size), data(other.data) {
        std::cout << "move constructor: stealing " << size << " ints" << std::endl;
        other.data = nullptr;  // leave other in valid state
        other.size = 0;
    }

    // copy assignment operator
    Buffer& operator=(const Buffer& other) {
        std::cout << "copy assignment: copying " << other.size << " ints" << std::endl;
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (size_t i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // move assignment operator
    Buffer& operator=(Buffer&& other) noexcept {
        std::cout << "move assignment: stealing " << other.size << " ints" << std::endl;
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = other.data;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    // destructor
    ~Buffer() {
        if (data) {
            std::cout << "destructor: freeing " << size << " ints" << std::endl;
            delete[] data;
        } else {
            std::cout << "destructor: nothing to free (moved)" << std::endl;
        }
    }

    void display() const {
        if (data) {
            std::cout << "buffer[" << size << "]: ";
            for (size_t i = 0; i < (size < 5 ? size : 5); i++) {
                std::cout << data[i] << " ";
            }
            if (size > 5) std::cout << "...";
            std::cout << std::endl;
        } else {
            std::cout << "buffer is empty (moved)" << std::endl;
        }
    }
};

// ==== lvalue vs rvalue ====

void demonstrateLvalueRvalue() {
    std::cout << "\n=== lvalue vs rvalue ===" << std::endl;
    
    int x = 10;           // x is lvalue (has name, can take address)
    int y = 20;           // y is lvalue
    int z = x + y;        // x+y is rvalue (temporary, no name)
    
    std::cout << "x (lvalue): " << x << std::endl;
    std::cout << "x+y (rvalue): " << (x + y) << std::endl;
    
    // int& ref1 = x + y;     // error: can't bind lvalue ref to rvalue
    int&& ref2 = x + y;       // ok: rvalue reference to rvalue
    std::cout << "rvalue reference: " << ref2 << std::endl;
}

// ==== copy vs move ====

void demonstrateCopyVsMove() {
    std::cout << "\n=== copy vs move ===" << std::endl;
    
    std::cout << "\ncreating buf1:" << std::endl;
    Buffer buf1(1000);
    
    std::cout << "\ncopy (expensive):" << std::endl;
    Buffer buf2 = buf1;  // copy constructor
    
    std::cout << "\nmove (cheap):" << std::endl;
    Buffer buf3 = std::move(buf1);  // move constructor
    
    std::cout << "\nafter move:" << std::endl;
    buf1.display();  // buf1 is now empty
    buf3.display();  // buf3 has the data
}

// ==== std::move usage ====

void demonstrateStdMove() {
    std::cout << "\n=== std::move usage ===" << std::endl;
    
    std::vector<Buffer> vec;
    
    std::cout << "\nadding buffer with move:" << std::endl;
    Buffer temp(500);
    vec.push_back(std::move(temp));  // move into vector
    
    std::cout << "\ntemp after move:" << std::endl;
    temp.display();
}

// ==== return value optimization (RVO) ====

Buffer createBuffer(size_t size) {
    std::cout << "inside createBuffer" << std::endl;
    Buffer buf(size);
    return buf;  // RVO: no copy/move, constructed directly at return location
}

void demonstrateRVO() {
    std::cout << "\n=== return value optimization ===" << std::endl;
    
    std::cout << "\ncalling createBuffer:" << std::endl;
    Buffer buf = createBuffer(300);
    std::cout << "returned buffer:" << std::endl;
    buf.display();
}

// ==== practical example: string class ====

class MyString {
private:
    char* data;
    size_t length;

public:
    MyString(const char* str = "") {
        length = std::strlen(str);
        data = new char[length + 1];
        std::strcpy(data, str);
        std::cout << "MyString constructed: \"" << data << "\"" << std::endl;
    }

    // copy constructor
    MyString(const MyString& other) : length(other.length) {
        data = new char[length + 1];
        std::strcpy(data, other.data);
        std::cout << "MyString copied: \"" << data << "\"" << std::endl;
    }

    // move constructor
    MyString(MyString&& other) noexcept : data(other.data), length(other.length) {
        other.data = nullptr;
        other.length = 0;
        std::cout << "MyString moved" << std::endl;
    }

    // copy assignment
    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            std::strcpy(data, other.data);
            std::cout << "MyString copy assigned" << std::endl;
        }
        return *this;
    }

    // move assignment
    MyString& operator=(MyString&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            length = other.length;
            other.data = nullptr;
            other.length = 0;
            std::cout << "MyString move assigned" << std::endl;
        }
        return *this;
    }

    ~MyString() {
        delete[] data;
    }

    void display() const {
        if (data) {
            std::cout << "\"" << data << "\"" << std::endl;
        } else {
            std::cout << "(empty)" << std::endl;
        }
    }
};

void demonstratePracticalExample() {
    std::cout << "\n=== practical example: MyString ===" << std::endl;
    
    MyString s1("hello");
    MyString s2("world");
    
    std::cout << "\ncopy:" << std::endl;
    MyString s3 = s1;
    
    std::cout << "\nmove:" << std::endl;
    MyString s4 = std::move(s2);
    
    std::cout << "\nafter operations:" << std::endl;
    std::cout << "s1: "; s1.display();
    std::cout << "s2: "; s2.display();
    std::cout << "s3: "; s3.display();
    std::cout << "s4: "; s4.display();
}

int main() {
    std::cout << "=== move semantics and rvalue references ===" << std::endl;
    
    demonstrateLvalueRvalue();
    demonstrateCopyVsMove();
    demonstrateStdMove();
    demonstrateRVO();
    demonstratePracticalExample();
    
    std::cout << "\n=== key concepts ===" << std::endl;
    std::cout << "lvalue: has name, can take address (e.g., variables)" << std::endl;
    std::cout << "rvalue: temporary, no name (e.g., literals, x+y)" << std::endl;
    std::cout << "move constructor: steals resources instead of copying" << std::endl;
    std::cout << "std::move: cast lvalue to rvalue" << std::endl;
    std::cout << "noexcept: promises not to throw (important for move ops)" << std::endl;
    std::cout << "rule of five: destructor, copy/move constructors, copy/move assignments" << std::endl;
    
    return 0;
}