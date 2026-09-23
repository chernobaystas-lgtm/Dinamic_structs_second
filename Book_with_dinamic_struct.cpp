#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <algorithm>
using namespace std;



void show(const std::vector<int>& list) {
    for (int x : list) { cout << x << " "; }
    cout << endl;
}

bool myPredicate(int x) {
    return x > 100;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);



    vector<int> numbers = { 1, 2, 5, 2, 7, 5, 2, 9 };

    vector<int>::iterator;

    int target = 2;

    cout << numbers.back();
    show(numbers);

    sort(numbers.begin(), numbers.end());
    show(numbers);

    for_each(numbers.begin(), numbers.end(), [](int& x) { x += 1; });
    show(numbers);

    for_each(numbers.begin(), numbers.end(), [](int& x) { x -= 1; });
    show(numbers);

    cout << erase(numbers, target) << endl;        
    show(numbers);                                

    cout << erase_if(numbers, myPredicate) << endl; 
    show(numbers);

    return 0;
}