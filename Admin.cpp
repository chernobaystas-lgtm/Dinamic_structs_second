#include "Admin.h"


bool Admin::AdminExists(const string& wantedLogin) const
{
    ifstream file("Admin.txt");

    if (!file.is_open())
        return false;

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string fileLogin;
        string surname;
        string password1;
        string password2;

        getline(ss, fileLogin, '|');
        getline(ss, surname, '|');
        getline(ss, password1, '|');
        getline(ss, password2, '|');

        if (fileLogin == wantedLogin)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}


bool Admin::RegisterAdmin()
{
    cout << "\n========== РЕГИСТРАЦИЯ АДМИНИСТРАТОРА ==========\n";

    string newLogin = ReadLine("Логин: ");

    if (AdminExists(newLogin))
    {
        cout << "Такой администратор уже существует.\n";
        return false;
    }

    string newSurname = ReadLine(
        "Фамилия (Enter, если нет): ",
        true
    );

    string password1 = ReadLine("Первый пароль: ");
    string password2 = ReadLine("Второй пароль: ");

    if (password1.empty() || password2.empty())
    {
        cout << "Пароли не могут быть пустыми.\n";
        return false;
    }

    if (password1 == password2)
    {
        cout << "Два пароля должны отличаться.\n";
        return false;
    }

    login = newLogin;
    second_name = newSurname;
    password = password1;
    secondPassword = password2;

    ofstream file("Admin.txt", ios::app);

    if (!file.is_open())
    {
        cout << "Не удалось открыть Admin.txt.\n";
        return false;
    }

    file << login << '|'
        << second_name << '|'
        << password << '|'
        << secondPassword
        << '\n';

    file.close();

    cout << "Администратор зарегистрирован.\n";

    return true;
}


bool Admin::LoadAdminRecord(
    const string& wantedLogin,
    const string& wantedSurname,
    const string& wantedPassword,
    const string& wantedSecondPassword
)
{
    ifstream file("Admin.txt");

    if (!file.is_open())
        return false;

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string fileLogin;
        string surname;
        string password1;
        string password2;

        getline(ss, fileLogin, '|');
        getline(ss, surname, '|');
        getline(ss, password1, '|');
        getline(ss, password2, '|');

        if (fileLogin == wantedLogin &&
            surname == wantedSurname &&
            password1 == wantedPassword &&
            password2 == wantedSecondPassword)
        {
            login = fileLogin;
            second_name = surname;
            password = password1;
            secondPassword = password2;

            file.close();
            return true;
        }
    }

    file.close();
    return false;
}


bool Admin::AuthenticateAdmin()
{
    cout << "\n========== АВТОРИЗАЦИЯ АДМИНИСТРАТОРА ==========\n";

    string wantedLogin = ReadLine("Логин: ");

    string wantedSurname = ReadLine(
        "Фамилия (Enter, если нет): ",
        true
    );

    string wantedPassword =
        ReadLine("Первый пароль: ");

    string wantedSecondPassword =
        ReadLine("Второй пароль: ");

    if (!LoadAdminRecord(
        wantedLogin,
        wantedSurname,
        wantedPassword,
        wantedSecondPassword))
    {
        cout << "Неверные данные администратора.\n";
        return false;
    }

    cout << "Авторизация администратора успешна.\n";

    return true;
}


void Admin::show() const
{
    cout << "\n========== АДМИНИСТРАТОР ==========\n";
    cout << "Логин: " << login << '\n';
    cout << "Фамилия: "
        << (second_name.empty() ? "-" : second_name)
        << '\n';
}


void Admin::AddQuestion()
{
    cout << "\n========== ДОБАВЛЕНИЕ ВОПРОСА ==========\n";

    int testNumber = ReadInt(
        "Для какого теста? "
        "(1 - пользователь, 2 - гость): ",
        1,
        2
    );

    string filename = TestFileByNumber(testNumber);

    map<int, Question> questions;

    LoadQuestions(filename, questions);

    int number = ReadInt(
        "Номер вопроса: ",
        1,
        1000000
    );

    if (questions.find(number) != questions.end())
    {
        cout << "Вопрос с таким номером уже существует.\n";
        return;
    }

    Question question;

    question.number = number;

    question.text = ReadLine("Вопрос: ");

    int answerCount = ReadInt(
        "Сколько ответов? (от 2): ",
        2,
        26
    );

    for (int i = 0; i < answerCount; i++)
    {
        string option = ReadLine(
            string(1, IndexToLetter(i)) +
            ") "
        );

        question.options.push_back(option);
    }

    question.correctAnswer =
        ReadAnswerLetter(answerCount);

    question.difficulty = ReadInt(
        "Сложность (1 - легкий, 2 - средний, 3 - сложный): ",
        1,
        3
    );

    questions[number] = question;

    SortQuestionNumbers(questions);

    cout << "\nВопрос добавлен в память.\n";

    ShowQuestion(question);

    if (AskSave())
    {
        if (SaveQuestions(filename, questions))
            cout << "Файл успешно сохранён.\n";
    }
    else
    {
        cout << "Изменения не сохранены.\n";
    }
}


