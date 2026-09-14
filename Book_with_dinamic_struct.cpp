#include <iostream>
#include <string>
#include <windows.h>
#include <format>

using namespace std;

struct Name
{
    string name;
    string second_name;
    string lastname;

    Name()
        : name(""), second_name(""), lastname("")
    {}

    Name(const string& fullName)
        : name(fullName), second_name(""), lastname("")
    {}

    Name(string name, string second_name, string lastname)
        : name(name), second_name(second_name), lastname(lastname)
    {}

    void show() const
    {
        cout << name << " "
            << second_name << " "
            << lastname << endl;
    }
};


class Entity
{
protected:
    Name name;

public:

    Entity()
        : name("No name")
    {}

    Entity(Name name)
        : name(name)
    {}

    virtual ~Entity() = default;

    virtual void SayName() const
    {
        cout << "Name: ";
        name.show();
    }
};


class Warrior : virtual public Entity
{
protected:
    int stamina;

public:

    Warrior()
        : Entity(), stamina(100)
    {}

    Warrior(Name name, int stamina)
        : Entity(name), stamina(stamina)
    {}

    virtual ~Warrior() = default;

    virtual void UseSword()
    {
        if (stamina >= 20)
        {
            cout << format(
                "{} uses sword! Stamina: {} -> {}",
                name.name,
                stamina,
                stamina - 20
            ) << endl;

            stamina -= 20;
        }
        else
        {
            cout << "Not enough stamina!" << endl;
        }
    }
};


class Mage : virtual public Entity
{
protected:
    int mana;

public:

    Mage()
        : Entity(), mana(100)
    {}

    Mage(Name name, int mana)
        : Entity(name), mana(mana)
    {}

    virtual ~Mage() = default;

    virtual void CastSpell()
    {
        if (mana >= 30)
        {
            cout << format(
                "{} casts a spell! Mana: {} -> {}",
                name.name,
                mana,
                mana - 30
            ) << endl;

            mana -= 30;
        }
        else
        {
            cout << "Not enough mana!" << endl;
        }
    }
};


class Spellblade : public Warrior, public Mage
{
public:

    Spellblade()
        : Entity(), Warrior(), Mage()
    {}

    Spellblade(Name name, int stamina, int mana)
        : Entity(name),
        Warrior(name, stamina),
        Mage(name, mana)
    {}

    ~Spellblade() override = default;


    void SayName() const override
    {
        cout << "Spellblade: ";
        name.show();
    }


    void UseSword() override
    {
        cout << "[Spellblade] ";
        Warrior::UseSword();
    }


    void CastSpell() override
    {
        cout << "[Spellblade] ";
        Mage::CastSpell();
    }
};



int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);


    Spellblade warriorMage1(
        Name("Arthur", "The", "Brave"),
        100,
        100
    );

    Spellblade warriorMage2(
        Name("Merlin", "The", "Great"),
        80,
        120
    );


    cout << "===== FIRST SPELLBLADE =====" << endl;

    warriorMage1.SayName();

    warriorMage1.UseSword();
    warriorMage1.CastSpell();


    cout << "\n===== SECOND SPELLBLADE =====" << endl;

    warriorMage2.SayName();

    warriorMage2.UseSword();
    warriorMage2.CastSpell();


    cout << "\n===== BATTLE =====" << endl;

    warriorMage1.UseSword();
    warriorMage2.CastSpell();

    warriorMage1.UseSword();
    warriorMage2.CastSpell();


    return 0;
}