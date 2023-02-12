#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include "iomanip"
class clsDeleteUserScreen : protected clsScreen
{
    static void _PrintUser(clsUser User)
    {
        cout << "\n" << "\n\n" << setw(37) << "" << "User Card:\n";
        cout << setw(37) << "" << "___________________";
        cout << "\n" << setw(37) << "" << "FirstName   : " << User.FirstName;
        cout << "\n" << setw(37) << "" << "LastName    : " << User.LastName;
        cout << "\n" << setw(37) << "" << "Full Name   : " << User.FullName();
        cout << "\n" << setw(37) << "" << "Email       : " << User.Email;
        cout << "\n" << setw(37) << "" << "Phone       : " << User.Phone;
        cout << "\n" << setw(37) << "" << "User Name   : " << User.UserName;
        cout << "\n" << setw(37) << "" << "Password    : " << User.Password;
        cout << "\n" << setw(37) << "" << "Permissions : " << User.Permissions;
        cout << "\n" << setw(37) << "" << "___________________\n";
    }

public:

    static void ShowDeleteUserScreen()
    {
        _DrawScreenHeader("  DELETE USER SCREEN");

        string UserName;
        cout << "\n\n" << setw(37) << "" << "Please Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        if (clsUser::IsUserExist(UserName))
        {
            clsUser User = clsUser::Find(UserName);
            _PrintUser(User);

            cout << "\n" << setw(37) << "" << "Are you sure that you wanna DELETE this User? [Y/n]. ";
            if (clsInputValidate::ReadYES_NO())
            {
                if (User.Delete()) {
                    cout << "\nCompeleted successfully.";
                }
                else {
                    cout << "\nERROR, User Was not Deleted\n";
                }
            }
        }
        else {
            cout << "\n" << setw(37) << "" << "User With UserName [" << UserName << "] Doesn't exist\n";
        }
    }
};

