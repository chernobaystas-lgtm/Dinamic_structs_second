#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <algorithm>
using namespace std;

void show(const vector<int>& list) {
    for (int x : list) { cout << x << " "; }
    cout << endl; 
}

int input(){}


int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);



    vector<int> numbers = { 11, 1, 56, -1, 2, 3, 4, 5, 999, 0 };

    vector<int>::iterator;

    

    cout << numbers.back();
    show(numbers);

    sort(numbers.begin(), numbers.end());
    show(numbers);

    for_each(numbers.begin(), numbers.end(), [](int& x) { x += 1; });
    show(numbers);

    for_each(numbers.begin(), numbers.end(), [](int& x) { x -= 1; });
    show(numbers);

    int target = 2;
    cout << erase(numbers, 5);
    show(numbers);


    return 0;
}