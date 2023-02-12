#pragma once
#include "clsScreen.h"
#include <iomanip>
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
class clsManageUsers : protected clsScreen
{
	enum enManageUsersOptions { enShowUsersList = 1, enAddUser, enDeleteUser, UpdateUser, enFindUser, enMainMenue };

	static enManageUsersOptions _ReadManageUserOptions()
	{
		cout << "\n" << setw(36)<< "" << "Choose What You Want To Do [1:6] ";
		return (enManageUsersOptions)clsInputValidate::ReadNumberBetween<short>(1, 6);
	}

	static void _BackToTheManageUsersScreen()
	{
		cout << "\n" << setw(37) << "" << "Press Any Key To Show The Manage Users Screen...";
		system("pause>0");
		ShowManageUsersMenue();
	}

    static void _ShowUsersListScreen()
    {
        //cout << "Show User List Screen Will be here\n";
        clsUsersListScreen::ShowUsersList();
    }

    static void _AddNewUserScreen()
    {
        //cout << "Show Add new User Screen Will be here\n";
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    static void _ShowDeleteUserScreen()
    {
        //cout << "Show Delete User Screen Will be here\n";
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void  _UpdateUserScreen()
    {
        //cout << "Show Update User Screen Will be here\n";
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _FindUserScreen()
    {
        //cout << "Show Find User Screen Will be here\n";
        clsFindUserScreen::ShowFindUserScreen();
    }

    static void _PerformManageUsersScreenOptions(enManageUsersOptions ManageUserOptions)
    {
        switch (ManageUserOptions)
        {
        case enManageUsersOptions::enShowUsersList:
            system("cls");
            _ShowUsersListScreen();
            _BackToTheManageUsersScreen();
            break;
        case enManageUsersOptions::enAddUser:
            system("cls");
            _AddNewUserScreen();
            _BackToTheManageUsersScreen();
            break;
        case enManageUsersOptions::enDeleteUser:
            system("cls");
            _ShowDeleteUserScreen();
            _BackToTheManageUsersScreen();
            break;
        case enManageUsersOptions::UpdateUser:
            system("cls");
            _UpdateUserScreen();
            _BackToTheManageUsersScreen();
            break;
        case enManageUsersOptions::enFindUser:
            system("cls");
            _FindUserScreen();
            _BackToTheManageUsersScreen();
            break;
        case enManageUsersOptions::enMainMenue:
            break;
        }
    }

public:

    static void ShowManageUsersMenue()
    {
        system("cls");
        _DrawScreenHeader("   MANAGE USERS SCREEN");
        cout << "\n\n" << setw(28) << "" << "______________________________________________________";
        cout << "\n\n" << setw(37) << right << "|" << setw(26) << "MANAGE USERS MENUE" << setw(9) << right << "|";
        cout << "\n" << setw(28) << "" << "______________________________________________________\n";
        cout << "\n" << setw(37) << "|" << setw(28) << "[1] Show Users List." << setw(7) << right << "|";
        cout << "\n" << setw(37) << "|" << setw(26) << "[2] Add New Users." << setw(9) << right << "|";
        cout << "\n" << setw(37) << "|" << setw(24) << "[3] Delete User." << setw(11) << right << "|";
        cout << "\n" << setw(37) << "|" << setw(24) << "[4] Update User." << setw(11) << right << "|";
        cout << "\n" << setw(37) << "|" << setw(22) << "[5] Find User." << setw(13) << right << "|";
        cout << "\n" << setw(37) << "|" << setw(23) << "[6] Main Menue." << setw(12) << right << "|";
        cout << "\n" << setw(28) << "" << "______________________________________________________";
        _PerformManageUsersScreenOptions(_ReadManageUserOptions());
    }

};

