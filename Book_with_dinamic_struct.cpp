#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <windows.h>
#include <cassert>
using namespace std;

class Pet {
protected:
	string name;
	string  breed;
	string color;
	string PetParent_name;
	double weight;
	double height;
	int age;

public:
	Pet() : name(""), breed(""), color(""), PetParent_name(""), weight(0.0), height(0.0), age(0) {}
	Pet(const string& name, const string& breed, const string& color, const string& PetParent_name, double weight, double height, int age)
		: name(name), breed(breed), color(color), PetParent_name(PetParent_name), weight(weight), height(height), age(age) {}
	virtual ~Pet() {}

	// For sound and type of pet, we can use virtual functions to allow derived classes to override these behaviors.

	virtual string getSound() const = 0;
	virtual string getType() const = 0;



	// Getters
	string getName() const { return name; }
	string getBreed() const { return breed; }
	string getColor() const { return color; }
	string getPetParent_name() const { return PetParent_name; }
	double getWeight() const { return weight; }
	double getHeight() const { return height; }
	int getAge() const { return age; }

	// Setters

	string setName(const string& name) {
		if (name.empty()) {
			cerr << "Name cannot be empty!" << endl;
			return "";
		}
		this->name = name;
		return this->name;
	}
	string setBreed(const string& breed) {
		if (breed.empty()) {
			cerr << "Breed cannot be empty!" << endl;
			return "";
		}
		this->breed = breed;
		return this->breed;
	}
	string setColor(const string& color) {
		if (color.empty()) {
			cerr << "Color cannot be empty!" << endl;
			return "";
		}
		this->color = color;
		return this->color;
	}
	string  setPetParent_name(const string& PetParent_name) {
		if (PetParent_name.empty()) {
			cerr << "Pet parent name cannot be empty!" << endl;
			return "";
		}
		this->PetParent_name = PetParent_name;
		return this->PetParent_name;
	}
	double setWeight(double weight) {
		if (weight < 0) {
			cerr << "Weight cannot be negative!" << endl;
			return -1;
		}
		this->weight = weight;
		return this->weight;
	}
	double setHeight(double height) {
		if (height < 0) {
			cerr << "Height cannot be negative!" << endl;
			return -1;
		}
		this->height = height;
		return this->height;
	}
	int setAge(int age) {
		if (age < 0) {
			cerr << "Age cannot be negative!" << endl;
			return -1;
		}
		this->age = age;
		return this->age;
	}

	virtual void displayInfo() const {
		cout << "Name: " << name << ", Breed: " << breed << ", Color: " << color
			<< ", Owner: " << PetParent_name << ", Weight: " << weight
			<< ", Height: " << height << ", Age: " << age
			<< ", Type: " << getType() << ", Sound: " << getSound() << endl;
	}

};

class Cat : public Pet {
private:
	bool isIndoor;

public:
	Cat(const string& name, const string& breed, const string& color,
		const string& PetParent_name, double weight, double height, int age, bool isIndoor)
		: Pet(name, breed, color, PetParent_name, weight, height, age), isIndoor(isIndoor) {}

	string getSound() const override { return "Meow"; }
	string getType() const override { return "Cat"; }

	bool getIsIndoor() const { return isIndoor; }
	bool setIsIndoor(bool isIndoor) {
		this->isIndoor = isIndoor;
		return this->isIndoor;
	}
	virtual void displayInfo() const {
		Pet::displayInfo;
		cout << "Indoor: " << (isIndoor ? "Yes" : "No") << endl;
	}
};


class Dog : public Pet {
private:
	bool isTrained;

public:
	Dog(const string& name, const string& breed, const string& color,
		const string& PetParent_name, double weight, double height, int age, bool isTrained)
		: Pet(name, breed, color, PetParent_name, weight, height, age), isTrained(isTrained) {}

	string getSound() const override { return "Woof"; }
	string getType() const override { return "Dog"; }

	bool getIsTrained() const { return isTrained; }
	bool setIsTrained(bool isTrained) {
		this->isTrained = isTrained;
		return this->isTrained;
	}

	void displayInfo() const override {
		Pet::displayInfo();
		cout << "Trained: " << (isTrained ? "Yes" : "No") << endl;
	}
};

class Parrot : public Pet {
private:
	bool canTalk;

public:
	Parrot(const string& name, const string& breed, const string& color,
		const string& PetParent_name, double weight, double height, int age, bool canTalk)
		: Pet(name, breed, color, PetParent_name, weight, height, age), canTalk(canTalk) {}

	string getSound() const override { return "Squawk"; }
	string getType() const override { return "Parrot"; }

	bool getCanTalk() const { return canTalk; }
	bool setCanTalk(bool canTalk) {
		this->canTalk = canTalk;
		return this->canTalk;
	}

	void displayInfo() const override {
		Pet::displayInfo();
		cout << "Can talk: " << (canTalk ? "Yes" : "No") << endl;
	}
};

class Hamster : public Pet {
private:
	bool hasWheel;

public:
	Hamster(const string& name, const string& breed, const string& color,
		const string& PetParent_name, double weight, double height, int age, bool hasWheel)
		: Pet(name, breed, color, PetParent_name, weight, height, age), hasWheel(hasWheel) {}

	string getSound() const override { return "Squeak"; }
	string getType() const override { return "Hamster"; }

	bool getHasWheel() const { return hasWheel; }
	bool setHasWheel(bool hasWheel) {
		this->hasWheel = hasWheel;
		return this->hasWheel;
	}

	void displayInfo() const override {
		Pet::displayInfo();
		cout << "Has wheel: " << (hasWheel ? "Yes" : "No") << endl;
	}
};


int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	Cat cat("Murka", "British", "Grey", "Olena", 4.5, 30.0, 2, true);
	Dog dog("Rex", "Labrador", "Brown", "Ivan", 25.0, 55.0, 3, true);
	Parrot parrot("Kesha", "Macaw", "Green", "Petro", 0.4, 30.0, 1, true);
	Hamster hamster("Fluffy", "Syrian", "White", "Anna", 0.15, 10.0, 1, false);

	cat.displayInfo();
	dog.displayInfo();
	parrot.displayInfo();
	hamster.displayInfo();

	return 0;

}