// Admin.h
#pragma once

#include "User.h"


class Admin : public User
{
private:
    string secondPassword;

    bool LoadAdminRecord(
        const string& wantedLogin,
        const string& wantedSurname,
        const string& wantedPassword,
        const string& wantedSecondPassword
    );

    bool AdminExists(const string& wantedLogin) const;

    void AddQuestion();

    void DeleteQuestion();

    void EditQuestion();

    void ShowTestQuestions();

    void ManageUsers();

    void ShowUsers();

    void BanUser();

    void UnbanUser();

    void AdminTestMenu();

public:
    Admin() = default;

    bool RegisterAdmin();

    bool AuthenticateAdmin();

    void AdminMenu();

    void show() const override;
};