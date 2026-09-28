// Common.h
#pragma once

#define NOMINMAX
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


enum class Answer
{
    NONE
};


struct Question
{
    int number{};
    string text;
    vector<string> options;
    char correctAnswer{};
    int difficulty{ 1 };
};


struct TestResult
{
    string testName;
    int correct{};
    int total{};
    double percent{};
    int difficulty{};
};


inline char ToUpperChar(char c)
{
    return static_cast<char>(
        toupper(static_cast<unsigned char>(c))
        );
}


inline char IndexToLetter(size_t index)
{
    return static_cast<char>('A' + index);
}


inline int LetterToIndex(char letter)
{
    letter = ToUpperChar(letter);

    if (letter < 'A' || letter > 'Z')
        return -1;

    return letter - 'A';
}


inline bool IsCorrectAnswer(char answer, const Question& question)
{
    return ToUpperChar(answer) == ToUpperChar(question.correctAnswer);
}


inline string GetDifficultyName(int difficulty)
{
    switch (difficulty)
    {
    case 1:
        return "Легкий";
    case 2:
        return "Средний";
    case 3:
        return "Сложный";
    default:
        return "Неизвестно";
    }
}


inline int ReadInt(const string& message, int minValue, int maxValue)
{
    int value;

    while (true)
    {
        cout << message;

        if (cin >> value && value >= minValue && value <= maxValue)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Ошибка! Введите число от "
            << minValue << " до "
            << maxValue << ".\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


inline string ReadLine(const string& message, bool allowEmpty = false)
{
    string value;

    while (true)
    {
        cout << message;
        getline(cin, value);

        if (allowEmpty || !value.empty())
            return value;

        cout << "Поле не может быть пустым.\n";
    }
}


inline char ReadAnswerLetter(int optionCount)
{
    while (true)
    {
        string input = ReadLine("Правильный ответ: ");

        if (input.size() == 1)
        {
            char answer = ToUpperChar(input[0]);

            if (answer >= 'A' &&
                answer < static_cast<char>('A' + optionCount))
            {
                return answer;
            }
        }

        cout << "Ошибка! Введите букву от A до "
            << static_cast<char>('A' + optionCount - 1)
            << ".\n";
    }
}


inline bool AskSave()
{
    while (true)
    {
        string answer = ReadLine(
            "Точно хотите сохранить изменения в файл? (Y/N): "
        );

        if (answer.size() == 1)
        {
            char c = ToUpperChar(answer[0]);

            if (c == 'Y' || c == 'Д')
                return true;

            if (c == 'N' || c == 'Н')
                return false;
        }

        cout << "Введите Y или N.\n";
    }
}


inline string TestFileByNumber(int testNumber)
{
    if (testNumber == 1)
        return "For_maps2.txt";

    return "Test2.txt";
}


inline string TestNameByNumber(int testNumber)
{
    if (testNumber == 1)
        return "Пользовательский тест";

    return "Гостевой тест";
}


inline void LoadQuestions(
    const string& filename,
    map<int, Question>& questions
)
{
    questions.clear();

    ifstream file(filename);

    if (!file.is_open())
        return;

    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        if (line.size() >= 3 &&
            static_cast<unsigned char>(line[0]) == 0xEF &&
            static_cast<unsigned char>(line[1]) == 0xBB &&
            static_cast<unsigned char>(line[2]) == 0xBF)
        {
            line.erase(0, 3);
        }

        stringstream ss(line);

        string numberText;
        string text;
        string correctText;
        string difficultyText;

        Question question;

        getline(ss, numberText, '|');
        getline(ss, question.text, '|');

        if (numberText.empty() || question.text.empty())
            continue;

        try
        {
            question.number = stoi(numberText);
        }
        catch (...)
        {
            continue;
        }

        vector<string> parts;
        string part;

        while (getline(ss, part, '|'))
            parts.push_back(part);

        if (parts.size() < 3)
            continue;

        correctText = parts[parts.size() - 1];

        bool hasDifficulty = false;

        if (parts.size() >= 4 &&
            parts[parts.size() - 2].size() == 1 &&
            parts[parts.size() - 2][0] >= '1' &&
            parts[parts.size() - 2][0] <= '3')
        {
            hasDifficulty = true;
            difficultyText = parts[parts.size() - 2];
        }

        size_t optionEnd = parts.size() - 1;

        if (hasDifficulty)
            optionEnd--;

        for (size_t i = 0; i < optionEnd; i++)
            question.options.push_back(parts[i]);

        if (question.options.size() < 2)
            continue;

        if (correctText.empty())
            continue;

        question.correctAnswer = ToUpperChar(correctText[0]);

        question.difficulty = 1;

        if (hasDifficulty)
            question.difficulty = difficultyText[0] - '0';

        int correctIndex =
            LetterToIndex(question.correctAnswer);

        if (correctIndex < 0 ||
            correctIndex >= static_cast<int>(question.options.size()))
        {
            continue;
        }

        questions[question.number] = question;
    }

    file.close();
}


inline bool SaveQuestions(
    const string& filename,
    const map<int, Question>& questions
)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        cout << "Не удалось открыть файл для сохранения.\n";
        return false;
    }

    for (const auto& [number, question] : questions)
    {
        file << number << '|'
            << question.text << '|';

        for (const string& option : question.options)
            file << option << '|';

        file << question.correctAnswer << '|'
            << question.difficulty << '\n';
    }

    file.close();
    return true;
}


