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



class Toy : public Product {

public:
	Toy(int a, string m) : ageLimit{ a }, manufacturer{ m } {
		cout << "Toy constructor called" << endl;
	}
	Toy(int a, string m, string Toyname) : ageLimit{ a }, manufacturer{ m }{
		name = Toyname;
		cout << "Toy constructor called" << endl;
	}
	Toy(string nameToy, string categoryName, double price, int ageLimit, string manufacturer) : Product(nameToy, categoryName, price), ageLimit(ageLimit), manufacturer(manufacturer) {
	}

	~Toy() {
		cout << "Toy destructor called" << endl;
	}

	void setprice(double price) {
		if(ageLimit > 5 && this ->price-price >10) {
			this->price = price;
		}
	}

	string productTostring() const {
		return "Product Name: " + name + ", Category: " + getCategoryName() + ", Price: " + to_string(price) + ", Age Limit: " + to_string(ageLimit) + ", Manufacturer: " + manufacturer;
	}

	void show() const {
		cout << productTostring() << endl;
	}

private:
	string manufacturer{ "" };
	int ageLimit{ 0 };

};


int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	Product product1("Laptop", "Electronics", 999.99);
	product1.show();
	Toy toy1(3, "Hasbro", "Action Figure");
	toy1.show();
	return 0;
}
