#include <iostream>
#include <string>
#include <windows.h>

using namespace std;


// ===== Вспомогательные структуры =====

struct Date_of_birth
{
    int day;
    int month;
    int year;

    void input()
    {
        cout << "Enter day: "; cin >> day;
        cout << "Enter month: "; cin >> month;
        cout << "Enter year: "; cin >> year;
    }

    void show() const
    {
        cout << day << "." << month << "." << year;
    }
};


struct Time
{
    int day;
    int hour;
    int minute;

    void input()
    {
        cout << "Enter days: "; cin >> day;
        cout << "Enter hours: "; cin >> hour;
        cout << "Enter minutes: "; cin >> minute;
    }

    void show() const
    {
        cout << day << "d " << hour << "h " << minute << "m";
    }
};


struct From_where
{
    string place;        // откуда едем
    Time travel_time;    // время в пути
    int stops_count;     // количество остановок

    void input()
    {
        cout << "Enter departure place: ";
        cin.ignore();
        getline(cin, place);

        cout << "Enter travel time:" << endl;
        travel_time.input();

        cout << "Enter number of stops: ";
        cin >> stops_count;
    }

    void show() const
    {
        cout << place << " (travel time: ";
        travel_time.show();
        cout << ", stops: " << stops_count << ")";
    }
};


struct Amenities
{
    bool has_toilet;
    bool has_wifi;
    bool has_ac;         // кондей
    bool has_heater;     // печка
    bool has_charging;
    bool has_speakers;
    bool has_light;

    void input()
    {
        cout << "Has toilet (1/0): "; cin >> has_toilet;
        cout << "Has wifi (1/0): "; cin >> has_wifi;
        cout << "Has AC (1/0): "; cin >> has_ac;
        cout << "Has heater (1/0): "; cin >> has_heater;
        cout << "Has charging (1/0): "; cin >> has_charging;
        cout << "Has speakers (1/0): "; cin >> has_speakers;
        cout << "Has light (1/0): "; cin >> has_light;
    }

    void show() const
    {
        cout << "Toilet: " << has_toilet
            << ", WiFi: " << has_wifi
            << ", AC: " << has_ac
            << ", Heater: " << has_heater
            << ", Charging: " << has_charging
            << ", Speakers: " << has_speakers
            << ", Light: " << has_light;
    }
};


// ===== Класс-компонент =====

class Passenger
{
private:
    string name;
    string surname;
    string lastname;
    Date_of_birth age;

    From_where place1;   // откуда
    string place2;        // куда

    string ticket_number;

public:

    Passenger()
        : name("No name"), surname("No surname"), lastname("No lastname"),
        age{ 1, 1, 2000 },
        place1{ "Unknown", Time{0,0,0}, 0 },
        place2("Unknown"),
        ticket_number("0000")
    {
        cout << "[Passenger] Default constructor: " << surname << endl;
    }

    Passenger(string name, string surname, string lastname,
        Date_of_birth age, From_where place1, string place2, string ticket_number)
        : name(name), surname(surname), lastname(lastname),
        age(age), place1(place1), place2(place2), ticket_number(ticket_number)
    {
        cout << "[Passenger] Constructor: " << this->surname << endl;
    }

    ~Passenger()
    {
        cout << "[Passenger] Destructor: " << surname << endl;
    }

    void input_passenger()
    {
        cout << "Enter name: "; cin >> name;
        cout << "Enter surname: "; cin >> surname;
        cout << "Enter lastname: "; cin >> lastname;

        cout << "Enter date of birth:" << endl;
        age.input();

        cout << "Enter departure info:" << endl;
        place1.input();

        cout << "Enter destination: ";
        cin.ignore();
        getline(cin, place2);

        cout << "Enter ticket number: ";
        cin >> ticket_number;
    }

    void show_passenger() const
    {
        cout << "Name: " << name << " " << surname << " " << lastname << endl;
        cout << "Date of birth: "; age.show(); cout << endl;
        cout << "From: "; place1.show(); cout << endl;
        cout << "To: " << place2 << endl;
        cout << "Ticket number: " << ticket_number << endl;
    }


    // ===== Getters =====

    string get_name() const { return name; }
    string get_surname() const { return surname; }
    string get_lastname() const { return lastname; }
    Date_of_birth get_age() const { return age; }
    From_where get_place1() const { return place1; }
    string get_place2() const { return place2; }
    string get_ticket_number() const { return ticket_number; }


    // ===== Setters =====

    void set_name(string new_name) { name = new_name; }
    void set_surname(string new_surname) { surname = new_surname; }
    void set_lastname(string new_lastname) { lastname = new_lastname; }
    void set_age(Date_of_birth new_age) { age = new_age; }
    void set_place1(From_where new_place1) { place1 = new_place1; }
    void set_place2(string new_place2) { place2 = new_place2; }
    void set_ticket_number(string new_ticket) { ticket_number = new_ticket; }
};


// ===== Класс-контейнер (агрегація) =====

class Bus
{
private:
    string route;
    string driver_name;
    int seats_count{ 0 };
    double length{ 0.0 };
    double width{ 0.0 };
    int conductors_count{ 0 };

    Amenities amenities;

    Passenger** passengers{ nullptr };
    int passenger_count{ 0 };

public:

    Bus()
        : route("No route"), driver_name("No driver"),
        seats_count(0), length(0.0), width(0.0), conductors_count(0),
        amenities{ false, false, false, false, false, false, false },
        passengers(nullptr), passenger_count(0)
    {
        cout << "[Bus] Default constructor: " << route << endl;
    }

