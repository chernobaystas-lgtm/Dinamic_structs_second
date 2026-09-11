#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <windows.h>
#include <cassert>
using namespace std;

class Vehicle {
protected:
	string brand;
	double speed;
public:
	Vehicle(const string& brand, double speed) : brand(brand), speed(speed) {}
	Vehicle() : brand(""), speed(0) {}
	virtual ~Vehicle() {}

	// Getters

	string get_brand() const { return brand; }
	double get_speed() const { return speed; }

	// Setters

	int set_brand(string brand) {
		if (brand.empty()) {
			cerr << "Brand cannot be empty!" << endl;
			return -1;
		}
		this->brand = brand;
		return 0;
	}
	int set_speed(double speed) {
		if (speed < 0) {
			cerr << "Speed cannot be negative!" << endl;
			return -1;
		}
		this->speed = speed;
		return 0;
	}
	void displayInfo() const {
		cout << "Brand: " << brand << endl;
		cout << "Speed: " << speed << endl;
	}
};

class Car : public Vehicle {
private:
	int num_doors;
public:
	Car(const string& brand, double speed, int num_doors) : Vehicle(brand, speed), num_doors(num_doors) {}
	Car() : Vehicle(), num_doors(0) {}
	virtual ~Car() {}
	int get_num_doors() const { return num_doors; }
	int set_num_doors(int num_doors) {
		if (num_doors < 0) {
			cerr << "Number of doors cannot be negative!" << endl;
			return -1;
		}
		this->num_doors = num_doors;
		return 0;
	}
	void displayInfo() const {
		Vehicle::displayInfo();
		cout << "Number of doors: " << num_doors << endl;
	}
};

class Bicycle : public Vehicle {
private:
	bool hasBasket;
public:
	Bicycle(const string& brand, double speed, bool hasBasket) : Vehicle(brand, speed), hasBasket(hasBasket) {}
	Bicycle() : Vehicle(), hasBasket(false) {}
	virtual ~Bicycle() {}
	bool get_hasBasket() const { return hasBasket; }
	int set_hasBasket(bool hasBasket) {
		this->hasBasket = hasBasket;
		return 0;
	}
	void displayInfo() const {
		Vehicle::displayInfo();
		cout << "Has basket: " << (hasBasket ? "Yes" : "No") << endl;
	}

};


int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	Vehicle* vehicles = new Vehicle("Toyota Corolla", 180);
	vehicles-> displayInfo();
	cout << endl;

	return 0;
}