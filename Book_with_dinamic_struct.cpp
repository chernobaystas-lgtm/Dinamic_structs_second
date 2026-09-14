#include <iostream>
#include <string>
#include <windows.h>
#include <format>

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



class Passenger {
protected:
	Name Passager_Name;
    Date birth_date;
    Date today;
    FromToSmw place;
public:
    Passenger()
        : Passager_Name("No name"), birth_date(), today(), place("Without place") {}

    Passenger(const string& name, const Date& date, const FromToSmw& fromTo, int age)
        : Passager_Name(name), birth_date(date), today(), place(fromTo) {}

    inline void input() {
        cout << "Enter passenger name: " << endl;
        Passager_Name.input();
        cout << "Enter birth date:" << endl;
        birth_date.input();
        cout << "Enter trip info:" << endl;
        place.input();
    }

    inline void show() const {
        Passager_Name.show();
        cout << "Birth date: ";
        birth_date.show();
        place.show();
    }

};



enum class PartType {
    Engine,
    Wheel,
    Brakes,
    Doors,
    Electronics,
    None  
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

class TransportMeans
{
protected:
    FuelType fuel;
    int wheels;
    PartType brokenPart;

    Passenger* passengers[40];
    int passengerCount{ 0 };

public:

    TransportMeans()
        : fuel(FuelType::Petrol),
        wheels(4),
        brokenPart(PartType::None),
        passengers{},
        passengerCount(0)
    {}

    TransportMeans(FuelType fuel, int wheels)
        : fuel(fuel),
        wheels(wheels),
        brokenPart(PartType::None),
        passengers{},
        passengerCount(0)
    {}

    virtual ~TransportMeans() = default;


    virtual int getSeats() const = 0;
    virtual int getDoors() const = 0;


    FuelType getFuel() const{  return fuel;}

    int getWheels() const {  return wheels;}


    bool isWorking() const{ return brokenPart == PartType::None;}

    void breakPart(PartType part){brokenPart = part;}

    void repair(){brokenPart = PartType::None;}

    virtual void addPassenger(Passenger* passenger)
    {
        if (passengerCount >= getSeats())
        {
            cout << "No free seats!" << endl;
            return;
        }

        passengers[passengerCount] = passenger;
        passengerCount++;
    }


    virtual void showPassengers() const
    {
        cout << "\nPassengers: " << passengerCount << endl;

        for (int i = 0; i < passengerCount; i++)
        {
            cout << "--- Passenger " << i + 1 << " ---" << endl;
            passengers[i]->show();
        }
    }


    virtual void displayInfo() const
    {
        cout << format(
            "Fuel: {}, Seats: {}, Doors: {}, Wheels: {}, Status: {}",
            fuelToString(fuel),
            getSeats(),
            getDoors(),
            wheels,
            isWorking() ? "OK" : "Broken"
        ) << endl;
    }
};

class Car : public TransportMeans
{
private:
    int seats;
    int doors;
    string bodyType;

public:

    Car(
        FuelType fuel,int seats,int doors,int wheels,const string& bodyType
    )
        : TransportMeans(fuel, wheels),seats(seats),doors(doors), bodyType(bodyType)
    {}

    int getSeats() const override{return seats;}

    int getDoors() const override{ return doors;}

    string getBodyType() const{return bodyType;}

    void setBodyType(const string& type){bodyType = type;}


    void displayInfo() const override
    {
        TransportMeans::displayInfo();

        cout << format(
            "Body type: {}",
            bodyType
        ) << endl;
    }
};


class Bus : public TransportMeans
{
protected:
    int seats;
    int doors;

private:
    string route;
    string stops[20];
    int stopsCount{ 0 };
    int tripsPerDay;

public:

    Bus(
        FuelType fuel, int seats, int doors, int wheels, const string& route, int tripsPerDay)
        : TransportMeans(fuel, wheels),
        seats((seats < 6 || seats > 40) ? 6 : seats),
        doors((doors < 2 || doors > 4) ? 2 : doors),
        route(route),
        tripsPerDay(tripsPerDay < 1 ? 1 : tripsPerDay)
    {}
    int getSeats() const override{ return seats;}

    int getDoors() const override{return doors;}

    string getRoute() const{ return route;}

    void setRoute(const string& r){ route = r;}


    int getTripsPerDay() const{ return tripsPerDay;}

    void setTripsPerDay(int trips){ if (trips >= 1) tripsPerDay = trips;}

    void addStop(const string& stop)
    {
        if (stopsCount >= 20)
        {
            cout << "Cannot add more stops!" << endl;
            return;
        }

        stops[stopsCount] = stop;
        stopsCount++;
    }


    void displayInfo() const override
    {
        TransportMeans::displayInfo();

        cout << format(
            "Route: {}, Trips per day: {}",
            route,
            tripsPerDay
        ) << endl;

        cout << "Stops: ";

        for (int i = 0; i < stopsCount; i++)
        {
            cout << stops[i];

            if (i != stopsCount - 1)
                cout << " -> ";
        }

        cout << endl;
    }
};


class Marshrutka : public Bus
{
private:
    bool standingPlaces;

public:

    Marshrutka(
        FuelType fuel, int seats, int doors, const string& route, int tripsPerDay, bool standingPlaces
    )
        : Bus(
            fuel, seats, doors, 4, route, tripsPerDay),standingPlaces(standingPlaces)
    {}


    bool hasStandingPlaces() const {return standingPlaces;}

    void setStandingPlaces(bool value){standingPlaces = value;}


    void displayInfo() const override
    {
        Bus::displayInfo();

        cout << format(
            "Standing places: {}",
            standingPlaces ? "Yes" : "No"
        ) << endl;
    }
};


int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);



    Passenger passenger1;
    Passenger passenger2;
    Passenger passenger3;



    Car car(
        FuelType::Petrol,5,4, 4, "Sedan"
    );

    Bus bus(
        FuelType::Diesel, 30,2,6,"Kyiv - Lviv", 3
    );

    Marshrutka marshrutka(
        FuelType::Gas,15,1,"Center - Airport",8, true
    );



    bus.addPassenger(&passenger1);
    bus.addPassenger(&passenger2);

    marshrutka.addPassenger(&passenger3);


    bus.addStop("Kyiv");
    bus.addStop("Zhytomyr");
    bus.addStop("Rivne");
    bus.addStop("Lviv");

    marshrutka.addStop("Center");
    marshrutka.addStop("Mall");
    marshrutka.addStop("Airport");



    cout << "\n===== CAR =====" << endl;
    car.displayInfo();

    cout << "\n===== BUS =====" << endl;
    bus.displayInfo();
    bus.showPassengers();

    cout << "\n===== MARSHRUTKA =====" << endl;
    marshrutka.displayInfo();
    marshrutka.showPassengers();


    TransportMeans* fleet[3];

    fleet[0] = &car;
    fleet[1] = &bus;
    fleet[2] = &marshrutka;

    cout << "\n===== POLYMORPHISM =====" << endl;

    for (int i = 0; i < 3; i++)
    {
        fleet[i]->displayInfo();
        cout << endl;
    }


    return 0;
}