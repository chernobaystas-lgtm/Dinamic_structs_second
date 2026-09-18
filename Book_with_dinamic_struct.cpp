#include <iostream>
#include <string>
#include <windows.h>
#include <cmath>
#include <fstream>
using namespace std;


class Firm {
private:
    string name_of_company{ "No thing" };
    string Owner{ "No name" };
    string Adress{ "Without adress" };
    string profession{ "Profession" };
    string telephone{ "No telephone"};
public:
    Firm() {}
    Firm(const string& name, const string& owner, const string& adress,
        const string& profession, const string& phone)
        : name_of_company{ name }, Owner{ owner }, Adress{ adress },
        profession{ profession }, telephone{ phone } {}

    friend istream& operator>>(istream& s, Firm& f) {
        string name, owner, adress, prof, phone;

        if (getline(s, name) && getline(s, owner) &&
            getline(s, adress) && getline(s, prof) &&
            getline(s, phone))
        {
            f.name_of_company = name;
            f.Owner = owner;
            f.Adress = adress;
            f.profession = prof;
            f.telephone = phone;
        }
        else {
            s.setstate(ios::failbit);   
        }

        return s;
    }
    friend ostream& operator<<(ostream& s, const Firm& Firm) {
        s << Firm.name_of_company << endl;
        s << Firm.Owner << endl;
        s << Firm.Adress << endl;
        s << Firm.profession << endl;
        s << Firm.telephone << endl;
        return s;
    }

    string getName() const { return name_of_company; }
    string getOwner() const { return Owner; }
    string getAdress() const { return Adress; }
    string getProfession() const { return profession; }
    string getPhone() const { return telephone; }
};


class Directory{
private:
    Firm* firms;      
    int count;       
    int capacity;      
    string filename;

    void ensureCapacity(int needed) {
        if (needed <= capacity) return;

        int newCapacity = (capacity == 0) ? 4 : capacity * 2;
        while (newCapacity < needed) newCapacity *= 2;

        Firm* newArr = new Firm[newCapacity];
        for (int i = 0; i < count && i < capacity; i++) {
            newArr[i] = firms[i];
        }

        delete[] firms;
        firms = newArr;
        capacity = newCapacity;
    }
public:
    Directory(const string& file) : firms(nullptr), count(0), capacity(0), filename(file) {}

    Directory(const Directory&) = delete;
    Directory& operator=(const Directory&) = delete;

    ~Directory() {
        delete[] firms;
    }

    void loadFromFile() {
        ifstream in(filename);
        if (!in.is_open()) {
            cerr << "Не вдалося відкрити файл для читання: " << filename << endl;
            return;
        }

        Firm temp;
        while (in >> temp) {
            ensureCapacity(count + 1);
            firms[count] = temp;
            count++;
        }

        in.close();
    }

    void saveToFile() const {
        ofstream out(filename, ios::out | ios::trunc);  
        if (!out.is_open()) {
            cerr << "Не вдалося відкрити файл для запису: " << filename << endl;
            return;
        }

        for (int i = 0; i < count; i++) {
            out << firms[i];
        }

        out.close();
    }

