// exercise 5: operator overloading
// learn: overloading operators, friend functions, returning references

#include <iostream>

class Vector2D {
private:
    double x;
    double y;

public:
    // constructor
    Vector2D(double xVal = 0.0, double yVal = 0.0) 
        : x(xVal), y(yVal) {
    }

    // display function
    void display() const {
        std::cout << "(" << x << ", " << y << ")";
    }

    // operator overloading: addition (+)
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    // operator overloading: subtraction (-)
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }

    // operator overloading: scalar multiplication (*)
    Vector2D operator*(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    // operator overloading: compound assignment (+=)
    Vector2D& operator+=(const Vector2D& other) {
        x += other.x;
        y += other.y;
        return *this;  // return reference to current object
    }

    // operator overloading: equality (==)
    bool operator==(const Vector2D& other) const {
        return (x == other.x && y == other.y);
    }

    // operator overloading: inequality (!=)
    bool operator!=(const Vector2D& other) const {
        return !(*this == other);  // reuse == operator
    }

    // friend function for output stream operator -> cout in this case
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }

    // getters
    double getX() const { return x; }
    double getY() const { return y; }
};

int main() {
    Vector2D v1(3.0, 4.0);
    Vector2D v2(1.0, 2.0);
    Vector2D v3;

    std::cout << "=== initial vectors ===" << std::endl;
    std::cout << "v1: " << v1 << std::endl;  // using << operator
    std::cout << "v2: " << v2 << std::endl;

    std::cout << "\n=== addition ===" << std::endl;
    v3 = v1 + v2;  // using + operator
    std::cout << "v1 + v2 = " << v3 << std::endl;

    std::cout << "\n=== subtraction ===" << std::endl;
    v3 = v1 - v2;  // using - operator
    std::cout << "v1 - v2 = " << v3 << std::endl;

    std::cout << "\n=== scalar multiplication ===" << std::endl;
    v3 = v1 * 2.5;  // using * operator
    std::cout << "v1 * 2.5 = " << v3 << std::endl;

    std::cout << "\n=== compound assignment ===" << std::endl;
    std::cout << "before: v1 = " << v1 << std::endl;
    v1 += v2;  // using += operator
    std::cout << "after v1 += v2: v1 = " << v1 << std::endl;

    std::cout << "\n=== comparison ===" << std::endl;
    Vector2D v4(4.0, 6.0);
    Vector2D v5(4.0, 6.0);
    std::cout << "v4: " << v4 << std::endl;
    std::cout << "v5: " << v5 << std::endl;
    std::cout << "v4 == v5: " << (v4 == v5 ? "true" : "false") << std::endl;
    std::cout << "v4 != v2: " << (v4 != v2 ? "true" : "false") << std::endl;

    return 0;
}
