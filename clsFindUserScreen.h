#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include "iomanip"
class clsFindUserScreen : protected clsScreen
{
	static void _PrintUser(clsUser User)
	{
		cout << "\n\n" << setw(37) << "" << "User Card:\n";
		cout << setw(37) << "" << "_____________________________";
		cout << "\n" << setw(37) << "" << "FirstName   : " << User.FirstName;
		cout << "\n" << setw(37) << "" << "LastName    : " << User.LastName;
		cout << "\n" << setw(37) << "" << "Full Name   : " << User.FullName();
		cout << "\n" << setw(37) << "" << "Email       : " << User.Email;
		cout << "\n" << setw(37) << "" << "Phone       : " << User.Phone;
		cout << "\n" << setw(37) << "" << "User Name   : " << User.UserName;
		cout << "\n" << setw(37) << "" << "Password    : " << User.Password;
		if (User.AccountStatus == clsUser::Blocked)
			cout << "\n" << setw(37) << "" << "Status      : Blocked";
		else
			cout << "\n" << setw(37) << "" << "Status      : Active";
		cout << "\n" << setw(37) << "" << "Permissions : " << User.Permissions;
		cout << "\n" << setw(37) << "" << "_____________________________\n";
	}

public:
	static void ShowFindUserScreen()
	{
		_DrawScreenHeader("  FIND USER SCREEN");

		string UserName;
		cout << "\n\n" << setw(37) << "" << "Please Enter UserName: ";
		UserName = clsInputValidate::ReadString();
		if (clsUser::IsUserExist(UserName))
		{
			cout << "\nUser is found :-) " << endl;
			clsUser User = clsUser::Find(UserName);
			_PrintUser(User);
			cout << "\n\n" << setw(37) << "" << "Do u want to change this USER's status? [Y/n] ";
			if (clsInputValidate::ReadYES_NO())
			{
				(User.AccountStatus == clsUser::Active) ? User.AccountStatus = clsUser::Blocked : User.AccountStatus = clsUser::Active;
				if (User.Save() == clsUser::svSucceeded) {
					cout << "\nDone succeccfully.\n";
				}
				else {
					cout << "\nFailed to update.\n";
				}
			}
		}
		else {
			cout << "\n" << "User With UserName [" << UserName << "] Doesn't exist\n";
		}
	}
};