inline void ShowQuestion(const Question& question)
{
    cout << "\n----------------------------------------\n";
    cout << question.number << ". "
        << question.text << "\n";

    for (size_t i = 0; i < question.options.size(); i++)
    {
        cout << IndexToLetter(i)
            << ") "
            << question.options[i]
            << '\n';
    }

    cout << "Сложность: "
        << GetDifficultyName(question.difficulty)
        << '\n';

    cout << "----------------------------------------\n";
}


inline void ShowQuestions(
    const map<int, Question>& questions
)
{
    if (questions.empty())
    {
        cout << "Вопросов нет.\n";
        return;
    }

    for (const auto& [number, question] : questions)
        ShowQuestion(question);
}


inline void SortQuestionNumbers(
    map<int, Question>& questions
)
{
    map<int, Question> sorted;

    for (const auto& [number, question] : questions)
        sorted[number] = question;

    questions = sorted;
}


class Base
{
protected:
    string login;
    string second_name;
    string password;

public:
    Base() = default;

    Base(
        const string& login,
        const string& second_name,
        const string& password
    )
        : login(login),
        second_name(second_name),
        password(password)
    {}

    virtual ~Base() = default;

    virtual void show() const
    {
        cout << "\n========== ПРОФИЛЬ ==========\n";
        cout << "Логин: " << login << '\n';
        cout << "Фамилия: "
            << (second_name.empty() ? "-" : second_name)
            << '\n';
    }

    const string& getLogin() const
    {
        return login;
    }

    const string& getSecondName() const
    {
        return second_name;
    }

    const string& getPassword() const
    {
        return password;
    }

    void setLogin(const string& value)
    {
        login = value;
    }

    void setSecondName(const string& value)
    {
        second_name = value;
    }

    void setPassword(const string& value)
    {
        password = value;
    }

    void inputLogin()
    {
        login = ReadLine("Логин: ");
    }

    void inputSecondName()
    {
        second_name = ReadLine(
            "Фамилия (Enter, если нет): ",
            true
        );
    }

    void inputPassword()
    {
        password = ReadLine("Пароль: ");
    }

    virtual bool saveToFile(const string& filename) const
    {
        ofstream file(filename, ios::app);

        if (!file.is_open())
            return false;

        file << "false|"
            << login << '|'
            << second_name << '|'
            << password
            << '\n';

        file.close();
        return true;
    }
};