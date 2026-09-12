#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <windows.h>
#include <cassert>
using namespace std;


class Animal {
protected:
    string name;
    int age;
    double weight;

public:
    Animal(string name = "Unknown", int age = 0, double weight = 0.0)
        : name(name), age(age), weight(weight) {}

    string getName() const { return name; }
    int getAge() const { return age; }
    double getWeight() const { return weight; }

    int setName(string newName) {
        if (newName.empty()) {
            cerr << "Name can`t be empty" << endl;
            return -1;
        }
        name = newName;
        return 0;
    }

    int setAge(int newAge) {
        if (newAge < 0) {
            cerr << "Age can`t be less 0" << endl;
            return -1;
        }
        age = newAge;
        return 0;
    }

    int setWeight(double newWeight) {
        if (newWeight < 0) {
            cerr << "Weight can`t be less 0" << endl;
            return -1;
        }
        weight = newWeight;
        return 0;
    }

    virtual void display() const {
        cout << "Name: " << name << ", Age: " << age << ", Weight: " << weight << " kg" << endl;
    }
};

class PredatorAnimal : public Animal {
protected:
    string location;
    int averagePopulation;
    double populationChangeRate; // например 0.05 = +5% в год, -0.05 = -5%

public:
    PredatorAnimal(string name, int age, double weight,
        string location, int averagePopulation, double populationChangeRate)
        : Animal(name, age, weight),
        location(location),
        averagePopulation(averagePopulation),
        populationChangeRate(populationChangeRate) {}

    string getLocation() const { return location; }
    int getAveragePopulation() const { return averagePopulation; }
    double getPopulationChangeRate() const { return populationChangeRate; }

    int setLocation(string newLocation) {
        if (newLocation.empty()) {
            cerr << "Location can`t be empty" << endl;
            return -1;
        }
        location = newLocation;
        return 0;
    }

    int setAveragePopulation(int newPopulation) {
        if (newPopulation < 0) {
            cerr << "Population can`t be less 0" << endl;
            return -1;
        }
        averagePopulation = newPopulation;
        return 0;
    }

    int setPopulationChangeRate(double newRate) {
        populationChangeRate = newRate; 
        return 0;
    }

    bool isPopulationSuccessful() const {
        return populationChangeRate > 0 && averagePopulation > 100;
    }

    bool needsProtection() const {
        return averagePopulation < 100 || populationChangeRate < 0;
    }

    void display() const override {
        Animal::display();
        cout << "  Location: " << location
            << ", Population: " << averagePopulation
            << ", Change rate: " << populationChangeRate * 100 << "%"
            << (isPopulationSuccessful() ? "  [Successful]" : "")
            << (needsProtection() ? "  [Needs protection]" : "")
            << endl;
    }
};


int main() {

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);


    const int SIZE = 5;
    PredatorAnimal animals[SIZE] = {
        PredatorAnimal("Amur Tiger", 6, 180.0, "Russia, Primorsky Krai", 550, -0.02),
        PredatorAnimal("Gray Wolf", 4, 45.0, "Europe", 12000, 0.03),
        PredatorAnimal("African Lion", 8, 190.0, "Africa, Savannah", 20000, -0.01),
        PredatorAnimal("Snow Leopard", 5, 55.0, "Central Asia mountains", 60, -0.04),
        PredatorAnimal("Red Fox", 3, 6.5, "Worldwide", 500000, 0.05)
    };

    cout << "=== All animals ===" << endl;
    for (int i = 0; i < SIZE; i++) {
        animals[i].display();
    }

    int maxIndex = 0;
    for (int i = 1; i < SIZE; i++) {
        if (animals[i].getAveragePopulation() > animals[maxIndex].getAveragePopulation()) {
            maxIndex = i;
        }
    }

    cout << "\n=== Animal with the largest population ===" << endl;
    animals[maxIndex].display();

    cout << "\n=== Animals that need protection (lowest population) ===" << endl;
    for (int i = 0; i < SIZE; i++) {
        if (animals[i].needsProtection()) {
            animals[i].display();
        }
    }

    return 0;
}