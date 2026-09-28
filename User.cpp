// User.cpp
#include "User.h"


bool User::LoginExists(const string& wantedLogin) const
{
    ifstream file("User.txt");

    if (!file.is_open())
        return false;

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string banned;
        string fileLogin;
        string surname;
        string filePassword;

        getline(ss, banned, '|');
        getline(ss, fileLogin, '|');
        getline(ss, surname, '|');
        getline(ss, filePassword, '|');

        if (fileLogin == wantedLogin)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}


bool User::Register()
{
    cout << "\n========== РЕГИСТРАЦИЯ ==========\n";

    string newLogin = ReadLine("Логин: ");

    if (LoginExists(newLogin))
    {
        cout << "Такой логин уже существует.\n";
        return false;
    }

    string newSurname = ReadLine(
        "Фамилия (Enter, если нет): ",
        true
    );

    string newPassword = ReadLine("Пароль: ");

    if (newPassword.empty())
    {
        cout << "Пароль не может быть пустым.\n";
        return false;
    }

    login = newLogin;
    second_name = newSurname;
    password = newPassword;

    ofstream file("User.txt", ios::app);

    if (!file.is_open())
    {
        cout << "Не удалось открыть User.txt.\n";
        return false;
    }

    file << "false|"
        << login << '|'
        << second_name << '|'
        << password
        << '\n';

    file.close();

    cout << "Регистрация успешно завершена.\n";

    return true;
}


bool User::LoadUserRecord(
    const string& wantedLogin,
    const string& wantedPassword
)
{
    ifstream file("User.txt");

    if (!file.is_open())
        return false;

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string banned;
        string fileLogin;
        string surname;
        string filePassword;

        getline(ss, banned, '|');
        getline(ss, fileLogin, '|');
        getline(ss, surname, '|');
        getline(ss, filePassword, '|');

        if (fileLogin == wantedLogin &&
            filePassword == wantedPassword)
        {
            if (banned == "true")
            {
                cout << "Этот пользователь заблокирован.\n";
                file.close();
                return false;
            }

            login = fileLogin;
            second_name = surname;
            password = filePassword;

            file.close();
            return true;
        }
    }

    file.close();
    return false;
}


bool User::Authenticate()
{
    cout << "\n========== АВТОРИЗАЦИЯ ==========\n";

    string wantedLogin = ReadLine("Логин: ");
    string wantedPassword = ReadLine("Пароль: ");

    if (!LoadUserRecord(wantedLogin, wantedPassword))
    {
        cout << "Неверный логин или пароль.\n";
        return false;
    }

    cout << "Авторизация успешна.\n";

    return true;
}


void User::ShowProfile() const
{
    Base::show();

    cout << "Количество результатов: "
        << results.size()
        << '\n';
}


void User::EditProfile()
{
    while (true)
    {
        cout << "\n========== ИЗМЕНЕНИЕ ПРОФИЛЯ ==========\n";
        cout << "1. Изменить логин\n";
        cout << "2. Изменить фамилию\n";
        cout << "3. Изменить пароль\n";
        cout << "0. Назад\n";

        int choice = ReadInt("Выберите действие: ", 0, 3);

        if (choice == 0)
            return;

        if (choice == 1)
        {
            string newLogin = ReadLine("Новый логин: ");

            if (newLogin.empty())
                continue;

            if (newLogin != login &&
                LoginExists(newLogin))
            {
                cout << "Такой логин уже существует.\n";
                continue;
            }

            string oldLogin = login;
            login = newLogin;

            ifstream in("User.txt");
            vector<string> lines;

            string line;

            while (getline(in, line))
            {
                stringstream ss(line);

                string banned;
                string fileLogin;
                string surname;
                string filePassword;

                getline(ss, banned, '|');
                getline(ss, fileLogin, '|');
                getline(ss, surname, '|');
                getline(ss, filePassword, '|');

                if (fileLogin == oldLogin)
                {
                    line = banned + "|" +
                        login + "|" +
                        surname + "|" +
                        filePassword;
                }

                lines.push_back(line);
            }

            in.close();

            ofstream out("User.txt");

            for (const string& currentLine : lines)
                out << currentLine << '\n';

            out.close();

            cout << "Логин изменён.\n";
        }

        else if (choice == 2)
        {
            string newSurname = ReadLine(
                "Новая фамилия (Enter, если убрать): ",
                true
            );

            ifstream in("User.txt");
            vector<string> lines;

            string line;

            while (getline(in, line))
            {
                stringstream ss(line);

                string banned;
                string fileLogin;
                string surname;
                string filePassword;

                getline(ss, banned, '|');
                getline(ss, fileLogin, '|');
                getline(ss, surname, '|');
                getline(ss, filePassword, '|');

                if (fileLogin == login)
                {
                    line = banned + "|" +
                        fileLogin + "|" +
                        newSurname + "|" +
                        filePassword;

                    second_name = newSurname;
                }

                lines.push_back(line);
            }

            in.close();

            ofstream out("User.txt");

            for (const string& currentLine : lines)
                out << currentLine << '\n';

            out.close();

            cout << "Фамилия изменена.\n";
        }

        else if (choice == 3)
        {
            string newPassword = ReadLine("Новый пароль: ");

            if (newPassword.empty())
                continue;

            ifstream in("User.txt");
            vector<string> lines;

            string line;

            while (getline(in, line))
            {
                stringstream ss(line);

                string banned;
                string fileLogin;
                string surname;
                string filePassword;

                getline(ss, banned, '|');
                getline(ss, fileLogin, '|');
                getline(ss, surname, '|');
                getline(ss, filePassword, '|');

                if (fileLogin == login)
                {
                    line = banned + "|" +
                        fileLogin + "|" +
                        surname + "|" +
                        newPassword;

                    password = newPassword;
                }

                lines.push_back(line);
            }

            in.close();

            ofstream out("User.txt");

            for (const string& currentLine : lines)
                out << currentLine << '\n';

            out.close();

            cout << "Пароль изменён.\n";
        }
    }
}


