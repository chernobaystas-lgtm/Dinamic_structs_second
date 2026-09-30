#include "Common.h"




class City {
protected:
    string name;
    double area;

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

public:
    Country() = default;
    Country(const string& name, const vector<City>& cities,
        const string& nativeLanguage, const string& president)
        : name{ name }, cities{ cities },
        nativeLanguage{ nativeLanguage }, president{ president } {}

    string getName() const { return name; }
    const vector<City>& getCities() const { return cities; }
    string getNativeLanguage() const { return nativeLanguage; }
    string getPresident() const { return president; }

    void setName(const string& newName) { name = newName; }
    void setCities(const vector<City>& newCities) { cities = newCities; }
    void setNativeLanguage(const string& newLanguage) { nativeLanguage = newLanguage; }
    void setPresident(const string& newPresident) { president = newPresident; }




};


void save(const map<string, Country>& db, const string& path) {
    ofstream out(path);
    for (const auto& [key, c] : db) {
        out << c.getName() << '|' << c.getNativeLanguage() << '|'
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


int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);


   

    return 0;
}