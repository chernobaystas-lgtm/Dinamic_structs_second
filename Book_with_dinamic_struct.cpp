#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <cctype>
#include <windows.h>

using namespace std;


enum class Answer
{
    A,
    B,
    C,
    D,
    NONE
};


struct Question
{
    string text;          
    string options[4];   
    char correctAnswer;   
};

Answer charToAnswer(char c)
{
    c = toupper(c);

    if (c == 'A')
        return Answer::A;

    if (c == 'B')
        return Answer::B;

    if (c == 'C')
        return Answer::C;

    if (c == 'D')
        return Answer::D;

    return Answer::NONE;
}


void LoadQuestions(map<int, Question>& questions)
{
    ifstream file("For_maps2.txt");

    if (!file.is_open())
    {
        cout << "Oshibka: ne udalos otkryt For_maps2.txt!\n";
        return;
    }

    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        if (line.size() >= 3 &&
            (unsigned char)line[0] == 0xEF &&
            (unsigned char)line[1] == 0xBB &&
            (unsigned char)line[2] == 0xBF)
        {
            line.erase(0, 3);
        }

        stringstream ss(line);

        string numberText;
        string correctText;

        Question question{};

        getline(ss, numberText, '|');

        getline(ss, question.text, '|');

        for (int i = 0; i < 4; i++)
        {
            getline(ss, question.options[i], '|');
        }

        getline(ss, correctText, '|');

        int number = stoi(numberText);

        question.correctAnswer = toupper(correctText[0]);

        questions[number] = question;
    }

    file.close();
}


int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    map<int, Question> questions;

    LoadQuestions(questions);

    if (questions.empty())
    {
        cout << "Voprosy ne zagruzheny.\n";
        cout << "Proverte For_maps2.txt.\n";
        system("pause");
        return 0;
    }


    cout << "====================================\n";
    cout << "          VIKTORINA\n";
    cout << "====================================\n";

    cout << "Kolichestvo voprosov: "
        << questions.size() << "\n";


    int score = 0;


    for (const auto& item : questions)
    {
        int number = item.first;

        const Question& question = item.second;


        cout << "\n";
        cout << "------------------------------------\n";

        cout << number << ". "
            << question.text << "\n\n";


        cout << "A) " << question.options[0] << "\n";
        cout << "B) " << question.options[1] << "\n";
        cout << "C) " << question.options[2] << "\n";
        cout << "D) " << question.options[3] << "\n";


        char answer;

        while (true)
        {
            cout << "\nVash otvet: ";
            cin >> answer;

            answer = toupper(answer);


            if (answer == 'A' ||
                answer == 'B' ||
                answer == 'C' ||
                answer == 'D')
            {
                break;
            }

            cout << "Oshibka! Vvedite tolko A, B, C ili D.\n";
        }

        
        if (answer == question.correctAnswer)
        {
            cout << "Pravilno!\n";
            score++;
        }
        else
        {
            cout << "Nepravilno!\n";
        }
    }


    cout << "\n====================================\n";
    cout << "             REZULTAT\n";
    cout << "====================================\n";

    cout << "Pravilnyh otvetov: "
        << score << " iz "
        << questions.size() << "\n";


    double percent =
        static_cast<double>(score) /
        questions.size() * 100.0;

    cout << "Rezultat: "
        << percent << "%\n";


    system("pause");

    return 0;
}