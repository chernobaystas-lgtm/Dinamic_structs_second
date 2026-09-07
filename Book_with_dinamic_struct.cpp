#include <iostream>
#include <string>
#include <windows.h>

using namespace std;


class Player
{
private:
    string surname;
    int game_number{ 0 };
    double rating{ 0.0 };

public:

    Player()
        : surname("No surname"), game_number(0), rating(0.0)
    {
        cout << "[Player] Default constructor: "
            << surname << endl;
    }

    Player(string surname, int number, double rating)
        : surname(surname),
        game_number(number),
        rating(rating)
    {
        cout << "[Player] Constructor: "
            << this->surname << endl;
    }

    ~Player()
    {
        cout << "[Player] Destructor: "
            << surname << endl;
    }

    void show_player() const
    {
        cout << "Surname: " << surname << endl;
        cout << "Game number: " << game_number << endl;
        cout << "Rating: " << rating << endl;
    }


    // Getters

    string get_surname() const
    {
        return surname;
    }

    int get_game_number() const
    {
        return game_number;
    }

    double get_rating() const
    {
        return rating;
    }


    // Setters

    void set_surname(string new_surname)
    {
        surname = new_surname;
    }

    void set_game_number(int new_number)
    {
        game_number = new_number;
    }

    void set_rating(double new_rating)
    {
        rating = new_rating;
    }
};


class Team
{
private:
    string club_name;
    Player** players{ nullptr };
    int player_count{ 0 };

public:

    Team()
        : club_name("No club"),
        players(nullptr),
        player_count(0)
    {
        cout << "[Team] Default constructor: "
            << club_name << endl;
    }

    Team(string name)
        : club_name(name),
        players(nullptr),
        player_count(0)
    {
        cout << "[Team] Constructor: "
            << club_name << endl;
    }


    void add_player(Player* player)
    {
        Player** temp = new Player * [player_count + 1];

        for (int i = 0; i < player_count; i++)
        {
            temp[i] = players[i];
        }

        temp[player_count] = player;

        delete[] players;

        players = temp;
        player_count++;
    }


    void show_team() const
    {
        cout << "\n===== TEAM =====" << endl;
        cout << "Club name: " << club_name << endl;
        cout << "Number of players: " << player_count << endl;

        for (int i = 0; i < player_count; i++)
        {
            cout << "\n--- Player " << i + 1 << " ---" << endl;
            players[i]->show_player();
        }
    }


    ~Team()
    {
        cout << "[Team] Destructor: "
            << club_name << endl;

        // ВАЖНО:
        // игроков здесь НЕ удаляем,
        // потому что Team ими не владеет.

        delete[] players;
    }


    // Getter

    string get_club_name() const
    {
        return club_name;
    }


    // Setter

    void set_club_name(string new_name)
    {
        club_name = new_name;
    }
};


int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Player player1("Messi", 10, 9.8);
    Player player2("Ronaldo", 7, 9.7);
    Player player3("Mbappe", 9, 9.5);

    {
        Team team("Dream Team");

        team.add_player(&player1);
        team.add_player(&player2);
        team.add_player(&player3);

        team.show_team();

        cout << "\n===== TEAM IS DESTROYED =====" << endl;
    }

    cout << "\n===== PLAYERS STILL EXIST =====" << endl;

    player1.show_player();
    cout << endl;

    player2.show_player();
    cout << endl;

    player3.show_player();
    cout << endl;

    return 0;
}