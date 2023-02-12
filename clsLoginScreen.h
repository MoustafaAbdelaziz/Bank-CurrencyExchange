#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
#include "Global.h"
class clsLoginScreen : protected clsScreen
{
    static void _Login()
    {
        string UserName = "", Password = "";
        bool LoginFailed = false;
        do
        {
            if (LoginFailed)
            {
                cout << "Invalid Username / Password!.\n";
            }
            cout << "\n\n" << setw(37) << "" << "Please Enter The Username: ";
            UserName = clsInputValidate::ReadString();
            cout << "\n" << setw(37) << "" << "Please Enter The Password: ";
            Password = clsInputValidate::ReadString();

            CurrentUser = clsUser::Find(UserName, Password);
            LoginFailed = CurrentUser.IsEmpty();
        } while (LoginFailed);
        clsMainScreen::ShowMainMenue();
    }

public:

    static void ShowLoginScreen() {
        system("cls");
        _DrawScreenHeader("  USER LOGIN SCREEN");
        _Login();
    }
};

