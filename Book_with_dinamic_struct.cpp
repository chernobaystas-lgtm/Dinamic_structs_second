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
    map<string, int> word_count;
    string word;

    while (file >> word) {
        word_count[word]++;
    }

    file.close();

    for (const auto& pair : word_count) {
        cout << pair.first << ": " << pair.second << "\n";
    }

    return 0;
}