void Admin::DeleteQuestion()
{
    cout << "\n========== УДАЛЕНИЕ ВОПРОСА ==========\n";

    int testNumber = ReadInt(
        "Какой тест? "
        "(1 - пользователь, 2 - гость): ",
        1,
        2
    );

    string filename = TestFileByNumber(testNumber);

    map<int, Question> questions;

    LoadQuestions(filename, questions);

    if (questions.empty())
    {
        cout << "Вопросов нет.\n";
        return;
    }

    int number = ReadInt(
        "Номер вопроса для удаления: ",
        1,
        1000000
    );

    auto it = questions.find(number);

    if (it == questions.end())
    {
        cout << "Вопрос не найден.\n";
        return;
    }

    ShowQuestion(it->second);

    string answer = ReadLine(
        "Удалить этот вопрос? (Y/N): "
    );

    if (answer.empty() ||
        ToUpperChar(answer[0]) != 'Y')
    {
        cout << "Удаление отменено.\n";
        return;
    }

    questions.erase(it);

    cout << "Вопрос удалён из памяти.\n";

    if (AskSave())
    {
        if (SaveQuestions(filename, questions))
            cout << "Файл успешно сохранён.\n";
    }
    else
    {
        cout << "Изменения не сохранены.\n";
    }
}


void Admin::EditQuestion()
{
    cout << "\n========== ИЗМЕНЕНИЕ ВОПРОСА ==========\n";

    int testNumber = ReadInt(
        "Какой тест? "
        "(1 - пользователь, 2 - гость): ",
        1,
        2
    );

    string filename = TestFileByNumber(testNumber);

    map<int, Question> questions;

    LoadQuestions(filename, questions);

    if (questions.empty())
    {
        cout << "Вопросов нет.\n";
        return;
    }

    int number = ReadInt(
        "Номер вопроса: ",
        1,
        1000000
    );

    auto it = questions.find(number);

    if (it == questions.end())
    {
        cout << "Вопрос не найден.\n";
        return;
    }

    cout << "\nСтарый вопрос:\n";
    ShowQuestion(it->second);

    Question& question = it->second;

    cout << "\n========== НОВЫЕ ДАННЫЕ ==========\n";

    question.text = ReadLine("Новый вопрос: ");

    int answerCount = ReadInt(
        "Сколько ответов? (от 2): ",
        2,
        26
    );

    question.options.clear();

    for (int i = 0; i < answerCount; i++)
    {
        string option = ReadLine(
            string(1, IndexToLetter(i)) +
            ") "
        );

        question.options.push_back(option);
    }

    question.correctAnswer =
        ReadAnswerLetter(answerCount);

    question.difficulty = ReadInt(
        "Сложность (1 - легкий, 2 - средний, 3 - сложный): ",
        1,
        3
    );

    cout << "\nИзменённый вопрос:\n";
    ShowQuestion(question);

    if (AskSave())
    {
        if (SaveQuestions(filename, questions))
            cout << "Файл успешно сохранён.\n";
    }
    else
    {
        cout << "Изменения не сохранены.\n";
    }
}


void Admin::ShowTestQuestions()
{
    cout << "\n========== ПРОСМОТР ТЕСТА ==========\n";

    int testNumber = ReadInt(
        "Какой тест? "
        "(1 - пользователь, 2 - гость): ",
        1,
        2
    );

    string filename = TestFileByNumber(testNumber);

    map<int, Question> questions;

    LoadQuestions(filename, questions);

    cout << "\n"
        << TestNameByNumber(testNumber)
        << "\n";

    ShowQuestions(questions);
}


