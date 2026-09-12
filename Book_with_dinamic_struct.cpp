#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <windows.h>
#include <cassert>
using namespace std;

struct FullName {
    string lastName;
    string firstName;
    string patronymic;
};

struct DateTime {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

class Employee {
protected:
    FullName fio;
    DateTime birthDate;
    int experience;       // стаж (у роках)
    double baseSalary;    // ставка за годину (в євро)
    DateTime workTime;    // скільки годин/хвилин/секунд працює за день
    int workingDays;      // робочих днів на місяць

public:
    Employee(const FullName& fio, const DateTime& birthDate, int experience,
        double baseSalary, const DateTime& workTime, int workingDays)
        : fio(fio), birthDate(birthDate), experience(experience),
        baseSalary(baseSalary), workTime(workTime), workingDays(workingDays) {}

    virtual ~Employee() {}

    virtual double calculateSalary() const = 0;
    virtual string whatIDo() const = 0;

    double getHoursPerDay() const {
        return workTime.hour + workTime.minute / 60.0 + workTime.second / 3600.0;
    }

protected:
    // базовий заробіток без бонусів: ставка * години на день * робочі дні
    double calculateBasePay() const {
        return baseSalary * getHoursPerDay() * workingDays;
    }

public:
    virtual void displayInfo() const {
        cout << fio.lastName << " " << fio.firstName << " " << fio.patronymic
            << ", Birth date: " << birthDate.day << "." << birthDate.month << "." << birthDate.year
            << ", Experience: " << experience << " years"
            << ", Hours/day: " << getHoursPerDay()
            << ", Working days: " << workingDays
            << ", Role: " << whatIDo()
            << ", Salary: " << calculateSalary() << " EUR" << endl;
    }
};

class Manager : public Employee {
private:
    double bonus;

public:
    Manager(const FullName& fio, const DateTime& birthDate, int experience,
        const DateTime& workTime, int workingDays, double bonus)
        : Employee(fio, birthDate, experience, 12.0, workTime, workingDays), bonus(bonus) {}

    double calculateSalary() const override {
        return calculateBasePay() + bonus;
    }

    string whatIDo() const override {
        return "Manager: manages the team and controls plan fulfillment";
    }
};

enum class Specialization {
    Frontend,
    Backend,
    Fullstack,
    Mobile,
    GameDev
};

string specializationToString(Specialization s) {
    switch (s) {
    case Specialization::Frontend: return "Frontend developer";
    case Specialization::Backend: return "Backend developer";
    case Specialization::Fullstack: return "Fullstack developer";
    case Specialization::Mobile: return "Mobile developer";
    case Specialization::GameDev: return "Game developer";
    }
    return "Developer";
}

class Developer : public Employee {
private:
    int linesOfCode;
    double ratePerLine;
    Specialization specialization;

public:
    Developer(const FullName& fio, const DateTime& birthDate, int experience,
        const DateTime& workTime, int workingDays, int linesOfCode, Specialization specialization)
        : Employee(fio, birthDate, experience, 12.0, workTime, workingDays),
        linesOfCode(linesOfCode), ratePerLine(0.50), specialization(specialization) {}

    double calculateSalary() const override {
        return calculateBasePay() + (linesOfCode * ratePerLine);
    }

    string whatIDo() const override {
        return specializationToString(specialization) + ": writes and supports code";
    }
};

Specialization chooseSpecialization() {
    cout << "Choose developer specialization:" << endl;
    cout << "1 - Frontend" << endl;
    cout << "2 - Backend" << endl;
    cout << "3 - Fullstack" << endl;
    cout << "4 - Mobile" << endl;
    cout << "5 - GameDev" << endl;
    cout << "Your choice: ";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1: return Specialization::Frontend;
    case 2: return Specialization::Backend;
    case 3: return Specialization::Fullstack;
    case 4: return Specialization::Mobile;
    case 5: return Specialization::GameDev;
    default:
        cout << "Wrong choice, Backend is set by default." << endl;
        return Specialization::Backend;
    }
}

int main() {

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

    FullName managerName = { "Petrenko", "Ivan", "Olegovych" };
    DateTime managerBirth = { 1990, 5, 12, 0, 0, 0 };
    DateTime managerWorkTime = { 0, 0, 0, 8, 0, 0 }; 

    FullName devName = { "Kovalenko", "Olena", "Petrivna" };
    DateTime devBirth = { 1995, 8, 23, 0, 0, 0 };
    DateTime devWorkTime = { 0, 0, 0, 6, 30, 0 }; 

    Specialization spec = chooseSpecialization();

    const int SIZE = 2;
    Employee* employees[SIZE];
    employees[0] = new Manager(managerName, managerBirth, 5, managerWorkTime, 20, 300.0);
    employees[1] = new Developer(devName, devBirth, 3, devWorkTime, 20, 450, spec);

    double totalSalary = 0.0;

    cout << "\n=== Employees info ===" << endl;
    for (int i = 0; i < SIZE; i++) {
        employees[i]->displayInfo();
        totalSalary += employees[i]->calculateSalary();
    }

    cout << "\nTotal salary company must pay this month: " << totalSalary << " EUR" << endl;

    for (int i = 0; i < SIZE; i++) {
        delete employees[i];
    }


	return 0;
}