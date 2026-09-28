#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <cctype>
#include <windows.h>
#include <limits>
#include <format>
#define NOMINMAX
using namespace std;


class Base {
protected:
	string login;
	string second_name;
	string password;

public:

	Base(){}
	Base(const string& login, const string& second_name, const string& password): login{ login }, second_name{ second_name }, password{ password } {}
	virtual ~Base() = default;

	void inputLogin() {
		cout << "Login: ";
		cin >> login;
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		cout << "Second name (Enter, если нет): ";
		getline(cin, second_name);
	}

	void show() const {
		cout << format("Login: {}, second name: {}\n",
			login, second_name.empty() ? "-" : second_name);
	}

	inline void inputPassword() {
		cout << "password: ";
		cin >> password;
	}

	void show() {
		cout << format("password: {}\n",password);
	}


	const string& getLogin() const { return login; }
	const string& getSecondName() const { return second_name; }
	const string& getPassword() const { return password; }


	void saveToFile(const string& filename) const {
		ofstream file(filename, ios::app);
		if (!file.is_open()) {
			cerr << "Не удалось открыть файл\n";
			return;
		}
		file << login << " " << (second_name.empty() ? "-" : second_name)
			<< " " << password << "\n";
	}

	bool readFrom(ifstream& file) {
		if (!(file >> login >> second_name >> password)) return false;
		if (second_name == "-") second_name.clear();
		return true;
	}
};