// exercise 6: inheritance and access specifiers
// learn: base and derived classes, protected members, constructor chaining and method overriding

#include <iostream>
#include <string>

// base class
class Vehicle {
protected:  // accessible to derived classes
    std::string brand;
    int year;
    double price;

public:
    // constructor
    Vehicle(std::string b, int y, double p)
        : brand(b), year(y), price(p) {
        std::cout << "vehicle constructor called" << std::endl;
    }

    // member functions
    void displayBasicInfo() const {
        std::cout << "brand: " << brand << std::endl;
        std::cout << "year: " << year << std::endl;
        std::cout << "price: $" << price << std::endl;
    }

    // virtual function (can be overridden)
    virtual void displayType() const {
        std::cout << "type: generic vehicle" << std::endl;
    }

    // getters
    std::string getBrand() const { return brand; }
    int getYear() const { return year; }
};

// derived class 1: Car
class Car : public Vehicle {
private:
    int numDoors;
    std::string fuelType;

public:
    // constructor with initialization list (calls base constructor)
    Car(std::string b, int y, double p, int doors, std::string fuel)
        : Vehicle(b, y, p), numDoors(doors), fuelType(fuel) {
        std::cout << "car constructor called" << std::endl;
    }

    // override base class method
    void displayType() const override {
        std::cout << "type: car" << std::endl;
    }

    // additional method specific to Car
    void displayCarInfo() const {
        displayBasicInfo();
        displayType();
        std::cout << "doors: " << numDoors << std::endl;
        std::cout << "fuel: " << fuelType << std::endl;
    }
};

// derived class 2: Motorcycle
class Motorcycle : public Vehicle {
private:
    bool hasSidecar;
    int engineCC;

public:
    // constructor
    Motorcycle(std::string b, int y, double p, bool sidecar, int cc)
        : Vehicle(b, y, p), hasSidecar(sidecar), engineCC(cc) {
        std::cout << "motorcycle constructor called" << std::endl;
    }

    // override base class method
    void displayType() const override {
        std::cout << "type: motorcycle" << std::endl;
    }

    // additional method specific to Motorcycle
    void displayMotorcycleInfo() const {
        displayBasicInfo();
        displayType();
        std::cout << "sidecar: " << (hasSidecar ? "yes" : "no") << std::endl;
        std::cout << "engine: " << engineCC << "cc" << std::endl;
    }
};

// derived class 3: Truck (demonstrates multilevel inheritance could be added later)
class Truck : public Vehicle {
private:
    double cargoCapacity;  // in tons
    int numAxles;

public:
    // constructor
    Truck(std::string b, int y, double p, double capacity, int axles)
        : Vehicle(b, y, p), cargoCapacity(capacity), numAxles(axles) {
        std::cout << "truck constructor called" << std::endl;
    }

    // override base class method
    void displayType() const override {
        std::cout << "type: truck" << std::endl;
    }

    // additional method specific to Truck
    void displayTruckInfo() const {
        displayBasicInfo();
        displayType();
        std::cout << "cargo capacity: " << cargoCapacity << " tons" << std::endl;
        std::cout << "axles: " << numAxles << std::endl;
    }
};

int main() {
    std::cout << "=== creating a car ===" << std::endl;
    Car car1("toyota", 2023, 25000.0, 4, "hybrid");
    
    std::cout << "\n=== car information ===" << std::endl;
    car1.displayCarInfo();

    std::cout << "\n=== creating a motorcycle ===" << std::endl;
    Motorcycle bike1("harley-davidson", 2022, 15000.0, false, 1200);
    
    std::cout << "\n=== motorcycle information ===" << std::endl;
    bike1.displayMotorcycleInfo();

    std::cout << "\n=== creating a truck ===" << std::endl;
    Truck truck1("ford", 2021, 45000.0, 10.5, 3);
    
    std::cout << "\n=== truck information ===" << std::endl;
    truck1.displayTruckInfo();

    std::cout << "\n=== demonstrating polymorphism ===" << std::endl;
    Vehicle* vehicles[3];
    vehicles[0] = &car1;
    vehicles[1] = &bike1;
    vehicles[2] = &truck1;

    for (int i = 0; i < 3; i++) {
        std::cout << "\nvehicle " << i + 1 << ":" << std::endl;
        vehicles[i]->displayType();  // calls overridden method
        std::cout << "brand: " << vehicles[i]->getBrand() << std::endl;
    }

    return 0;
}
