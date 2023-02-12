#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include "iomanip"
class clsAddNewUserScreen : protected clsScreen
{
	static clsUser _ReadUserInfo(clsUser& User)
	{
		cout << "\n" << setw(37) << "" << "Enter First Name: ";
		User.FirstName = clsInputValidate::ReadString();

		cout << setw(37) << "" << "Enter Last Name : ";
		User.LastName = clsInputValidate::ReadString();

		cout << setw(37) << "" << "Enter Email     : ";
		User.Email = clsInputValidate::ReadString();

		cout << setw(37) << "" << "Enter Phone     : ";
		User.Phone = clsInputValidate::ReadString();

		cout << setw(37) << "" << "Enter Password  : ";
		User.Password = clsInputValidate::ReadString();

		User.Permissions = _ReadPermissions();

		return User;
	}
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
	static short _ReadPermissions()
	{
		short Permission = 0;
		cout << "\n" << setw(37) << "" << "Do u want to give there FULL access [Y/n]? ";
		if (clsInputValidate::ReadYES_NO())
			return clsUser::eAll;

		cout << "\n" << setw(37) << "" << "Do you want to give access to: ";
		cout << "\n" << setw(37) << "" << "Show Client List?[Y/n]. ";
		if (clsInputValidate::ReadYES_NO())
			Permission += clsUser::ePShowClientList;

		cout << setw(37) << "" << "Add New Client? [Y/n]. ";
		if (clsInputValidate::ReadYES_NO())
			Permission += clsUser::ePAddNewClients;

		cout << setw(37) << "" << "Delete Client? [Y/n]. ";
		if (clsInputValidate::ReadYES_NO())
			Permission += clsUser::ePDeleteClient;

		cout << setw(37) << "" << "Update Client? [Y/n]. ";
		if (clsInputValidate::ReadYES_NO())
			Permission += clsUser::ePUpdateClientInfo;

		cout << setw(37) << "" << "Find Client? [Y/n]. ";
		if (clsInputValidate::ReadYES_NO())
			Permission += clsUser::ePFindClient;

		cout << setw(37) << "" << "Transactions? [Y/n]. ";
		if (clsInputValidate::ReadYES_NO())
			Permission += clsUser::ePTransactions;

		cout << setw(37) << "" << "Manage users? [Y/n]. ";
		if (clsInputValidate::ReadYES_NO())
			Permission += clsUser::ePManageUsers;

		cout << setw(37) << "" << " Currency Exchange? [Y/n]. ";
		if (clsInputValidate::ReadYES_NO())
			Permission += clsUser::ePCurrencyExchange;

		return Permission;
	}

public:

	static void ShowAddNewUserScreen()
	{
		_DrawScreenHeader("  ADD NEW USER SCREEN");

		string UserName;
		cout << "\n\n" << setw(37) << "" << "Please Enter UserName: ";
		UserName = clsInputValidate::ReadString();
		if (!clsUser::IsUserExist(UserName))
		{
			clsUser NewUser = clsUser::GetAddNewUserObject(UserName);
			_ReadUserInfo(NewUser);
			cout << "\n" << setw(37) << "" << "Are you sure you wanna ADD this user? [Y/n]. ";
			if (clsInputValidate::ReadYES_NO())
			{
				clsUser::enSaveResults SaveResult = NewUser.Save();

				switch (SaveResult)
				{
				case  clsUser::enSaveResults::svSucceeded:
				{
					cout << "\n" << setw(37) << "" << "User Addeded Successfully :-)\n";
					_PrintUser(NewUser);
					break;
				}
				case clsUser::enSaveResults::svFailedEmptyObject:
				{
					cout << "\n" << setw(37) << "" << "Error User was not saved because it's Empty";
					break;
				}
				case clsUser::enSaveResults::svFaildUserNameExists:
				{
					cout << "\n" << setw(37) << "" << "Error User was not saved because UserName is used!\n";
					break;
				}
				}
			}
			else {
				cout << "\nAdding new user is cancelled.\n";
			}
		}
		else {
			cout << "\n" << "User With UserName [" << UserName << "] already exists\n";
		}
	}
};

