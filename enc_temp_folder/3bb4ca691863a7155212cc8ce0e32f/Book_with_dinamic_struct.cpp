#include <iostream>
#include <string>
#include <windows.h>
#include <cmath>

using namespace std;



int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    do {
    
        try {
            string  x;
            cout << "Input from 1 to 100" << endl;
            cin >> x;
            long long result = 0;
            for (int i = 0; i < x.length(); i++) {
                int digit = x[i] - '0';
                result = result * 10 + digit;
                if (result > 1) {  
                    throw string("число виходить за межі");
                }
                if (result < 1) {
                    throw string("число виходить за межі");
                }
                if (result > 2147483647) {
                    throw string("число виходить за межі int");
                }
            }
    }
        catch (const string& msg) {
            cerr << "Error: " << msg << " is out of range" << endl;
        }
    
    cout << "All good" << endl;
    } while (17);

    return 0;
}