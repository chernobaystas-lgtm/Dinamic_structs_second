#include <iostream>
#include <string>
#include <windows.h>
#include <cmath>
#include <fstream>
using namespace std;


class Myclass {
private:
    string name{ "No thing" };
    int number = 0;
    double l = 0.0;
public:
    Myclass() {}
    Myclass(const string& name, int number) : name{ name }, number{ number } {}  //NEW: const string&

    friend istream& operator>>(istream& s, Myclass& myclass) {
        getline(s, myclass.name);
        s >> myclass.number;
        s.ignore();
        s >> myclass.l;
        if (s.peek() == '\n') s.ignore();

        return s;
    }
    friend ostream& operator<<(ostream& s, const Myclass& myclass) {
        s << myclass.name << endl;
        s << myclass.number << endl;
        return s;
    }
};

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    char MyFile[] = "C:\\Users\\Admin\\Visual Studio\\OOP\\Book_with_dinamic_struct\\MyNEwFile.txt";

    //ofstream Opened(MyFile);
    //if (Opened.fail()) { //!Opened.is_open()
    //    cerr << "Error" << endl;
    //    system("pause");
    //    return -1;
    //}



    //ofstream Opened;
    //Opened.open(MyFile); //ios::binary|ios::app
    Myclass myclass;
    fstream Opened;
    Opened.open(MyFile);  
    if (Opened.fail()) { //!Opened.is_open()
        cerr << "Error" << endl;
        system("pause");
        return -1;
    }
    /*string str{ "My Start" };*/

    //while (!Opened.eof()) {
    //    getline(Opened, str);
    //    cout << str << endl;
    //}

    //Opened >> myclass;
    //cout << myclass << endl;
    while (Opened >> myclass) { 
        if (Opened.peek() == '\n') Opened.ignore();  
        cout << myclass << endl;
    }
    Opened.close();
    Opened.clear();



    Opened.open(MyFile, ios::out | ios::app);
    //Opened.open(MyFile); 
    if (Opened.fail()) { //!Opened.is_open()
        cerr << "Error" << endl;
        system("pause");
        return -1;
    }
    //string str{ "My New WAy" };
    //Opened << str;
    Opened << Myclass("My New WAy", 1); 
    Opened.close();
    Opened.clear();  




    Opened.open(MyFile, ios::in);
    if (Opened.fail()) { //!Opened.is_open()
        cerr << "Error" << endl;
        system("pause");
        return -1;
    }
    string str1{ "My Start" };

    //while (!Opened.eof()) {
    //    getline(Opened, str1);
    //    cout << str1 << endl;
    //}
    while (getline(Opened, str1)) { 
        cout << str1 << endl;
    }

    Opened.close();

    /*string str{ "My Start" };
    Opened << "Begin" << endl;
    Opened << str;
    Opened.close();*/

    return 0;
}