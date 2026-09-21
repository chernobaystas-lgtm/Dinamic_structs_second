#include <iostream>
#include <string>
#include <windows.h>
#include <memory>
#include <fstream>
#include <limits>
#include <stdexcept>
using namespace std;


#define NOMINMAX

enum class Answer { No = 0, Yes = 1 };

class Console {
public:
    static bool askYesNo(const string& question) {
        while (true) {
            cout << question << " (1 - так, 0 - ні): ";
            int value;
            if (cin >> value && (value == 0 || value == 1)) {
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                return static_cast<Answer>(value) == Answer::Yes;
            }
            cin.clear();  
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            cout << "Введіть 1 або 0." << endl;
        }
    }

    static int readInt() {
        while (true) {
            int value;
            if (cin >> value) {
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                return value;
            }
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            cout << "Введіть число." << endl;
        }
    }
};

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

    static Firm readFromConsole() {
        string name, owner, adress, prof, phone;
        cout << "Назва: ";      getline(cin, name);
        cout << "Власник: ";    getline(cin, owner);
        cout << "Адреса: ";     getline(cin, adress);
        cout << "Діяльність: "; getline(cin, prof);
        cout << "Телефон: ";    getline(cin, phone);
        return Firm(name, owner, adress, prof, phone);
    }
};


class Directory{
private:
    unique_ptr<Firm[]> firms;
    int count;       
    int capacity;      
    string filename;
    bool modified;

    void ensureCapacity(int needed) {
        if (needed <= capacity) return;

        int newCapacity = (capacity == 0) ? 4 : capacity * 2;
        while (newCapacity < needed) newCapacity *= 2;

        auto newArr = make_unique<Firm[]>(newCapacity);
        for (int i = 0; i < count && i < capacity; i++) {
            newArr[i] = move(firms[i]);
        }

        firms = move(newArr);
        capacity = newCapacity;
    }
public:
    Directory(const string& file)
        : firms(nullptr), count(0), capacity(0), filename(file), modified(false) {}

    bool isModified() const { return modified; }
    Directory(const Directory&) = delete;
    Directory& operator=(const Directory&) = delete;


    bool loadFromFile() {
        ifstream in(filename);
        if (!in.is_open()) {
            cerr << "Не вдалося відкрити файл для читання: " << filename << endl;
            return false;
        }

        count = 0; 
        Firm temp;
        while (in >> temp) {
            ensureCapacity(count + 1);
            firms[count] = move(temp);
            count++;
        }

        modified = false;
        return true;
    }

    bool saveToFile() {
        ofstream out(filename, ios::out | ios::trunc);
        if (!out.is_open()) {
            cerr << "Не вдалося відкрити файл для запису: " << filename << endl;
            return false;
        }

        for (int i = 0; i < count; i++) {
            out << firms[i];
        }

        modified = false;
        return true;
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

enum class MenuItem {
    Exit, ShowAll, Add, Remove,
    FindName, FindOwner, FindPhone, FindProfession,
    Save, Load
};

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    auto dir = make_unique<Directory>("Firma.txt");
    dir->loadFromFile();

    if (dir->isEmpty()) {
        cout << "Довідник порожній. Почнемо з додавання фірм." << endl;
    }
    else if (dir->size() == 1) {
        cout << "У довіднику знайдено одну фірму:" << endl;
        dir->printAll();

        if (Console::askYesNo("Додати ще?")) {
            cout << "Скільки фірм хочете додати? ";
            int n = Console::readInt();
            for (int i = 0; i < n; i++) {
                cout << "--- Фірма #" << (i + 1) << " ---" << endl;
                dir->add(Firm::readFromConsole());
            }
        }
    }
    else {
        cout << "У довіднику " << dir->size() << " фірм(и)." << endl;
    }

    MenuItem choice = MenuItem::ShowAll;   // любое значение кроме Exit
    while (choice != MenuItem::Exit) {
        cout << "\n=== МЕНЮ ===" << endl;
        cout << "1. Показати всі фірми" << endl;
        cout << "2. Додати фірму" << endl;
        cout << "3. Видалити фірму за індексом" << endl;
        cout << "4. Пошук за назвою" << endl;
        cout << "5. Пошук за власником" << endl;
        cout << "6. Пошук за телефоном" << endl;
        cout << "7. Пошук за родом діяльності" << endl;
        cout << "8. Зберегти" << endl;
        cout << "9. Завантажити з файлу" << endl;
        cout << "0. Вихід" << endl;
        cout << "Ваш вибір: ";

        int input = Console::readInt();
        if (input < 0 || input > static_cast<int>(MenuItem::Load)) {
            cout << "Невірний пункт меню." << endl;
            continue;
        }
        choice = static_cast<MenuItem>(input);

        try {
            switch (choice) {
            case MenuItem::ShowAll:
                dir->printAll();
                break;

            case MenuItem::Add:
                cout << "--- Нова фірма ---" << endl;
                dir->add(Firm::readFromConsole());
                cout << "Додано." << endl;
                break;

            case MenuItem::Remove:
                cout << "Індекс запису для видалення: ";
                dir->remove(Console::readInt());
                cout << "Видалено." << endl;
                break;

            case MenuItem::FindName: {
                cout << "Назва для пошуку: ";
                string q; getline(cin, q);
                dir->findByName(q);
                break;
            }
            case MenuItem::FindOwner: {
                cout << "Власник для пошуку: ";
                string q; getline(cin, q);
                dir->findByOwner(q);
                break;
            }
            case MenuItem::FindPhone: {
                cout << "Телефон для пошуку: ";
                string q; getline(cin, q);
                dir->findByPhone(q);
                break;
            }
            case MenuItem::FindProfession: {
                cout << "Рід діяльності для пошуку: ";
                string q; getline(cin, q);
                dir->findByProfession(q);
                break;
            }

            case MenuItem::Save:
                if (dir->saveToFile()) cout << "Збережено." << endl;
                break;

            case MenuItem::Load:
                if (dir->isModified() &&
                    !Console::askYesNo("Незбережені зміни буде втрачено. Продовжити?")) break;
                if (dir->loadFromFile()) cout << "Завантажено." << endl;
                break;

            case MenuItem::Exit:
                if (dir->isModified() &&
                    Console::askYesNo("Є незбережені зміни. Зберегти?")) {
                    dir->saveToFile();
                }
                cout << "Вихід..." << endl;
                break;
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