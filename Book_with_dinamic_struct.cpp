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

	inline void display() {
		cout << "n1:" << n1 <<endl <<"n2:" << n2 <<endl << "n3" << n3;
	}


	inline void increaseN1() {
		setN1(getN1() + 1);
	}

	inline void increaseN2() {
		setN2(getN2() + 1);
	}
	inline void increaseN3() {
		setN3(getN3() + 1);
	}
};


class Date : public triada {

};

int main() {

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);



	return 0;
}