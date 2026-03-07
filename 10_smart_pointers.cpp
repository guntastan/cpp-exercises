// exercise 10: smart pointers and RAII
// learn: unique_ptr, shared_ptr, weak_ptr, automatic memory management, RAII pattern

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// simple class to demonstrate RAII
class Resource {
private:
    std::string name;
    int* data;

public:
    Resource(std::string n) : name(n), data(new int(42)) {
        std::cout << "resource '" << name << "' acquired" << std::endl;
    }

    ~Resource() {
        delete data;
        std::cout << "resource '" << name << "' released" << std::endl;
    }

    void use() {
        std::cout << "using resource '" << name << "' with value: " << *data << std::endl;
    }

    std::string getName() const { return name; }
};

// ==== unique_ptr examples ====

void demonstrateUniquePtr() {
    std::cout << "\n=== unique_ptr (exclusive ownership) ===" << std::endl;
    
    // creating unique_ptr
    std::unique_ptr<Resource> ptr1(new Resource("resource1"));
    ptr1->use();
    
    // better: use make_unique (c++14)
    auto ptr2 = std::make_unique<Resource>("resource2");
    ptr2->use();
    
    // cannot copy unique_ptr
    // std::unique_ptr<Resource> ptr3 = ptr1;  // ERROR: deleted copy constructor
    
    // but can move (transfer ownership)
    std::unique_ptr<Resource> ptr3 = std::move(ptr1);
    std::cout << "after move, ptr1 is: " << (ptr1 == nullptr ? "nullptr" : "valid") << std::endl;
    std::cout << "ptr3 now owns the resource:" << std::endl;
    ptr3->use();
    
    std::cout << "unique_ptrs will automatically delete resources when going out of scope" << std::endl;
}

// ==== shared_ptr examples ====

void demonstrateSharedPtr() {
    std::cout << "\n=== shared_ptr (shared ownership) ===" << std::endl;
    
    // creating shared_ptr
    std::shared_ptr<Resource> ptr1 = std::make_shared<Resource>("shared1");
    std::cout << "ptr1 reference count: " << ptr1.use_count() << std::endl;
    
    // can copy shared_ptr (increases reference count)
    std::shared_ptr<Resource> ptr2 = ptr1;
    std::cout << "after copy, reference count: " << ptr1.use_count() << std::endl;
    
    {
        std::shared_ptr<Resource> ptr3 = ptr1;
        std::cout << "in inner scope, reference count: " << ptr1.use_count() << std::endl;
        ptr3->use();
    }  // ptr3 destroyed here
    
    std::cout << "after inner scope, reference count: " << ptr1.use_count() << std::endl;
    
    // resource only deleted when last shared_ptr is destroyed
    std::cout << "resource will be deleted when last shared_ptr goes out of scope" << std::endl;
}

// ==== weak_ptr examples ====

class Node {
public:
    std::string name;
    std::shared_ptr<Node> next;  // strong reference
    std::weak_ptr<Node> prev;    // weak reference (breaks cycle)
    
    Node(std::string n) : name(n) {
        std::cout << "node '" << name << "' created" << std::endl;
    }
    
    ~Node() {
        std::cout << "node '" << name << "' destroyed" << std::endl;
    }
};

void demonstrateWeakPtr() {
    std::cout << "\n=== weak_ptr (non-owning reference) ===" << std::endl;
    
    auto node1 = std::make_shared<Node>("node1");
    auto node2 = std::make_shared<Node>("node2");
    
    // create circular reference using weak_ptr
    node1->next = node2;
    node2->prev = node1;  // weak_ptr doesn't increase reference count
    
    std::cout << "node1 reference count: " << node1.use_count() << std::endl;
    std::cout << "node2 reference count: " << node2.use_count() << std::endl;
    
    // accessing through weak_ptr
    if (auto prevNode = node2->prev.lock()) {  // lock() returns shared_ptr
        std::cout << "node2's previous node is: " << prevNode->name << std::endl;
    }
    
    std::cout << "weak_ptr prevents memory leaks from circular references" << std::endl;
}

// ==== comparing raw pointers vs smart pointers ====

