# cpp-exercises

daily c++ practice exercises covering fundamental concepts and modern features. built for reference and maintaining proficiency. each exercise is self-contained.

## exercises

| # | topic | concepts |
|---|-------|----------|
| 01 | basic classes | class structure, member variables, methods |
| 02 | constructors | default/parameterized constructors, initialization lists |
| 03 | separate files | header/implementation separation, include guards |
| 04 | copy & destructor | copy constructor, destructor, resource management |
| 05 | operator overloading | operator functions, friend functions |
| 06 | inheritance | base/derived classes, polymorphism, virtual functions |
| 07 | abstract classes | pure virtual functions, abstract base classes |
| 08 | templates | function/class templates, specialization |
| 09 | exception handling | try-catch blocks, custom exceptions, stack unwinding |
| 10 | smart pointers | unique_ptr, shared_ptr, weak_ptr, raii |
| 11 | stl containers | vector, map, set, algorithms, iterators, lambda functions |
| 12 | move semantics | move constructor, move assignment, std::move, rvalue references |
| 13 | concurrency | std::thread, mutex, lock_guard, condition_variable, async, future |
| 14 | file i/o and filesystem | ifstream, ofstream, fstream, stringstream, filesystem, text and binary files |
| 15 | regular expressions | |

## compile

```bash
g++ -std=c++14 <file>.cpp -o out && ./out
```