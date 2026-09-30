#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <limits>
#include <cctype>
#include <algorithm>
#include <format>

using namespace std;




class City {
protected:
    string name;
    double area;
    // civilians

public:
    City(): area{0.0} {}
    City(const string& name, double area) : name{ name }, area{ area } {}

    string getName() const { return name; }
    double getArea() const { return area; }
    void setName(const string& newName) { name = newName; }
    void setArea(double newArea) { area = newArea; }
};



class Country {
private:
    string name;
    vector<City> cities;
    string nativeLanguage;
    string president;
    // type_of_control

public:
    Country() = default;
    Country(const string& name, const vector<City>& cities,
        const string& nativeLanguage, const string& president)
        : name{ name }, cities{ cities },
        nativeLanguage{ nativeLanguage }, president{ president } {}

    string getcountryName() const { return name; }
    const vector<City>& getCities() const { return cities; }
    string getNativeLanguage() const { return nativeLanguage; }
    string getPresident() const { return president; }

    void setcountryName(const string& newName) { name = newName; }
    void setCities(const vector<City>& newCities) { cities = newCities; }
    void setNativeLanguage(const string& newLanguage) { nativeLanguage = newLanguage; }
    void setPresident(const string& newPresident) { president = newPresident; }

    bool hasCity(const vector<City>& v, const string& name)
    {
        auto it = find_if(v.begin(), v.end(), [&name](const City& c)
            {
                return c.getName() == name;
            });

        return it != v.end();
    }

    bool addCity(const City& c) {
        if (hasCity(cities, c.getName())) return false;   
        cities.push_back(c);
        return true;
    }

    bool removeCity(const string& cityName) {
        auto it = find_if(cities.begin(), cities.end(), [&cityName](const City& c) {
            return c.getName() == cityName;
            });
        if (it == cities.end()) return false;
        cities.erase(it);
        return true;
    }

    bool renameCity(const string& oldName, const string& newName) {
        if (hasCity(cities, newName)) return false;
        for (auto& c : cities) {
            if (c.getName() == oldName) {
                c.setName(newName);
                return true;
            }
        }
        return false;
    }

    bool setCityArea(const string& cityName, double newArea) {
        for (auto& c : cities) {
            if (c.getName() == cityName) {
                c.setArea(newArea);
                return true;
            }
        }
        return false;
    }


};


void printCountry(const Country& c) {
    cout << c.getcountryName() << " | язык: " << c.getNativeLanguage()
        << " | президент: " << c.getPresident() << '\n';
    for (const auto& city : c.getCities())
        cout << "    " << city.getName() << ", площадь: " << city.getArea() << '\n';
}

// только названия стран
void showCountries(const map<string, Country>& db) {
    for (const auto& [key, c] : db)
        cout << key << '\n';
}

// одна страна со всеми городами
bool showCountry(const map<string, Country>& db, const string& name) {
    auto it = db.find(name);
    if (it == db.end()) return false;
    printCountry(it->second);
    return true;
}

// все страны и города
void showAll(const map<string, Country>& db) {
    for (const auto& [key, c] : db)
        printCountry(c);
}



void save(const map<string, Country>& db, const string& path) {
    ofstream out(path);
    for (const auto& [key, c] : db) {
        out << c.getcountryName() << '|' << c.getNativeLanguage() << '|'
            << c.getPresident() << '|' << c.getCities().size() << '\n';
        for (const auto& city : c.getCities())
            out << city.getName() << '|' << city.getArea() << '\n';
    }
}

map<string, Country> load(const string& path) {
    map<string, Country> db;
    ifstream in(path);
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;  
        stringstream ss(line);
        string name, lang, pres, count;
        getline(ss, name, '|');
        getline(ss, lang, '|');
        getline(ss, pres, '|');
        getline(ss, count);

        vector<City> cities;
        for (int i = 0; i < stoi(count); ++i) {
            getline(in, line);
            stringstream cs(line);
            string cityName, area;
            getline(cs, cityName, '|');
            getline(cs, area);
            cities.emplace_back(cityName, stod(area));
        }
        db[name] = Country(name, cities, lang, pres);
    }
    return db;
}

