// exercise 7: abstract classes and pure virtual functions
// learn: abstract base classes, pure virtual functions, interfaces, enforcing implementation

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// abstract base class (has at least one pure virtual function)
class Shape {
protected:
    std::string name;
    std::string color;

public:
    // constructor
    Shape(std::string n, std::string c) : name(n), color(c) {
        std::cout << "shape constructor: " << name << std::endl;
    }

    // virtual destructor (important for abstract classes)
    virtual ~Shape() {
        std::cout << "shape destructor: " << name << std::endl;
    }

    // pure virtual functions (= 0 makes them pure virtual)
    // derived classes MUST implement these
    virtual double calculateArea() const = 0;
    virtual double calculatePerimeter() const = 0;
    virtual void draw() const = 0;

    // regular virtual function (can be overridden but has default implementation)
    virtual void displayInfo() const {
        std::cout << "shape: " << name << std::endl;
        std::cout << "color: " << color << std::endl;
        std::cout << "area: " << calculateArea() << std::endl;
        std::cout << "perimeter: " << calculatePerimeter() << std::endl;
    }

    // regular member function
    std::string getName() const { return name; }
    std::string getColor() const { return color; }
};

// concrete class 1: Circle
class Circle : public Shape {
private:
    double radius;

public:
    Circle(std::string c, double r) 
        : Shape("circle", c), radius(r) {
        std::cout << "circle constructor" << std::endl;
    }

    ~Circle() {
        std::cout << "circle destructor" << std::endl;
    }

    // implement pure virtual functions
    double calculateArea() const override {
        return M_PI * radius * radius;
    }

    double calculatePerimeter() const override {
        return 2 * M_PI * radius;
    }

    void draw() const override {
        std::cout << "drawing circle with radius " << radius << std::endl;
    }

    double getRadius() const { return radius; }
};

// concrete class 2: Rectangle
class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(std::string c, double w, double h)
        : Shape("rectangle", c), width(w), height(h) {
        std::cout << "rectangle constructor" << std::endl;
    }

    ~Rectangle() {
        std::cout << "rectangle destructor" << std::endl;
    }

    // implement pure virtual functions
    double calculateArea() const override {
        return width * height;
    }

    double calculatePerimeter() const override {
        return 2 * (width + height);
    }

    void draw() const override {
        std::cout << "drawing rectangle " << width << "x" << height << std::endl;
    }
};

// concrete class 3: Triangle
class Triangle : public Shape {
private:
    double side1, side2, side3;

public:
    Triangle(std::string c, double s1, double s2, double s3)
        : Shape("triangle", c), side1(s1), side2(s2), side3(s3) {
        std::cout << "triangle constructor" << std::endl;
    }

    ~Triangle() {
        std::cout << "triangle destructor" << std::endl;
    }

    // implement pure virtual functions
    double calculateArea() const override {
        // using heron's formula
        double s = (side1 + side2 + side3) / 2.0;
        return sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }

    double calculatePerimeter() const override {
        return side1 + side2 + side3;
    }

    void draw() const override {
        std::cout << "drawing triangle with sides " << side1 << ", " << side2 << ", " << side3 << std::endl;
    }
};

// function that works with any Shape (polymorphism)
void processShape(const Shape& shape) {
    std::cout << "\n--- processing shape ---" << std::endl;
    shape.displayInfo();
    shape.draw();
}

int main() {
    std::cout << "=== creating shapes ===" << std::endl;
    
    // cannot create Shape object directly (it's abstract)
    // Shape s("shape", "white");  // ERROR: cannot instantiate abstract class
    
    Circle circle("red", 5.0);
    std::cout << std::endl;
    
    Rectangle rect("blue", 4.0, 6.0);
    std::cout << std::endl;
    
    Triangle tri("green", 3.0, 4.0, 5.0);
    std::cout << std::endl;

    std::cout << "\n=== displaying shape information ===" << std::endl;
    circle.displayInfo();
    std::cout << std::endl;
    
    rect.displayInfo();
    std::cout << std::endl;
    
    tri.displayInfo();

    std::cout << "\n=== polymorphism with abstract base class ===" << std::endl;
    processShape(circle);
    processShape(rect);
    processShape(tri);

    std::cout << "\n=== using pointers to abstract base class ===" << std::endl;
    std::vector<Shape*> shapes;
    shapes.push_back(&circle);
    shapes.push_back(&rect);
    shapes.push_back(&tri);

    double totalArea = 0.0;
    for (const auto& shape : shapes) {
        std::cout << "\n" << shape->getName() << " (" << shape->getColor() << ")" << std::endl;
        std::cout << "area: " << shape->calculateArea() << std::endl;
        totalArea += shape->calculateArea();
    }
    
    std::cout << "\ntotal area of all shapes: " << totalArea << std::endl;

    std::cout << "\n=== demonstrating dynamic polymorphism ===" << std::endl;
    Shape* ptr = &circle;
    std::cout << "pointer to circle:" << std::endl;
    ptr->draw();
    
    ptr = &rect;
    std::cout << "same pointer, now to rectangle:" << std::endl;
    ptr->draw();

    std::cout << "\n=== end of program (destructors will be called) ===" << std::endl;

    return 0;
}
