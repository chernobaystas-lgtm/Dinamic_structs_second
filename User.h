// User.h
#pragma once

#include "Common.h"


class User : public Base
{
private:
    vector<TestResult> results;

    bool LoadUserRecord(
        const string& wantedLogin,
        const string& wantedPassword
    );

    bool LoginExists(const string& wantedLogin) const;

    void SaveResults() const;

public:
    User() = default;

    User(
        const string& login,
        const string& second_name,
        const string& password
    )
        : Base(login, second_name, password)
    {}

    bool Register();

    bool Authenticate();

    void ShowProfile() const override;

    void EditProfile();

    void RunTest();

    void ShowResults() const;

    void UserMenu();

    bool IsAuthenticated() const
    {
        return !login.empty();
    }
};