string inputNewCountryName(const map<string, Country>& db) {
    string name;
    while (true) {
        cout << "Название страны: ";
        getline(cin, name);
        if (name.empty()) {
            cout << "it's empty";
            continue;
        }
        if (db.find(name) != db.end()) {
            cout << "this name already excist";
            continue;
        }
        break;
    }
    return name;
}



bool isBlank(const string& s) {
    return s.find_first_not_of(" \t") == string::npos;
}

City inputCity(const vector<City>& already) {
    string name;
    while (true) {
        cout << "Название города: ";
        getline(cin, name);
        if (isBlank(name)) {
            cout << "Название не может быть пустым\n";
            continue;
        }
        if (hasCity(already, name)) {
            cout << "Такой город в стране уже есть, введи другой\n";
            continue;
        }
        break;
    }

    double area;
    while (true) {
        cout << "Площадь города: ";
        string input;
        getline(cin, input);
        try {
            area = stod(input);
            if (area <= 0) {
                cout << "Площадь должна быть больше нуля\n";
                continue;
            }
            break;
        }
        catch (const invalid_argument&) {
            cout << "Введи число\n";
        }
        catch (const out_of_range&) {
            cout << "Слишком большое число\n";
        }
    }
    return City(name, area);
}

string inputNonBlank(const string& prompt) {
    string s;
    while (true) {
        cout << prompt;
        getline(cin, s);
        if (!isBlank(s)) return s;
        cout << "Строка не может быть пустой\n";
    }
}

bool askYesNo(const string& question) {
    string s; // char
    while (true) {
        cout << question << " (д/н): ";
        getline(cin, s);
        if (s == "д" || s == "Д" || s == "y" || s == "Y") return true; // tolower ot toupper
        if (s == "н" || s == "Н" || s == "n" || s == "N") return false;
        cout << "Введи д или н\n";
    }
}

Country inputCountry(const map<string, Country>& db) {
    string name = inputNewCountryName(db);
    string lang = inputNonBlank("Язык: ");
    string pres = inputNonBlank("Президент: ");

    vector<City> cities;
    while (true) {
        cities.push_back(inputCity(cities));
        if (cities.size() < 2) {
            cout << "Нужно минимум два города\n";
            continue;
        }
        if (!askYesNo("Добавить ещё город?")) break;
    }
    return Country(name, cities, lang, pres);
}

bool addCountry(map<string, Country>& db, const Country& c) {   // crot
    return db.insert({ c.getcountryName(), c }).second;
}

bool removeCountry(map<string, Country>& db, const string& name) {
    return db.erase(name) > 0;
}

bool addCity(map<string, Country>& db, const string& countryName, const City& c) {
    auto it = db.find(countryName);
    if (it == db.end()) return false;       
    return it->second.addCity(c);          
}

bool removeCity(map<string, Country>& db, const string& countryName, const string& cityName) {
    auto it = db.find(countryName);
    if (it == db.end()) return false;
    return it->second.removeCity(cityName);
}

double totalArea(const map<string, Country>& db) {
    double sum = 0.0;
    for (const auto& [key, c] : db)
        for (const auto& city : c.getCities())
            sum += city.getArea();
    return sum;
}

size_t totalCities(const map<string, Country>& db) {
    size_t count = 0;
    for (const auto& [key, c] : db)
        count += c.getCities().size();
    return count;
}

void showStats(const map<string, Country>& db) {
    cout << "Стран: " << db.size() << '\n';
    cout << "Городов: " << totalCities(db) << '\n';
    cout << "Общая площадь: " << totalArea(db) << '\n';
}


bool renameCountry(map<string, Country>& db, const string& oldName, const string& newName) {
    if (db.count(newName)) return false;
    auto node = db.extract(oldName);
    if (node.empty()) return false;
    node.key() = newName;
    node.mapped().setcountryName(newName);
    db.insert(move(node));
    return true;
}

void findCity(const map<string, Country>& db, const string& cityName) {
    bool found = false;
    for (const auto& [key, c] : db) {
        for (const auto& city : c.getCities()) {
            if (city.getName() == cityName) {
                cout << city.getName() << ", площадь " << city.getArea()
                    << ", страна: " << key << '\n';
                found = true;
            }
        }
    }
    if (!found) cout << "Город не найден\n";
}

