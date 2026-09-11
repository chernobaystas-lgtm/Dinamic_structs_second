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
	Vehicle(string brand, double speed) : brand(brand), speed(speed) {}
	Vehicle() : brand(""), speed(0) {}
	~Vehicle() {}

	// Getters

	string get_brand() const { return brand; }
	double get_speed() const { return speed; }


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
	void display() const {
		cout << "Brand: " << brand << endl;
		cout << "Speed: " << speed << endl;
	}
};

class Car : public Vehicle {
private:
	int num_doors;
public:
	Car(string brand, double speed, int num_doors) : Vehicle(brand, speed), num_doors(num_doors) {}
	Car() : Vehicle(), num_doors(0) {}
	~Car() {}
	int get_num_doors() const { return num_doors; }
	int set_num_doors(int num_doors) {
		if (num_doors < 0) {
			cerr << "Number of doors cannot be negative!" << endl;
			return -1;
		}
		this->num_doors = num_doors;
		return 0;
	}
	void display() const {
		Vehicle::display();
		cout << "Number of doors: " << num_doors << endl;
	}
};

class Bycle : public Vehicle {
private:
	bool hasBasket;
public:
	Bycle(string brand, double speed, bool hasBasket) : Vehicle(brand, speed), hasBasket(hasBasket) {}
	Bycle() : Vehicle(), hasBasket(false) {}
	~Bycle() {}
	bool get_hasBasket() const { return hasBasket; }
	int set_hasBasket(bool hasBasket) {
		this->hasBasket = hasBasket;
		return 0;
	}
	void display() const {
		Vehicle::display();
		cout << "Has basket: " << (hasBasket ? "Yes" : "No") << endl;
	}

};


int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);


}