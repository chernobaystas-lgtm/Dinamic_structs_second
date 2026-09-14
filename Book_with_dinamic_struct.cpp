#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <windows.h>
#include <cassert>
using namespace std;


struct Date {
    int year;
    int month;
    int day;
    int hour;
    int minuts;
    int seconds;

    Date() : year(0), month(0), day(0), hour(0), minuts(0), seconds(0) {}

    void input() {
        cout << "Enter year: ";
        cin >> year;
        cout << "Enter month: ";
        cin >> month;
        cout << "Enter day: ";
        cin >> day;
        cout << "Enter hour: ";
        cin >> hour;
        cout << "Enter minutes: ";
        cin >> minuts;
        cout << "Enter seconds: ";
        cin >> seconds;
    }

    void show() const {
        cout << day << "." << month << "." << year << " "
            << hour << ":" << minuts << ":" << seconds << endl;
    }
};

struct Name {
    string name;
    string second_name;
    string lastname;


    Name() : name(""), second_name(""), lastname("") {}
    Name(const string& fullName) : name(fullName), second_name(""), lastname("") {}


    void input() {
        cout << "Enter name: " << endl;
        cin >> name;
        cout << "Enter second name: " << endl;
        cin >> second_name;
        cout << "Enter last name: " << endl;
        cin >> lastname;
    }

    void show() const {
        cout << "Name: " << name << " Second name: " << second_name
            << " Last name: " << lastname << endl;
    }
};

struct FromToSmw {
    string from;
    string to;
    Date date1;


    FromToSmw() : from(""), to(""), date1() {}
    FromToSmw(const string& label) : from(label), to(""), date1() {}


    void input() {
        cout << "Enter from: " << endl;
        cin >> from;
        cout << "Enter to: " << endl;
        cin >> to;
        cout << "Enter date:" << endl;
        date1.input();
    }

    void show() const {
        cout << "From: " << from << " To: " << to << " Date: ";
        date1.show();
    }
};



class Passager {
protected:
	Name Passager_Name;
    Date birth_date;
    Date today;
    FromToSmw place;
    int age;
public:
    Passager()
        : Passager_Name("No name"), birth_date(), today(), place("Without place"), age(0) {}

    Passager(const string& name, const Date& date, const FromToSmw& fromTo, int age)
        : Passager_Name(name), birth_date(date), today(), place(fromTo), age(age) {}

    virtual ~Passager() {}

    inline void input() {
        cout << "Enter passenger name: " << endl;
        Passager_Name.input();
        cout << "Enter birth date:" << endl;
        birth_date.input();
        cout << "Enter trip info:" << endl;
        place.input();
        cout << "Enter age: ";
        cin >> age;
    }

    inline void show() const {
        Passager_Name.show();
        cout << "Birth date: ";
        birth_date.show();
        place.show();
        cout << "Age: " << age << endl;
    }

};








enum class PartType {
    Engine,
    Wheel,
    Brakes,
    Doors,
    Electronics,
    None   // "ничего не сломано"
};

enum class FuelType {
    Petrol,
    Diesel,
    Electric,
    Gas
};


string fuelToString(FuelType fuel) {
    switch (fuel) {
    case FuelType::Petrol:   return "Petrol";
    case FuelType::Diesel:   return "Diesel";
    case FuelType::Electric: return "Electric";
    case FuelType::Gas:      return "Gas";
    default:                 return "Unknown";
    }
}

string partToString(PartType part) {
    switch (part) {
    case PartType::Engine:      return "Engine";
    case PartType::Wheel:       return "Wheel";
    case PartType::Brakes:      return "Brakes";
    case PartType::Doors:       return "Doors";
    case PartType::Electronics: return "Electronics";
    case PartType::None:        return "None";
    default:                    return "Unknown";
    }
}

class TransportMeans {
protected:
    FuelType fuel;
    int seats;
    int doors;
    int wheels;
    PartType brokenPart;

public:

    TransportMeans() : fuel(FuelType::Petrol), seats(0), doors(0), wheels(4), brokenPart(PartType::None) {}

    TransportMeans(FuelType fuel, int seats, int doors, int wheels)
        : fuel(fuel), seats(seats), doors(doors), wheels(wheels), brokenPart(PartType::None) {}

    virtual ~TransportMeans() {}

    FuelType getFuel() const { return fuel; }
    int getSeats() const { return seats; }
    int getDoors() const { return doors; }
    int getWheels() const { return wheels; }

    bool isWorking() const { return brokenPart == PartType::None; }

    void breakPart(PartType part) { brokenPart = part; }
    void repair() { brokenPart = PartType::None; }

    virtual void displayInfo() const {
        cout << "Fuel: " << fuelToString(fuel)
            << ", Seats: " << seats
            << ", Doors: " << doors
            << ", Wheels: " << wheels
            << ", Status: " << (isWorking() ? "OK" : "Broken (" + partToString(brokenPart) + ")")
            << endl;
    }
};

class Car : public TransportMeans {
private:
    string bodyType; 

public:
    Car(FuelType fuel, int seats, int doors, int wheels, const string& bodyType)
        : TransportMeans(fuel, seats, doors, wheels), bodyType(bodyType) {}

    string getBodyType() const { return bodyType; }
    void setBodyType(const string& type) { bodyType = type; }

    void displayInfo() const override {
        TransportMeans::displayInfo();
        cout << "Body type: " << bodyType << endl;
    }
};

int main() {

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);



    Car car(FuelType::Petrol, 5, 4, 4, "Sedan");
    car.displayInfo();

    car.breakPart(PartType::Engine);
    car.displayInfo(); // теперь Status: Broken (Engine)


	return 0;
}