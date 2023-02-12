#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
class clsLoginRegisterScreen : protected clsScreen
{
    static void PrintLoginRegisterRecord(clsUser::stLoginRegisterRecord User)
    {
        cout << "| " << setw(30) << left << User.DateTime;
        cout << "| " << setw(10) << left << User.UserName;
        cout << "| " << setw(10) << left << User.Password;
        cout << "| " << setw(10) << left << User.Permissions;
    }

public:
    static void ShowLoginRegisterScreen()
    {
        vector <clsUser::stLoginRegisterRecord> vLoginRegisterList = clsUser::GetLoginRegisterList();
        string SubTitle = "      (" + to_string(vLoginRegisterList.size()) + ") Record(s).";

        _DrawScreenHeader("LOGIN REGISTER LIST SCREEN", SubTitle);

        cout << "\n_______________________________________________________________________________________________________________________\n" << endl;
        cout << "| " << setw(30) << left << "Date / Time";
        cout << "| " << setw(10) << left << "Username";
        cout << "| " << setw(10) << left << "Password";
        cout << "| " << setw(10) << left << "Permission";
        cout << "\n_______________________________________________________________________________________________________________________\n" << endl;
        if (vLoginRegisterList.size() == 0) {
            cout << "\n\n There Are No Logins In The System!.\n";
        }
        else
        {
            for (clsUser::stLoginRegisterRecord& LoginRegister : vLoginRegisterList)
            {
                PrintLoginRegisterRecord(LoginRegister);
                cout << endl;
            }
            cout << "\n_______________________________________________________________________________________________________________________\n" << endl;
        }
    }
};