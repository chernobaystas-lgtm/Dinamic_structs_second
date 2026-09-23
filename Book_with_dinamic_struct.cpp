#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <algorithm>
using namespace std;




struct time_table {

    int month{ 0 };
    int day{ 0 };
    int hour{ 0 };
    int minuts{ 0 };



    void show(const vector<int>& list) {
        for (int x : list) { cout << x << " "; }
        cout << endl;
    }

    void input() {
        cout << "input month";
        cin >> month;
        cout << "input day";
        cin >> day;
        cout << "input hour";
        cin >> hour;
        cout << "input minuts";
        cin >> minuts;
    }

};




class Train_Station {
private:
    time_table timeWhen;
    time_table timeWay;
    int number;
    string toWhere;
public:
    Train_Station(): timeWhen(0, 0, 0, 0), timeWay(0, 0, 0, 0), number(0), toWhere("Without end") {}
    Train_Station(time_table timeWhen, time_table timeWay, int number, const string& toWhere): timeWhen(timeWhen), timeWay(timeWay), number(number), toWhere(toWhere){}

    time_table getTimeWhen() const { return timeWhen; }
    time_table getTimeWay() const { return timeWay; }
    int getNumber() const { return number; }
    string getToWhere() const { return toWhere; }

    void setTimeWhen(time_table tw) { timeWhen = tw; }
    void setTimeWay(time_table tw) { timeWay = tw; }
    void setNumber(int num) { number = num; }
    void setToWhere(const string& where) { toWhere = where; }





    void showAllWays(const vector<Train_Station>& list) {
        for (const auto& train : list) {
            cout << "Поезд №" << train.getNumber() << " в " << train.getToWhere() << endl;
        }
        cout << endl;
    }

    void showOne(const vector<Train_Station>& list, int searchNumber) {
        bool found = false;

        for (const auto& train : list) {
            if (train.getNumber() == searchNumber) {
                cout << "=== Поезд найден! ===" << endl;
                cout << "Номер поезда: " << train.getNumber() << endl;
                cout << "Пункт назначения: " << train.getToWhere() << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Поезд с номером " << searchNumber << " не найден." << endl;
        }
    }


    static void addTrain(vector<Train_Station>& list) {
        if (list.size() == list.capacity()) {
            cout << "Список полный: " << list.size() << " из " << list.capacity() << "." << endl;
            if (!confirm("Точно расширить список и добавить поезд?")) {
                cout << "Отмена." << endl;
                return;
            }
        }

        int num;
        cout << "Номер поезда: ";
        cin >> num;
        if (findByNumber(list, num) != list.end()) {
            cout << "Поезд с номером " << num << " уже есть." << endl;
            return;
        }

        string where;
        cout << "Пункт назначения: ";
        cin >> ws;
        getline(cin, where);

        time_table when, way;
        cout << "Время отправления:" << endl;
        when.input();
        cout << "Время в пути:" << endl;
        way.input();

        list.push_back(Train_Station(when, way, num, where));
        cout << "Поезд добавлен. Занято: " << list.size() << " из " << list.capacity() << endl;
    }

    static void removeTrain(vector<Train_Station>& list, int num) {
        auto it = findByNumber(list, num);
        if (it == list.end()) {
            cout << "Поезд с номером " << num << " не найден." << endl;
            return;
        }
        list.erase(it);
        cout << "Поезд удалён. Занято: " << list.size() << " из " << list.capacity() << endl;
    }

    static void replaceTrain(vector<Train_Station>& list, int num) {
        auto it = findByNumber(list, num);
        if (it == list.end()) {
            cout << "Поезд с номером " << num << " не найден." << endl;
            return;
        }

        if (!confirm("Точно заменить поезд №" + to_string(num) + "?")) {
            cout << "Отмена." << endl;
            return;
        }

        int choice = -1;
        while (choice != 0) {
            cout << endl << "Что заменить?" << endl;
            cout << "1 - номер" << endl;
            cout << "2 - пункт назначения" << endl;
            cout << "3 - время отправления" << endl;
            cout << "4 - время в пути" << endl;
            cout << "5 - всё сразу" << endl;
            cout << "0 - выход" << endl;
            cout << "Выбор: ";
            cin >> choice;

            switch (choice) {
            case 1:
                changeNumber(list, *it);
                break;
            case 2:
                changeWhere(*it);
                break;
            case 3: {
                time_table t;
                t.input();
                it->setTimeWhen(t);
                break;
            }
            case 4: {
                time_table t;
                t.input();
                it->setTimeWay(t);
                break;
            }
            case 5: {
                changeNumber(list, *it);
                changeWhere(*it);
                time_table t1, t2;
                cout << "Время отправления:" << endl;
                t1.input();
                cout << "Время в пути:" << endl;
                t2.input();
                it->setTimeWhen(t1);
                it->setTimeWay(t2);
                break;
            }
            case 0:
                cout << "Готово." << endl;
                break;
            default:
                cout << "Нет такого пункта." << endl;
            }
        }
    }
    private:
        static void changeNumber(vector<Train_Station>& list, Train_Station& train) {
            int newNum;
            cout << "Новый номер: ";
            cin >> newNum;
            if (newNum != train.getNumber() && findByNumber(list, newNum) != list.end()) {
                cout << "Номер " << newNum << " занят, оставляю старый." << endl;
                return;
            }
            train.setNumber(newNum);
        }

        static void changeWhere(Train_Station& train) {
            string where;
            cout << "Новый пункт назначения: ";
            cin >> ws;
            getline(cin, where);
            train.setToWhere(where);
        }

        static bool confirm(const string& question) {
            int answer = 0;
            cout << question << " (1 - да, 0 - нет): ";
            cin >> answer;
            return answer == 1;
        }

        static vector<Train_Station>::iterator findByNumber(vector<Train_Station>& list, int num) {
            return find_if(list.begin(), list.end(),
                [num](const Train_Station& t) { return t.getNumber() == num; });
        }
};

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);


    vector<Train_Station> Ways;
    Ways.reserve(7);
    Ways.push_back(Train_Station(time_table(10, 15, 0, 0), time_table(2, 30, 0, 0), 102, "Киев"));
    Ways.push_back(Train_Station(time_table(14, 45, 0, 0), time_table(1, 15, 0, 0), 734, "Львов"));
    Ways.push_back(Train_Station(time_table(22, 0, 0, 0), time_table(5, 0, 0, 0), 45, "Одесса"));

    Train_Station helper;
    int choice = -1;
    while (choice != 0) {
        cout << endl << "1 - показать все, 2 - добавить, 3 - удалить, 4 - заменить, 0 - выход" << endl;
        cout << "Выбор: ";
        cin >> choice;

        int num;
        switch (choice) {
        case 1:
            helper.showAllWays(Ways);
            break;
        case 2:
            Train_Station::addTrain(Ways);
            break;
        case 3:
            cout << "Номер поезда: ";
            cin >> num;
            Train_Station::removeTrain(Ways, num);
            break;
        case 4:
            cout << "Номер поезда: ";
            cin >> num;
            Train_Station::replaceTrain(Ways, num);
            break;
        case 0:
            cout << "exit";
        }
    }
    return 0;
}