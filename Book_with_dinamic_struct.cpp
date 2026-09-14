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


class Bus : public TransportMeans {
private:
    string route;
    string stops[20];   
    int stopsCount;      
    int tripsPerDay;

public:
    Bus(FuelType fuel, int seats, int doors, int wheels,
        const string& route, int tripsPerDay)
        : TransportMeans(fuel,
            (seats < 6 || seats > 40) ? 6 : seats,
            (doors < 2 || doors > 4) ? 2 : doors,
            (wheels < 2 || wheels > 8) ? 2 : wheels),
        route(route), stopsCount(0),
        tripsPerDay(tripsPerDay < 1 ? 1 : tripsPerDay)
    {
        if (seats < 6 || seats > 40)
            cerr << "Warning: seats out of range [6,40], set to default 6" << endl;
        if (doors < 2 || doors > 4)
            cerr << "Warning: doors out of range [2,4], set to default 2" << endl;
        if (wheels < 2 || wheels > 8)
            cerr << "Warning: wheels out of range [2,8], set to default 2" << endl;
    }

    string getRoute() const { return route; }
    void setRoute(const string& r) { route = r; }

    int getTripsPerDay() const { return tripsPerDay; }
    void setTripsPerDay(int trips) { tripsPerDay = (trips < 1) ? 1 : trips; }

    void addStop(const string& stop) {
        if (stopsCount >= 20) {
            cerr << "Cannot add more stops, limit reached!" << endl;
            return;
        }
        stops[stopsCount] = stop;
        stopsCount++;
    }

    void displayInfo() const override {
        TransportMeans::displayInfo();
        cout << "Route: " << route << ", Trips per day: " << tripsPerDay << endl;
        cout << "Stops: ";
        for (int i = 0; i < stopsCount; i++) {
            cout << stops[i];
            if (i != stopsCount - 1) cout << " -> ";
        }
        cout << endl;
    }
};


class Marshrutka : public TransportMeans {
private:
    string route;
    string stops[20];
    int stopsCount;
    int tripsPerDay;

public:
    Marshrutka(FuelType fuel, int seats, int doors,
        const string& route, int tripsPerDay)
        : TransportMeans(fuel,
            (seats < 8 || seats > 20) ? 8 : seats,
            (doors < 1 || doors > 2) ? 1 : doors,
            4), 
        route(route), stopsCount(0),
        tripsPerDay((tripsPerDay < 1 || tripsPerDay > 15) ? 5 : tripsPerDay)
    {
        if (seats < 8 || seats > 20)
            cerr << "Warning: seats out of range [8,20], set to default 8" << endl;
        if (doors < 1 || doors > 2)
            cerr << "Warning: doors out of range [1,2], set to default 1" << endl;
        if (tripsPerDay < 1 || tripsPerDay > 15)
            cerr << "Warning: tripsPerDay out of range [1,15], set to default 5" << endl;
    }

    string getRoute() const { return route; }
    void setRoute(const string& r) { route = r; }

    int getTripsPerDay() const { return tripsPerDay; }
    void setTripsPerDay(int trips) {
        tripsPerDay = (trips < 1 || trips > 15) ? tripsPerDay : trips;
    }

    void addStop(const string& stop) {
        if (stopsCount >= 20) {
            cerr << "Cannot add more stops, limit reached!" << endl;
            return;
        }
        stops[stopsCount] = stop;
        stopsCount++;
    }

    void displayInfo() const override {
        TransportMeans::displayInfo();
        cout << "Route: " << route << ", Trips per day: " << tripsPerDay << endl;
        cout << "Stops: ";
        for (int i = 0; i < stopsCount; i++) {
            cout << stops[i];
            if (i != stopsCount - 1) cout << " -> ";
        }
        cout << endl;
    }
};



int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    const int FLEET_SIZE = 3;
    TransportMeans* fleet[FLEET_SIZE];

    fleet[0] = new Car(FuelType::Petrol, 5, 4, 4, "Sedan");
    fleet[1] = new Bus(FuelType::Diesel, 30, 2, 6, "Kyiv - Lviv", 3);
    fleet[2] = new Marshrutka(FuelType::Gas, 15, 1, "Center - Airport", 8);

    static_cast<Bus*>(fleet[1])->addStop("Kyiv");
    static_cast<Bus*>(fleet[1])->addStop("Zhytomyr");
    static_cast<Bus*>(fleet[1])->addStop("Rivne");
    static_cast<Bus*>(fleet[1])->addStop("Lviv");

    static_cast<Marshrutka*>(fleet[2])->addStop("Center");
    static_cast<Marshrutka*>(fleet[2])->addStop("Mall");
    static_cast<Marshrutka*>(fleet[2])->addStop("Airport");

    cout << "=== Autopark before trips ===" << endl;
    for (int i = 0; i < FLEET_SIZE; i++) {
        fleet[i]->displayInfo();
        cout << endl;
    }

    fleet[1]->breakPart(PartType::Wheel); 

    int totalPassengers = 0;
    const int TRIPS = 2;

    cout << "=== Simulating " << TRIPS << " trips ===" << endl;
    for (int trip = 1; trip <= TRIPS; trip++) {
        cout << "--- Trip " << trip << " ---" << endl;
        for (int i = 0; i < FLEET_SIZE; i++) {
            if (fleet[i]->isWorking()) {
                totalPassengers += fleet[i]->getSeats();
                cout << "Vehicle " << i << " carried " << fleet[i]->getSeats() << " passengers" << endl;
            }
            else {
                cout << "Vehicle " << i << " is broken, skipped this trip" << endl;
            }
        }
    }

    cout << "\nMax passengers transported in " << TRIPS << " trips: " << totalPassengers << endl;

    for (int i = 0; i < FLEET_SIZE; i++) {
        delete fleet[i];
    }

    return 0;
}