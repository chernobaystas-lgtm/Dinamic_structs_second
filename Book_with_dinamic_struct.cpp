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


class Rectangle1 : public Figure {
public:
    Rectangle1() : Figure() {}

    Rectangle1(double width, double length) : Figure(width, length) {}

    double getArea() const override {
        return width * length;
    }
};

class Circle : public Figure {
private:
    double radius;

public:
    Circle() : Figure(), radius(0.0) {}

    Circle(double radius) : Figure(), radius(radius) {}

    double getArea() const override {
        return 3.14159265 * radius * radius;
    }
};

class RightTriangle : public Figure {
public:
    RightTriangle() : Figure() {}

    RightTriangle(double width, double length) : Figure(width, length) {}

    double getArea() const override {
        return (width * length) / 2.0;
    }
};

class Trapezoid : public Figure {
private:
    double base2;

public:
    Trapezoid() : Figure(), base2(0.0) {}

    Trapezoid(double base1, double base2, double height) : Figure(base1, height), base2(base2) {}

    double getArea() const override {
        return ((length + base2) / 2.0) * width;
    }
};


int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    const int COUNT = 4;
    Figure* figures[COUNT];

    figures[0] = new Rectangle1(4.0, 6.0);
    figures[1] = new Circle(3.0);
    figures[2] = new RightTriangle(3.0, 4.0);
    figures[3] = new Trapezoid(5.0, 3.0, 4.0);

    for (int i = 0; i < COUNT; i++) {
        cout << "Figure " << i << " area: " << figures[i]->getArea() << endl;
    }

    for (int i = 0; i < COUNT; i++) {
        delete figures[i];
    }

    return 0;
}