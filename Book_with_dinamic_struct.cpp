#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <set>
#include <iostream>
#include <random>
#include <fstream> 
#include <algorithm>
using namespace std;

const string FILENAME = "For_sets.txt";
const size_t IPS_PER_DAY = 100;
const int TOTAL_DAYS = 3;

void generate_and_write(int total_days, size_t ips_per_day) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist_byte(1, 5);

    ofstream file(FILENAME, ios::out | ios::trunc);
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл для записи!\n";
        return;
    }

    for (int d = 0; d < total_days; ++d) {
        set<string> day_ips;
        while (day_ips.size() < ips_per_day) {
            string ip = to_string(dist_byte(gen)) + "." +
                to_string(dist_byte(gen)) + "." +
                to_string(dist_byte(gen)) + "." +
                to_string(dist_byte(gen));
            day_ips.insert(ip);
        }

        file << "#" << (d + 1) << " Day\n";
        for (const auto& ip : day_ips) file << ip << "\n";
    }

    file.close();
    cout << "Файл " << FILENAME << " записан.\n\n";
}


vector<set<string>> read_days_from_file(const string& filename) {
    vector<set<string>> days;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл для чтения!\n";
        return days;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        if (line.find("Day") != string::npos) {
            days.emplace_back(); 
        }
        else if (!days.empty()) {
            days.back().insert(line);
        }
    }

    file.close();
    return days;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    generate_and_write(TOTAL_DAYS, IPS_PER_DAY);

    vector<set<string>> days = read_days_from_file(FILENAME);
    if (days.empty()) return 1;


    vector<set<string>> by_days_count(days.size() + 1);

    set<string> seen;
    for (const auto& day : days) seen.insert(day.begin(), day.end());

    for (const auto& ip : seen) {
        int count = 0;
        for (const auto& day : days) {
            if (day.count(ip)) count++;
        }
        by_days_count[count].insert(ip);
    }

    for (int k = 2; k <= TOTAL_DAYS; ++k) {
        cout << "ВІДВІДУВАЧІ, ЯКІ ЗАХОДИЛИ РІВНО " << k << " ДНІ (" << by_days_count[k].size() << "):" << endl;
        for (const auto& ip : by_days_count[k]) cout << ip << " ";
        cout << "\n\n";
    }

    cout << "ПОСТІЙНІ КЛІЄНТИ (заходили ВСІ " << TOTAL_DAYS << " дні): "
        << by_days_count[TOTAL_DAYS].size() << endl;
    for (const auto& ip : by_days_count[TOTAL_DAYS]) cout << ip << " ";
    cout << "\n\n";

    return 0;
}