    void add(const Firm& f) {
        ensureCapacity(count + 1);
        firms[count] = f;
        count++;
        saveToFile();     
    }
    void remove(int index) {
        if (count == 0) {
            throw runtime_error("Довідник порожній, видаляти нічого.");
        }
        if (index < 0 || index >= count) {
            throw out_of_range("Невірний індекс запису.");
        }
        for (int i = index; i < count - 1; i++) {
            firms[i] = firms[i + 1];
        }
        count--;
        saveToFile();
    }

    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == capacity; }   
    int size() const { return count; }

    void printAll() const {
        if (count == 0) {
            cout << "Довідник порожній." << endl;
            return;
        }

        for (int i = 0; i < count; i++) {
            cout << "--- Фірма #" << i << " ---" << endl;
            cout << firms[i];   
            cout << endl;
        }
    }

    void findByName(const string& query) const {
        bool found = false;

        for (int i = 0; i < count; i++) {
            if (firms[i].getName() == query) {
                cout << "--- Знайдено (запис #" << i << ") ---" << endl;
                cout << firms[i];
                cout << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "Фірм з назвою \"" << query << "\" не знайдено." << endl;
        }
    }
    void findByOwner(const string& query) const {
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (firms[i].getOwner() == query) {
                cout << "--- Знайдено (запис #" << i << ") ---" << endl;
                cout << firms[i] << endl;
                found = true;
            }
        }
        if (!found) cout << "Фірм з власником \"" << query << "\" не знайдено." << endl;
    }

    void findByPhone(const string& query) const {
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (firms[i].getPhone() == query) {
                cout << "--- Знайдено (запис #" << i << ") ---" << endl;
                cout << firms[i] << endl;
                found = true;
            }
        }
        if (!found) cout << "Фірм з телефоном \"" << query << "\" не знайдено." << endl;
    }

    void findByProfession(const string& query) const {
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (firms[i].getProfession() == query) {
                cout << "--- Знайдено (запис #" << i << ") ---" << endl;
                cout << firms[i] << endl;
                found = true;
            }
        }
        if (!found) cout << "Фірм з родом діяльності \"" << query << "\" не знайдено." << endl;
    }
};

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    string filepath = "Firma.txt";
    Directory dir(filepath);
    dir.loadFromFile();

    if (dir.isEmpty()) {
        cout << "Довідник порожній. Почнемо з додавання фірм." << endl;
    }
    else if (dir.size() == 1) {
        cout << "У довіднику знайдено одну фірму:" << endl;
        dir.printAll();

        cout << "Додати ще? (1 - так, 0 - ні): ";
        int answer;
        cin >> answer;
        cin.ignore();

        if (answer == 1) {
            cout << "Скільки фірм хочете додати? ";
            int n;
            cin >> n;
            cin.ignore();

            for (int i = 0; i < n; i++) {
                cout << "--- Фірма #" << (i + 1) << " ---" << endl;
                string name, owner, adress, prof, phone;
                cout << "Назва: ";      getline(cin, name);
                cout << "Власник: ";    getline(cin, owner);
                cout << "Адреса: ";     getline(cin, adress);
                cout << "Діяльність: "; getline(cin, prof);
                cout << "Телефон: ";    getline(cin, phone);

                dir.add(Firm(name, owner, adress, prof, phone));
            }
        }
    }
    else {
        cout << "У довіднику " << dir.size() << " фірм(и)." << endl;
    }

    int choice = -1;
    while (choice != 0) {
        cout << "\n=== МЕНЮ ===" << endl;
        cout << "1. Показати всі фірми" << endl;
        cout << "2. Додати фірму" << endl;
        cout << "3. Видалити фірму за індексом" << endl;
        cout << "4. Пошук за назвою" << endl;
        cout << "5. Пошук за власником" << endl;
        cout << "6. Пошук за телефоном" << endl;
        cout << "7. Пошук за родом діяльності" << endl;
        cout << "0. Вихід" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;
        cin.ignore();

        try {
            switch (choice) {
            case 1:
                if (dir.isEmpty())
                    cout << "Довідник порожній." << endl;
                else
                    dir.printAll();
                break;

            case 2: {
                cout << "--- Нова фірма ---" << endl;
                string name, owner, adress, prof, phone;
                cout << "Назва: ";      getline(cin, name);
                cout << "Власник: ";    getline(cin, owner);
                cout << "Адреса: ";     getline(cin, adress);
                cout << "Діяльність: "; getline(cin, prof);
                cout << "Телефон: ";    getline(cin, phone);
                dir.add(Firm(name, owner, adress, prof, phone));
                cout << "Додано." << endl;
                break;
            }

            case 3: {
                cout << "Індекс запису для видалення: ";
                int idx;
                cin >> idx;
                dir.remove(idx);   
                cout << "Видалено." << endl;
                break;
            }

            case 4: {
                cout << "Назва для пошуку: ";
                string q; getline(cin, q);
                dir.findByName(q);
                break;
            }
            case 5: {
                cout << "Власник для пошуку: ";
                string q; getline(cin, q);
                dir.findByOwner(q);
                break;
            }
            case 6: {
                cout << "Телефон для пошуку: ";
                string q; getline(cin, q);
                dir.findByPhone(q);
                break;
            }
            case 7: {
                cout << "Рід діяльності для пошуку: ";
                string q; getline(cin, q);
                dir.findByProfession(q);
                break;
            }

            case 0:
                cout << "Вихід..." << endl;
                break;

            default:
                cout << "Невірний пункт меню." << endl;
            }
        }
        catch (const out_of_range& e) {
            cout << "Помилка: " << e.what() << endl;
        }
        catch (const runtime_error& e) {
            cout << "Помилка: " << e.what() << endl;
        }
        catch (...) {
            cout << "Невідома помилка." << endl;
        }
    }

    return 0;
}