#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <random>
#include <fstream> 
#include <algorithm>
using namespace std;



int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    ifstream file("For_maps.txt");
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл\n";
        return 1;
    }
    map<string, int> myDictionary;
    string word;

    while (file >> word) {
        if (myDictionary.contains(word) == true) {
            myDictionary[word] += 1;
        }
        else {
            myDictionary[word] = 1;
        }
    }

    file.close();

    for (auto it : myDictionary) {
        cout << "key: " << it.first << "\t" << " value: " << it.second << endl;
    }

    return 0;
}