    Bus(string route, string driver_name, int seats_count,
        double length, double width, int conductors_count, Amenities amenities)
        : route(route), driver_name(driver_name),
        seats_count(seats_count), length(length), width(width),
        conductors_count(conductors_count), amenities(amenities),
        passengers(nullptr), passenger_count(0)
    {
        cout << "[Bus] Constructor: " << route << endl;
    }


    void input_bus()
    {
        cout << "Enter route: ";
        cin.ignore();
        getline(cin, route);

        cout << "Enter driver name: ";
        getline(cin, driver_name);

        cout << "Enter seats count: "; cin >> seats_count;
        cout << "Enter length: "; cin >> length;
        cout << "Enter width: "; cin >> width;
        cout << "Enter conductors count: "; cin >> conductors_count;

        cout << "Enter amenities:" << endl;
        amenities.input();
    }


    void boardPassenger(Passenger* passenger)
    {
        Passenger** temp = new Passenger * [passenger_count + 1];

        for (int i = 0; i < passenger_count; i++)
        {
            temp[i] = passengers[i];
        }

        temp[passenger_count] = passenger;

        delete[] passengers;

        passengers = temp;
        passenger_count++;

        cout << "[Bus] Passenger boarded: " << passenger->get_surname() << endl;
    }


    void alightPassenger(Passenger* passenger)
    {
        int index = -1;

        for (int i = 0; i < passenger_count; i++)
        {
            if (passengers[i] == passenger)  // ищем по адресу объекта
            {
                index = i;
                break;
            }
        }

        if (index == -1)
        {
            cout << "[Bus] Passenger not found on this bus." << endl;
            return;
        }

        Passenger** temp = new Passenger * [passenger_count - 1];

        for (int i = 0, j = 0; i < passenger_count; i++)
        {
            if (i != index)
            {
                temp[j++] = passengers[i];
            }
        }

        delete[] passengers;

        passengers = temp;
        passenger_count--;

        cout << "[Bus] Passenger alighted: " << passenger->get_surname() << endl;
    }


    void show_bus() const
    {
        cout << "\n===== BUS =====" << endl;
        cout << "Route: " << route << endl;
        cout << "Driver: " << driver_name << endl;
        cout << "Seats: " << seats_count << endl;
        cout << "Dimensions: " << length << "x" << width << endl;
        cout << "Conductors: " << conductors_count << endl;
        cout << "Amenities -> "; amenities.show(); cout << endl;

        cout << "Number of passengers: " << passenger_count << endl;

        for (int i = 0; i < passenger_count; i++)
        {
            cout << "\n--- Passenger " << i + 1 << " ---" << endl;
            passengers[i]->show_passenger();
        }
    }


    ~Bus()
    {
        cout << "[Bus] Destructor: " << route << endl;

        // ВАЖНО:
        // пассажиров здесь НЕ удаляем,
        // потому что Bus ими не владеет (агрегация).

        delete[] passengers;
    }


    // ===== Getters =====

    string get_route() const { return route; }
    string get_driver_name() const { return driver_name; }
    int get_seats_count() const { return seats_count; }
    double get_length() const { return length; }
    double get_width() const { return width; }
    int get_conductors_count() const { return conductors_count; }
    Amenities get_amenities() const { return amenities; }
    int get_passenger_count() const { return passenger_count; }


    // ===== Setters =====

    void set_route(string new_route) { route = new_route; }
    void set_driver_name(string new_driver_name) { driver_name = new_driver_name; }
    void set_seats_count(int new_seats_count) { seats_count = new_seats_count; }
    void set_length(double new_length) { length = new_length; }
    void set_width(double new_width) { width = new_width; }
    void set_conductors_count(int new_conductors_count) { conductors_count = new_conductors_count; }
    void set_amenities(Amenities new_amenities) { amenities = new_amenities; }
};


int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Date_of_birth d1{ 24, 6, 1987 };
    Date_of_birth d2{ 5, 2, 1985 };
    Date_of_birth d3{ 21, 12, 1998 };

    From_where fw1{ "Kyiv", Time{0, 2, 0}, 4 };
    From_where fw2{ "Lviv", Time{0, 1, 30}, 2 };
    From_where fw3{ "Odesa", Time{0, 2, 30}, 5 };

    Passenger passenger1("Leo", "Messi", "Andres", d1, fw1, "Warsaw", "T-001");
    Passenger passenger2("Cristiano", "Ronaldo", "dos Santos", d2, fw2, "Berlin", "T-002");
    Passenger passenger3("Kylian", "Mbappe", "Lottin", d3, fw3, "Vienna", "T-003");

    Amenities amenities{ true, true, true, false, true, true, true };

    {
        Bus bus("Kyiv - Warsaw Express", "Ivan Petrenko", 50, 12.5, 2.5, 2, amenities);

        bus.boardPassenger(&passenger1);
        bus.boardPassenger(&passenger2);
        bus.boardPassenger(&passenger3);

        bus.show_bus();

        cout << "\n===== ONE PASSENGER ALIGHTS EARLY =====" << endl;
        bus.alightPassenger(&passenger2);

        bus.show_bus();

        cout << "\n===== BUS IS DESTROYED =====" << endl;
    }

    cout << "\n===== PASSENGERS STILL EXIST =====" << endl;

    passenger1.show_passenger();
    cout << endl;

    passenger2.show_passenger();
    cout << endl;

    passenger3.show_passenger();
    cout << endl;

    return 0;
}