void demonstrateRawPointerProblems() {
    std::cout << "\n=== problems with raw pointers ===" << std::endl;
    
    // problem 1: memory leak
    Resource* raw1 = new Resource("raw1");
    raw1->use();
    // forgot to delete! memory leak!
    
    // problem 2: double delete
    Resource* raw2 = new Resource("raw2");
    Resource* raw3 = raw2;
    delete raw2;
    // delete raw3;  // ERROR: double delete! undefined behavior
    
    // problem 3: dangling pointer
    Resource* raw4 = new Resource("raw4");
    delete raw4;
    // raw4->use();  // ERROR: use after delete! undefined behavior
    
    std::cout << "raw pointers require manual memory management" << std::endl;
}

void demonstrateSmartPointerSolutions() {
    std::cout << "\n=== smart pointers solve these problems ===" << std::endl;
    
    // automatic cleanup - no memory leaks
    {
        auto ptr1 = std::make_unique<Resource>("smart1");
        ptr1->use();
    }  // automatically deleted here
    
    // no double delete possible
    auto ptr2 = std::make_shared<Resource>("smart2");
    auto ptr3 = ptr2;  // both point to same object
    // when both go out of scope, only deleted once
    
    // no dangling pointers with shared_ptr
    std::shared_ptr<Resource> ptr4;
    {
        auto ptr5 = std::make_shared<Resource>("smart3");
        ptr4 = ptr5;  // ptr4 keeps object alive
    }  // ptr5 destroyed, but object still alive because ptr4 exists
    ptr4->use();
    
    std::cout << "smart pointers provide automatic, safe memory management" << std::endl;
}

// ==== using smart pointers with containers ====

void demonstrateSmartPointersInContainers() {
    std::cout << "\n=== smart pointers in containers ===" << std::endl;
    
    std::vector<std::unique_ptr<Resource>> resources;
    
    // add resources (must use move because unique_ptr can't be copied)
    resources.push_back(std::make_unique<Resource>("res1"));
    resources.push_back(std::make_unique<Resource>("res2"));
    resources.push_back(std::make_unique<Resource>("res3"));
    
    std::cout << "using resources in vector:" << std::endl;
    for (const auto& res : resources) {
        res->use();
    }
    
    std::cout << "all resources will be automatically cleaned up when vector is destroyed" << std::endl;
}

// ==== custom deleters ====

void customDeleter(Resource* ptr) {
    std::cout << "custom deleter called for: " << ptr->getName() << std::endl;
    delete ptr;
}

void demonstrateCustomDeleter() {
    std::cout << "\n=== custom deleters ===" << std::endl;
    
    std::unique_ptr<Resource, decltype(&customDeleter)> ptr(
        new Resource("custom"),
        customDeleter
    );
    
    ptr->use();
    std::cout << "custom deleter will be called automatically" << std::endl;
}

int main() {
    std::cout << "=== smart pointers and RAII demonstration ===" << std::endl;

    demonstrateUniquePtr();
    demonstrateSharedPtr();
    demonstrateWeakPtr();
    
    demonstrateRawPointerProblems();
    demonstrateSmartPointerSolutions();
    
    demonstrateSmartPointersInContainers();
    demonstrateCustomDeleter();

    std::cout << "\n=== smart pointer comparison ===" << std::endl;
    std::cout << "unique_ptr:" << std::endl;
    std::cout << "  - exclusive ownership" << std::endl;
    std::cout << "  - cannot be copied, only moved" << std::endl;
    std::cout << "  - zero overhead compared to raw pointer" << std::endl;
    std::cout << "  - use when: one owner, clear ownership transfer" << std::endl;
    
    std::cout << "\nshared_ptr:" << std::endl;
    std::cout << "  - shared ownership with reference counting" << std::endl;
    std::cout << "  - can be copied freely" << std::endl;
    std::cout << "  - small overhead (reference count storage)" << std::endl;
    std::cout << "  - use when: multiple owners, unclear lifetime" << std::endl;
    
    std::cout << "\nweak_ptr:" << std::endl;
    std::cout << "  - non-owning reference to shared_ptr" << std::endl;
    std::cout << "  - doesn't affect reference count" << std::endl;
    std::cout << "  - use when: observing without owning, breaking cycles" << std::endl;

    std::cout << "\n=== RAII principles ===" << std::endl;
    std::cout << "1. acquire resources in constructor" << std::endl;
    std::cout << "2. release resources in destructor" << std::endl;
    std::cout << "3. resources automatically managed by object lifetime" << std::endl;
    std::cout << "4. exception-safe (destructor always called)" << std::endl;

    return 0;
}