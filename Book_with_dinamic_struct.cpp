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



	void show() {
		cout << "month" << month << "day" << day << "hour" << hour << "minuts" << minuts;
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
    Train_Station() : timeWhen(0, 0, 0, 0), timeWay(0, 0, 0, 0), number(0), toWhere("Without end") {}
    Train_Station(time_table timeWhen, time_table timeWay, int number, const string& toWhere)
        : timeWhen(timeWhen), timeWay(timeWay), number(number), toWhere(toWhere) {}

    time_table getTimeWhen() const { return timeWhen; }
    time_table getTimeWay() const { return timeWay; }
    int getNumber() const { return number; }
    string getToWhere() const { return toWhere; }

    void setTimeWhen(time_table tw) { timeWhen = tw; }
    void setTimeWay(time_table tw) { timeWay = tw; }
    void setNumber(int num) { number = num; }
    void setToWhere(const string& where) { toWhere = where; }
};


class TrainManager {
private:
    vector<Train_Station> ways;

    vector<Train_Station>::iterator findByNumber(int num) {
        return find_if(ways.begin(), ways.end(),
            [num](const Train_Station& t) { return t.getNumber() == num; });
    }

    bool confirm(const string& question) {
        int answer = 0;
        cout << question << " (1 - да, 0 - нет): ";
        cin >> answer;
        return answer == 1;
    }

    void changeNumber(Train_Station& train) {
        int newNum;
        cout << "Новый номер: ";
        cin >> newNum;
        if (newNum != train.getNumber() && findByNumber(newNum) != ways.end()) {
            cout << "Номер " << newNum << " занят, оставляю старый." << endl;
            return;
        }
        train.setNumber(newNum);
    }

    void changeWhere(Train_Station& train) {
        string where;
        cout << "Новый пункт назначения: ";
        cin >> ws;
        getline(cin, where);
        train.setToWhere(where);
    }

public:
    TrainManager(vector<Train_Station> start, size_t places) : ways(move(start)) {
        ways.reserve(places);
    }

    void showAllWays() const {
        for (const auto& train : ways) {
            cout << "Поезд №" << train.getNumber() << " в " << train.getToWhere() << endl;
        }
        cout << "Занято: " << ways.size() << " из " << ways.capacity() << " мест" << endl << endl;
    }

    void showOne(int searchNumber) const {
        for (const auto& train : ways) {
            if (train.getNumber() == searchNumber) {
                cout << "=== Поезд найден! ===" << endl;
                cout << "Номер поезда: " << train.getNumber() << endl;
                cout << "Пункт назначения: " << train.getToWhere() << endl;
                return;
            }
        }
        cout << "Поезд с номером " << searchNumber << " не найден." << endl;
    }

    void addTrain() {
        if (ways.size() == ways.capacity()) {
            cout << "Список полный: " << ways.size() << " из " << ways.capacity() << "." << endl;
            if (!confirm("Точно расширить список и добавить поезд?")) {
                cout << "Отмена." << endl;
                return;
            }
        }

        int num;
        cout << "Номер поезда: ";
        cin >> num;
        if (findByNumber(num) != ways.end()) {
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

        ways.push_back(Train_Station(when, way, num, where));
        cout << "Поезд добавлен. Занято: " << ways.size() << " из " << ways.capacity() << endl;
    }

    void removeTrain(int num) {
        auto it = findByNumber(num);
        if (it == ways.end()) {
            cout << "Поезд с номером " << num << " не найден." << endl;
            return;
        }
        ways.erase(it);
        cout << "Поезд удалён. Занято: " << ways.size() << " из " << ways.capacity() << endl;
    }

    void replaceTrain(int num) {
        auto it = findByNumber(num);
        if (it == ways.end()) {
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
                changeNumber(*it);
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
                changeNumber(*it);
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
};


int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    TrainManager manager({
        Train_Station(time_table(10, 15, 0, 0), time_table(2, 30, 0, 0), 102, "Киев"),
        Train_Station(time_table(14, 45, 0, 0), time_table(1, 15, 0, 0), 734, "Львов"),
        Train_Station(time_table(22, 0, 0, 0),  time_table(5, 0, 0, 0),  45,  "Одесса")
        }, 7);

    int choice = -1;
    while (choice != 0) {
        cout << endl << "1 - показать все, 2 - добавить, 3 - удалить, 4 - заменить, 0 - выход" << endl;
        cout << "Выбор: ";
        cin >> choice;

        int num;
        switch (choice) {
        case 1:
            manager.showAllWays();
            break;
        case 2:
            manager.addTrain();
            break;
        case 3:
            cout << "Номер поезда (0 - выход из программы): ";
            cin >> num;
            if (num == 0) { choice = 0; break; }
            manager.removeTrain(num);
            break;
        case 4:
            cout << "Номер поезда (0 - выход из программы): ";
            cin >> num;
            if (num == 0) { choice = 0; break; }
            manager.replaceTrain(num);
            break;
        }
    }
    return 0;
}