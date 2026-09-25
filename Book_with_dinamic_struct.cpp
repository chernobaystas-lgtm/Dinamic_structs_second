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



enum class Answer { A, B, C, D, NONE };

char answerToChar(Answer a) {
    switch (a) {
    case Answer::A: return 'A';
    case Answer::B: return 'B';
    case Answer::C: return 'C';
    case Answer::D: return 'D';
    default: return '?';
    }
}

Answer charToAnswer(char c) {
    switch (toupper(c)) {
    case 'A': return Answer::A;
    case 'B': return Answer::B;
    case 'C': return Answer::C;
    case 'D': return Answer::D;
    default: return Answer::NONE;
    }
}

struct Question {
    string text;
    string options[4];
};

map<int, Answer> read_correct_answers(const string& filename) {
    map<int, Answer> answers;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл з відповідями\n";
        return answers;
    }

    int num;
    char letter;
    while (file >> num >> letter) {
        answers[num] = charToAnswer(letter);
    }

    file.close();
    return answers;
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    vector<Question> questions = {
        {"Столиця України?", {"Львів", "Одеса", "Київ", "Харків"}},
        {"Хто написав \"Кобзар\"?", {"Франко", "Шевченко", "Леся Українка", "Гоголь"}},
        {"Найдовша річка України?", {"Дніпро", "Дністер", "Буг", "Десна"}},
        {"Скільки областей в Україні?", {"24", "25", "26", "27"}},
        {"У якому році Україна здобула незалежність?", {"1989", "1990", "1991", "1992"}},
        {"Найвища гора України?", {"Говерла", "Петрос", "Піп Іван", "Ребра"}},
        {"Яка мова офіційна в Україні?", {"Російська", "Українська", "Польська", "Англійська"}},
        {"Автор \"Лісової пісні\"?", {"Шевченко", "Леся Українка", "Франко", "Коцюбинський"}},
        {"Найбільше місто України за населенням?", {"Львів", "Одеса", "Харків", "Київ"}},
        {"Валюта України?", {"Рубль", "Злотий", "Гривня", "Євро"}},
        {"Скільки букв в українському алфавіті?", {"32", "33", "34", "35"}},
        {"Національний символ України, крім прапора?", {"Тризуб", "Орел", "Лев", "Ведмідь"}}
    };

    map<int, Answer> correct = read_correct_answers("For_maps2.txt");
    if (correct.empty()) {
        cerr << "Файл з відповідями порожній або не знайдений\n";
        return 1;
    }

    int score = 0;
    const char letters[4] = { 'a', 'b', 'c', 'd' };

    for (size_t i = 0; i < questions.size(); ++i) {
        int num = static_cast<int>(i) + 1;
        cout << num << ". " << questions[i].text << "\n";
        for (int k = 0; k < 4; ++k) {
            cout << "  " << letters[k] << ") " << questions[i].options[k] << "\n";
        }
        cout << "Ваша відповідь: ";

        char input;
        cin >> input;
        Answer userAnswer = charToAnswer(input);

        if (correct.count(num) && userAnswer == correct[num]) {
            score++;
        }
    }

    cout << "==================================================\n";
    cout << "Результат: " << score << " з " << questions.size() << " (12-бальна система)\n";

    ofstream result("result.txt");
    if (result.is_open()) {
        result << "Результат тестування: " << score << " з " << questions.size() << "\n";
        result.close();
        cout << "Результат збережено у result.txt\n";
    }
    else {
        cerr << "Не вдалося зберегти результат у файл\n";
    }

    return 0;

};