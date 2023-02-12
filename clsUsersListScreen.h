#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
class clsUsersListScreen : protected clsScreen
{
    static void PrintUserRecord(clsUser User)
    {
        cout << "| " << setw(12) << left << User.UserName;
        cout << "| " << setw(25) << left << User.FullName();
        cout << "| " << setw(15) << left << User.Phone;
        cout << "| " << setw(20) << left << User.Email;
        cout << "| " << setw(10) << left << User.Password;
        cout << "| " << setw(12) << left << User.Permissions;
        if (User.AccountStatus == clsUser::Blocked)
            cout << "| " << setw(10) << left << "Blocked";
        else
            cout << "| " << setw(10) << left << "Active";
    }
public:
   static void ShowUsersList()
    {
        vector <clsUser> vUsers = clsUser::GetAllUsers();
        string SubTitle = "     (" + to_string(vUsers.size()) + ") User(s).";

        _DrawScreenHeader("   USER LIST SCREEN", SubTitle);

        cout << "\n_______________________________________________________________________________________________________________________\n" << endl;
        cout << "| " << setw(12) << left << "UserName";
        cout << "| " << setw(25) << left << "Full Name";
        cout << "| " << setw(15) << left << "Phone";
        cout << "| " << setw(20) << left << "Email";
        cout << "| " << setw(10) << left << "Password";
        cout << "| " << setw(12) << left << "Permission";
        cout << "| " << setw(10) << left << "Status";
        cout << "\n_______________________________________________________________________________________________________________________\n" << endl;
        if (vUsers.size() == 0){
            cout << "\n\n There Are No Users In The System!.\n";
        }
        else
        {
            for (clsUser& User : vUsers)
            {
                PrintUserRecord(User);
                cout << endl;
            }
            cout << "\n_______________________________________________________________________________________________________________________\n" << endl;
        }
    }
};

