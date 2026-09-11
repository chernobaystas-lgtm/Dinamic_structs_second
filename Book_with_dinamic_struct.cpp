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
	int set_speed(int speed) {
		if (speed < 0) {
			cerr << "Speed cannot be negative!" << endl;
			return -1;
		}
		this->speed = speed;
		return 0;
	}

};





int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);


}