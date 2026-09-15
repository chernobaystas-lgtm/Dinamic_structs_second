#include <iostream>
#include <string>
#include <windows.h>


using namespace std;


class Figure {
protected:
    double width;
    double length;

public:
    Figure() : width(0.0), length(0.0) {}

    Figure(double width, double length) : width(width), length(length) {}

    virtual ~Figure() {}

    virtual double getArea() const = 0;
};


int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);





    return 0;
}