#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <windows.h>
#include <cassert>
using namespace std;

class triada {
protected:
	double n1;
	double n2;
	double n3;
public:
	triada(double n1, double n2, double n3) : n1(n1), n2(n2), n3(n3) {
	}
	triada(): n1(0.0), n2(0.0), n3(0.0){}

	inline double getN1() const { return n1; }
	inline double getN2() const { return n2; }
	inline double getN3() const { return n3; }

	int setN1(double n1){
		if (n1 < 0) {
			cerr << "Number can`t be less 0";
			return -1;
		}
		this->n1 = n1;
		return 0;
	}
	int setN2(double n2) {
		if (n2 < 0) {
			cerr << "Number can`t be less 0";
			return -1;
		}
		this->n2 = n2;
		return 0;
	}
	int setN3(double n3) {
		if (n3 < 0) {
			cerr << "Number can`t be less 0";
			return -1;
		}
		this->n3 = n3;
		return 0;
	}

	virtual inline void display() {
		cout << "n1:" << n1 <<endl <<"n2:" << n2 <<endl << "n3" << n3;
	}


	virtual inline void increaseN1() {
		setN1(getN1() + 1);
	}

	virtual inline void increaseN2() {
		setN2(getN2() + 1);
	}
	virtual inline void increaseN3() {
		setN3(getN3() + 1);
	}
};


class Date : public triada {
private:
	int year;
	int month;
	int day;
public:
	Date(): year(0), month(0), day(0){}
	Date(int year, int month, int day): year(year), month(month), day(day){}

	double getYear() const { return getN1(); }
	double getMonth() const { return getN2(); }
	double getDay() const { return getN3(); }

	int setYear(double year) { return setN1(year); }
	int setMonth(double month) { return setN2(month); }
	int setDay(double day) { return setN3(day); }

	bool isLeapYear(int year) const {
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}
	
	int daysInMonth(int month, int year) const {
		int days[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		if (month == 2 && isLeapYear(year)) {
			return 29;
		}
		return days[month - 1];
	}
	
	virtual void increaseYear()  {
		setYear(getYear() + 1);
	}

	virtual void increaseMonth()  {
		int month = (int)getMonth();
		int year = (int)getYear();

		month++;
		if (month > 12) {
			month = 1;
			increaseYear();
		}
		setMonth(month);
	}

	virtual void increaseDay()  {
		int day = (int)getDay();
		int month = (int)getMonth();
		int year = (int)getYear();

		day++;
		if (day > daysInMonth(month, year)) {
			day = 1;
			increaseMonth();
		}
		setDay(day);
	}

	void increaseByNDays(int n) {
		for (int i = 0; i < n; i++) {
			increaseDay();
		}
	}
};


int main() {

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);


	Date d;
	d.setYear(2024);
	d.setMonth(2);
	d.setDay(28);

	cout << "Було: " << d.getDay() << "." << d.getMonth() << "." << d.getYear() << endl;

	d.increaseDay(); 
	cout << "Після increaseDay: " << d.getDay() << "." << d.getMonth() << "." << d.getYear() << endl;

	d.increaseByNDays(5);
	cout << "Після +5 дней: " << d.getDay() << "." << d.getMonth() << "." << d.getYear() << endl;

	Date d2;
	d2.setYear(2023);
	d2.setMonth(12);
	d2.setDay(31);
	d2.increaseDay();
	cout << "31.12.2023 + 1 день = " << d2.getDay() << "." << d2.getMonth() << "." << d2.getYear() << endl;

	return 0;
}