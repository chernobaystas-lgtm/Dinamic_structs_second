#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <windows.h>
#include  <cassert>
using namespace std;

class Product {
public:
	Product(){
		cout << "constructor called" << endl;
	}
	Product(string name, string categoryName, double price) : name(name), categoryName(categoryName), price(price) {
		cout << "parameterized constructor called" << endl;
	}

	~Product() {
		cout << "destructor called" << endl;
	}

	string productTostring() const {
		return "Product Name: " + name + ", Category: " + categoryName + ", Price: " + to_string(price);
	}

	void show() const {
		cout << productTostring() << endl;
	}
	// Getters and Setters
	string getName() const {
		return name;
	}
	void setName(const string& name) {
		this->name = name;
	}
	string getCategoryName() const {
		return categoryName;
	}
	void setCategoryName(const string& categoryName) {
		this->categoryName = categoryName;
	}
	double getPrice() const {
		return price;
	}
	void setPrice(double price) {
		this->price = price;
	}

protected:
	string name{""};
	double price{0.0};
private:
	string categoryName{""};

};

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);


	return 0;
}
