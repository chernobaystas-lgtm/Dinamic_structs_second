#include "Admin.h"


int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    while (true)
    {
        cout << "\n";
        cout << "========================================\n";
        cout << "              ВИКТОРИНА\n";
        cout << "========================================\n";

        cout << "Enter - Гость\n";
        cout << "1 - Пользователь\n";
        cout << "2 - Администратор\n";
        cout << "0 - Выход\n";

        cout << "\nВаш выбор: ";

        string choice;
        getline(cin, choice);

        if (choice.empty())
        {
            map<int, Question> guestQuestions;

            LoadQuestions(
                "Test2.txt",
                guestQuestions
            );

            if (guestQuestions.empty())
            {
                cout << "\nГостевой тест не найден.\n";
                continue;
            }

            cout << "\n========== ГОСТЕВОЙ ТЕСТ ==========\n";

            int difficulty = ReadInt(
                "Выберите уровень сложности "
                "(1 - легкий, 2 - средний, 3 - сложный, 4 - все): ",
                1,
                4
            );

            vector<Question> selected;

            for (const auto& [number, question] : guestQuestions)
            {
                if (difficulty == 4 ||
                    question.difficulty == difficulty)
                {
                    selected.push_back(question);
                }
            }

            if (selected.empty())
            {
                cout << "Вопросов на этом уровне нет.\n";
                continue;
            }

            int score = 0;

            for (const Question& question : selected)
            {
                ShowQuestion(question);

                char answer = ReadAnswerLetter(
                    static_cast<int>(
                        question.options.size()
                        )
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

            cout << "\n========================================\n";
            cout << "              РЕЗУЛЬТАТ\n";
            cout << "========================================\n";

            cout << "Правильных ответов: "
                << score
                << " из "
                << selected.size()
                << '\n';

            cout << "Результат: "
                << percent
                << "%\n";

            continue;
        }

        if (choice == "0")
        {
            break;
        }

        if (choice == "1")
        {
            while (true)
            {
                cout << "\n";
                cout << "========================================\n";
                cout << "       АВТОРИЗАЦИЯ ПОЛЬЗОВАТЕЛЯ\n";
                cout << "========================================\n";

                cout << "1. Авторизация\n";
                cout << "2. Регистрация\n";
                cout << "0. Назад\n";

                int userChoice = ReadInt(
                    "Выберите действие: ",
                    0,
                    2
                );

                if (userChoice == 0)
                    break;

                User user;

                if (userChoice == 2)
                {
                    if (user.Register())
                        user.UserMenu();

                    continue;
                }

                if (userChoice == 1)
                {
                    if (user.Authenticate())
                        user.UserMenu();
                }
            }

            continue;
        }

        if (choice == "2")
        {
            while (true)
            {
                cout << "\n";
                cout << "========================================\n";
                cout << "       АВТОРИЗАЦИЯ АДМИНИСТРАТОРА\n";
                cout << "========================================\n";

                cout << "1. Авторизация\n";
                cout << "2. Регистрация администратора\n";
                cout << "0. Назад\n";

                int adminChoice = ReadInt(
                    "Выберите действие: ",
                    0,
                    2
                );

                if (adminChoice == 0)
                    break;

                Admin admin;

                if (adminChoice == 2)
                {
                    if (admin.RegisterAdmin())
                        admin.AdminMenu();

                    continue;
                }

                if (adminChoice == 1)
                {
                    if (admin.AuthenticateAdmin())
                        admin.AdminMenu();
                }
            }

            continue;
        }

        cout << "Неверный выбор.\n";
    }

    return 0;
}