void Admin::AdminTestMenu()
{
    while (true)
    {
        cout << "\n========================================\n";
        cout << "              ТЕСТЫ\n";
        cout << "========================================\n";

        cout << "1. Добавить вопрос\n";
        cout << "2. Удалить вопрос\n";
        cout << "3. Изменить вопрос\n";
        cout << "4. Посмотреть вопросы\n";
        cout << "0. Назад\n";

        int choice = ReadInt(
            "Выберите действие: ",
            0,
            4
        );

        switch (choice)
        {
        case 1:
            AddQuestion();
            break;

        case 2:
            DeleteQuestion();
            break;

        case 3:
            EditQuestion();
            break;

        case 4:
            ShowTestQuestions();
            break;

        case 0:
            return;
        }
    }
}


void Admin::ShowUsers()
{
    cout << "\n========== СПИСОК ПОЛЬЗОВАТЕЛЕЙ ==========\n";

    ifstream file("User.txt");

    if (!file.is_open())
    {
        cout << "Файл пользователей не найден.\n";
        return;
    }

    string line;
    int number = 1;

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

        cout << number++ << ". "
            << fileLogin;

        cout << " | Фамилия: "
            << (surname.empty() ? "-" : surname);

        cout << " | Статус: "
            << (banned == "true"
                ? "ЗАБАНЕН"
                : "Активен")
            << '\n';
    }

    file.close();
}


void Admin::BanUser()
{
    cout << "\n========== БАН ПОЛЬЗОВАТЕЛЯ ==========\n";

    string wantedLogin =
        ReadLine("Логин пользователя: ");

    ifstream in("User.txt");

    if (!in.is_open())
    {
        cout << "User.txt не найден.\n";
        return;
    }

    vector<string> lines;

    string line;
    bool found = false;

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

        if (fileLogin == wantedLogin)
        {
            found = true;

            line = "true|" +
                fileLogin + "|" +
                surname + "|" +
                filePassword;
        }

        lines.push_back(line);
    }

    in.close();

    if (!found)
    {
        cout << "Пользователь не найден.\n";
        return;
    }

    cout << "Пользователь будет заблокирован.\n";

    if (!AskSave())
    {
        cout << "Изменения не сохранены.\n";
        return;
    }

    ofstream out("User.txt");

    for (const string& currentLine : lines)
        out << currentLine << '\n';

    out.close();

    cout << "Пользователь заблокирован.\n";
}


void Admin::UnbanUser()
{
    cout << "\n========== РАЗБАН ПОЛЬЗОВАТЕЛЯ ==========\n";

    string wantedLogin =
        ReadLine("Логин пользователя: ");

    ifstream in("User.txt");

    if (!in.is_open())
    {
        cout << "User.txt не найден.\n";
        return;
    }

    vector<string> lines;

    string line;
    bool found = false;

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

        if (fileLogin == wantedLogin)
        {
            found = true;

            line = "false|" +
                fileLogin + "|" +
                surname + "|" +
                filePassword;
        }

        lines.push_back(line);
    }

    in.close();

    if (!found)
    {
        cout << "Пользователь не найден.\n";
        return;
    }

    if (!AskSave())
    {
        cout << "Изменения не сохранены.\n";
        return;
    }

    ofstream out("User.txt");

    for (const string& currentLine : lines)
        out << currentLine << '\n';

    out.close();

    cout << "Пользователь разблокирован.\n";
}


void Admin::ManageUsers()
{
    while (true)
    {
        cout << "\n========================================\n";
        cout << "         УПРАВЛЕНИЕ ПОЛЬЗОВАТЕЛЯМИ\n";
        cout << "========================================\n";

        cout << "1. Показать пользователей\n";
        cout << "2. Заблокировать пользователя\n";
        cout << "3. Разблокировать пользователя\n";
        cout << "0. Назад\n";

        int choice = ReadInt(
            "Выберите действие: ",
            0,
            3
        );

        switch (choice)
        {
        case 1:
            ShowUsers();
            break;

        case 2:
            BanUser();
            break;

        case 3:
            UnbanUser();
            break;

        case 0:
            return;
        }
    }
}


void Admin::AdminMenu()
{
    while (true)
    {
        cout << "\n========================================\n";
        cout << "          МЕНЮ АДМИНИСТРАТОРА\n";
        cout << "========================================\n";

        cout << "1. Управление тестами\n";
        cout << "2. Управление пользователями\n";
        cout << "3. Показать профиль\n";
        cout << "0. Выход\n";

        int choice = ReadInt(
            "Выберите действие: ",
            0,
            3
        );

        switch (choice)
        {
        case 1:
            AdminTestMenu();
            break;

        case 2:
            ManageUsers();
            break;

        case 3:
            show();
            break;

        case 0:
            return;
        }
    }
}