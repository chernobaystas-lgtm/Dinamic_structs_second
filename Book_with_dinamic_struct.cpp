#include <iostream>
#include <string>
#include <windows.h>
#include <cmath>
#include <fstream>
using namespace std;



int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    char MyFile[] = "C:\\Users\\Admin\\Visual Studio\\OOP\\Book_with_dinamic_struct";

    //ofstream Opened(MyFile);
    //if (Opened.fail()) { //!Opened.is_open()
    //    cerr << "Error" << endl;
    //    system("pause");
    //    return -1;
    //}



    //ofstream Opened;
    //Opened.open(MyFile); //ios::binary|ios::app
    fstream Opened;
    Opened.open(MyFile);
    if (Opened.fail()) { //!Opened.is_open()
        cerr << "Error" << endl;
        system("pause");
        return -1;
    }
    string str{ "My Start" };

    while (!Opened.eof()) {
        getline(Opened, str);
        cout << str << endl;
    }
 
    Opened.close();




    fstream Opened(MyFile, ios::app);
    Opened.open(MyFile);
    if (Opened.fail()) { //!Opened.is_open()
        cerr << "Error" << endl;
        system("pause");
        return -1;
    }
    string str{ "My New WAy" };
    Opened << str;
    Opened.close();




    Opened.open(MyFile, ios::in);
    if (Opened.fail()) { //!Opened.is_open()
        cerr << "Error" << endl;
        system("pause");
        return -1;
    }
    string str{ "My Start" };

    while (!Opened.eof()) {
        getline(Opened, str);
        cout << str << endl;
    }

    Opened.close();

    /*string str{ "My Start" };
    Opened << "Begin" << endl;
    Opened << str;
    Opened.close();*/

    return 0;
}