double inputArea() {
    while (true) {
        cout << "Площадь: ";
        string s;
        getline(cin, s);
        try {
            double a = stod(s);
            if (a > 0) return a;
            cout << "Площадь должна быть больше нуля\n";
        }
        catch (...) {
            cout << "Введи число\n";
        }
    }
}

int inputChoice() {
    string s;
    getline(cin, s);
    try { return stoi(s); }
    catch (...) { return -1; }
}

void printMenu() {
    cout << "\n1  Показать страны\n"
        << "2  Показать все страны и города\n"
        << "3  Показать одну страну (поиск городов страны)\n"
        << "4  Добавить страну\n"
        << "5  Добавить город\n"
        << "6  Удалить страну\n"
        << "7  Удалить город\n"
        << "8  Изменить страну\n"
        << "9  Изменить город\n"
        << "10 Итоги\n"
        << "11 Поиск города\n"
        << "12 Сохранить в файл\n"
        << "0  Выход\n"
        << "Выбор: ";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    const string path = "forcountry.txt";
    map<string, Country> db = load(path);
    int choice;

    do {
        printMenu();
        choice = inputChoice();

        switch (choice) {
        case 1:
            showCountries(db);
            break;
        case 2:
            showAll(db);
            break;
        case 3: {
            string name = inputNonBlank("Страна: ");
            if (!showCountry(db, name)) cout << "Такой страны нет\n";
            break;
        }
        case 4: {
            Country c = inputCountry(db);
            printCountry(c);
            if (askYesNo("Всё верно?")) {
                addCountry(db, c);
                cout << "Страна добавлена\n";
            }
            break;
        }
        case 5: {
            string country = inputNonBlank("В какую страну: ");
            auto it = db.find(country);
            if (it == db.end()) {
                cout << "Такой страны нет\n";
                break;
            }
            City c = inputCity(it->second.getCities());
            addCity(db, country, c);
            cout << "Город добавлен\n";
            break;
        }
        case 6: {
            string name = inputNonBlank("Какую страну удалить: ");
            cout << (removeCountry(db, name) ? "Удалено\n" : "Такой страны нет\n");
            break;
        }
        case 7: {
            string country = inputNonBlank("Из какой страны: ");
            string city = inputNonBlank("Какой город удалить: ");
            cout << (removeCity(db, country, city) ? "Удалено\n" : "Страны или города нет\n");
            break;
        }
        case 8: {
            string country = inputNonBlank("Какую страну менять: ");
            auto it = db.find(country);
            if (it == db.end()) {
                cout << "Такой страны нет\n";
                break;
            }
            cout << "1 Название, 2 Язык, 3 Президент: ";
            int what = inputChoice();
            if (what == 1) {
                string newName = inputNonBlank("Новое название: ");
                cout << (renameCountry(db, country, newName) ? "Готово\n" : "Такая страна уже есть\n");
            }
            else if (what == 2) {
                it->second.setNativeLanguage(inputNonBlank("Новый язык: "));
                cout << "Готово\n";
            }
            else if (what == 3) {
                it->second.setPresident(inputNonBlank("Новый президент: "));
                cout << "Готово\n";
            }
            else {
                cout << "Нет такого пункта\n";
            }
            break;
        }
        case 9: {
            string country = inputNonBlank("В какой стране: ");
            auto it = db.find(country);
            if (it == db.end()) {
                cout << "Такой страны нет\n";
                break;
            }
            string city = inputNonBlank("Какой город менять: ");
            cout << "1 Название, 2 Площадь: ";
            int what = inputChoice();
            if (what == 1) {
                string newName = inputNonBlank("Новое название: ");
                cout << (it->second.renameCity(city, newName) ? "Готово\n" : "Города нет или такое название занято\n");
            }
            else if (what == 2) {
                cout << (it->second.setCityArea(city, inputArea()) ? "Готово\n" : "Такого города нет\n");
            }
            else {
                cout << "Нет такого пункта\n";
            }
            break;
        }
        case 10:
            showStats(db);
            break;
        case 11:
            findCity(db, inputNonBlank("Название города: "));
            break;
        case 12:
            save(db, path);
            cout << "Сохранено\n";
            break;
        case 0:
            save(db, path);
            cout << "Сохранено, пока\n";
            break;
        default:
            cout << "Нет такого пункта\n";
        }
    } while (choice != 0);
    return 0;
}