void User::SaveResults() const
{
    if (login.empty())
        return;

    ifstream in("Results.txt");
    vector<string> lines;

    if (in.is_open())
    {
        string line;

        while (getline(in, line))
            lines.push_back(line);

        in.close();
    }

    ofstream out("Results.txt");

    for (const string& line : lines)
        out << line << '\n';

    for (const TestResult& result : results)
    {
        out << login << '|'
            << result.testName << '|'
            << result.correct << '|'
            << result.total << '|'
            << result.percent << '|'
            << result.difficulty
            << '\n';
    }

    out.close();
}


void User::RunTest()
{
    map<int, Question> questions;

    LoadQuestions("For_maps2.txt", questions);

    if (questions.empty())
    {
        cout << "Пользовательский тест не найден.\n";
        return;
    }

    cout << "\n========== ПОЛЬЗОВАТЕЛЬСКИЙ ТЕСТ ==========\n";

    cout << "Выберите уровень сложности:\n";
    cout << "1. Легкий\n";
    cout << "2. Средний\n";
    cout << "3. Сложный\n";
    cout << "4. Все уровни\n";

    int difficulty = ReadInt(
        "Ваш выбор: ",
        1,
        4
    );

    vector<Question> selected;

    for (const auto& [number, question] : questions)
    {
        if (difficulty == 4 ||
            question.difficulty == difficulty)
        {
            selected.push_back(question);
        }
    }

    if (selected.empty())
    {
        cout << "На этом уровне вопросов нет.\n";
        return;
    }

    int score = 0;

    for (const Question& question : selected)
    {
        ShowQuestion(question);

        char answer = ReadAnswerLetter(
            static_cast<int>(question.options.size())
        );

        if (IsCorrectAnswer(answer, question))
        {
            cout << "Правильно!\n";
            score++;
        }
        else
        {
            cout << "Неправильно!\n";
            cout << "Правильный ответ: "
                << question.correctAnswer
                << '\n';
        }
    }

    double percent =
        static_cast<double>(score) /
        selected.size() * 100.0;

    cout << "\n========== РЕЗУЛЬТАТ ==========\n";
    cout << "Пользователь: " << login << '\n';
    cout << "Правильных ответов: "
        << score << " из "
        << selected.size() << '\n';

    cout << "Результат: "
        << percent
        << "%\n";

    TestResult result;

    result.testName = "Пользовательский тест";
    result.correct = score;
    result.total = static_cast<int>(selected.size());
    result.percent = percent;
    result.difficulty = difficulty;

    results.push_back(result);

    SaveResults();

    cout << "Результат сохранён.\n";
}


void User::ShowResults() const
{
    cout << "\n========== МОИ РЕЗУЛЬТАТЫ ==========\n";

    if (results.empty())
    {
        cout << "Результатов пока нет.\n";
        return;
    }

    for (size_t i = 0; i < results.size(); i++)
    {
        const TestResult& result = results[i];

        cout << "\n"
            << i + 1
            << ". "
            << result.testName
            << '\n';

        cout << "Правильных ответов: "
            << result.correct
            << " из "
            << result.total
            << '\n';

        cout << "Результат: "
            << result.percent
            << "%\n";

        cout << "Уровень: "
            << GetDifficultyName(result.difficulty)
            << '\n';
    }
}


void User::UserMenu()
{
    while (true)
    {
        cout << "\n========================================\n";
        cout << "          МЕНЮ ПОЛЬЗОВАТЕЛЯ\n";
        cout << "========================================\n";

        cout << "1. Посмотреть профиль\n";
        cout << "2. Изменить профиль\n";
        cout << "3. Пройти тест\n";
        cout << "4. Посмотреть результаты\n";
        cout << "0. Выход\n";

        int choice = ReadInt(
            "Выберите действие: ",
            0,
            4
        );

        switch (choice)
        {
        case 1:
            ShowProfile();
            break;

        case 2:
            EditProfile();
            break;

        case 3:
            RunTest();
            break;

        case 4:
            ShowResults();
            break;

        case 0:
            return;
        }
    }
}