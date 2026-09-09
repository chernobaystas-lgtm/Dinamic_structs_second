#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <windows.h>
#include <cassert>
using namespace std;

class Passport {
public:
	Passport() {
		cout << "Passport constructor called" << endl;
	}
	Passport(string fullName, string birthDate, string series, string number, string issuedBy)
		: fullName(fullName), birthDate(birthDate), series(series), number(number), issuedBy(issuedBy) {
		cout << "Passport parameterized constructor called" << endl;
	}

	~Passport() {
		cout << "Passport destructor called" << endl;
	}

	string passportToString() const {
		return "Full Name: " + fullName + ", Birth Date: " + birthDate +
			", Series: " + series + ", Number: " + number + ", Issued By: " + issuedBy;
	}

	void show() const {
		cout << passportToString() << endl;
	}

	// Getters and Setters
	string getFullName() const {
		return fullName;
	}
	void setFullName(const string& fullName) {
		this->fullName = fullName;
	}
	string getBirthDate() const {
		return birthDate;
	}
	void setBirthDate(const string& birthDate) {
		this->birthDate = birthDate;
	}
	string getSeries() const {
		return series;
	}
	void setSeries(const string& series) {
		this->series = series;
	}
	string getNumber() const {
		return number;
	}
	void setNumber(const string& number) {
		this->number = number;
	}
	string getIssuedBy() const {
		return issuedBy;
	}
	void setIssuedBy(const string& issuedBy) {
		this->issuedBy = issuedBy;
	}

protected:
	string fullName{ "" };
	string birthDate{ "" };
	string series{ "" };
	string number{ "" };
private:
	string issuedBy{ "" };
};

class ForeignPassport : public Passport {
public:
	ForeignPassport() : Passport() {
		cout << "ForeignPassport constructor called" << endl;
	}
	ForeignPassport(string fullName, string birthDate, string series, string number, string issuedBy,
		string foreignNumber, string visaInfo)
		: Passport(fullName, birthDate, series, number, issuedBy),
		foreignNumber(foreignNumber), visaInfo(visaInfo) {
		cout << "ForeignPassport parameterized constructor called" << endl;
	}

	~ForeignPassport() {
		cout << "ForeignPassport destructor called" << endl;
	}

	// перекрываем toString, чтобы не дублировать паспортные поля
	string foreignPassportToString() const {
		return passportToString() + ", Foreign Passport Number: " + foreignNumber + ", Visa Info: " + visaInfo;
	}

	void show() const {
		cout << foreignPassportToString() << endl;
	}

	string getForeignNumber() const {
		return foreignNumber;
	}
	void setForeignNumber(const string& foreignNumber) {
		this->foreignNumber = foreignNumber;
	}
	string getVisaInfo() const {
		return visaInfo;
	}
	void setVisaInfo(const string& visaInfo) {
		this->visaInfo = visaInfo;
	}

private:
	string foreignNumber{ "" };
	string visaInfo{ "" };
};

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	Passport p("Ivanenko Ivan Ivanovych", "01.01.2000", "AA", "123456", "Kyiv DMS");
	p.show();

	ForeignPassport fp("Petrenko Petro Petrovych", "05.05.1995", "BB", "654321", "Lviv DMS",
		"FP9988776", "Schengen visa till 2027");
	fp.show();

	return 0;
}