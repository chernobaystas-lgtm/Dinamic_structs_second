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




int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);


    return 0;
}