#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include "iomanip"
class clsUpdateUserScreen : protected clsScreen
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

		cout << setw(37) << "" << "Choose Status   : [1] Active [2] Blocked: ";
		User.AccountStatus = (clsUser::enAccStatus)clsInputValidate::ReadNumberBetween<short>(1, 2);

		User.Permissions = _ReadPermissions();

		return User;
	}
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
	static short _ReadPermissions()
	{
		short Permission = 0;
		cout << "\n" << setw(37) << "" << "Do u want to give there FULL access [Y/n]? ";
		if (clsInputValidate::ReadYES_NO())
			return clsUser::eAll;

		cout << "\n" << setw(37) << "" << "Do you want to give access to: ";
		cout << "\n\n" << setw(37) << "" << "Show Client List? [Y/n]. ";
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
		
		cout << setw(37) << "" << "Login register? [Y/n]. ";
		if (clsInputValidate::ReadYES_NO())
			Permission += clsUser::ePLoginRegister;
		
		cout << setw(37) << "" << " Currency Exchange? [Y/n]. ";
		if (clsInputValidate::ReadYES_NO())
			Permission += clsUser::ePCurrencyExchange;

		return Permission;
	}

public:
	static void ShowUpdateUserScreen() {
		_DrawScreenHeader("  UPDATE USER SCREEN");

		string UserName;
		cout << "\n\n" << setw(37) << "" << "Please Enter UserName: ";
		UserName = clsInputValidate::ReadString();
		if (clsUser::IsUserExist(UserName))
		{
			clsUser User = clsUser::Find(UserName);
			_PrintUser(User);
			cout << "\n\n" << setw(37) << "" << "Are you sure u wanna update this USER? [Y/n] ";
			if (clsInputValidate::ReadYES_NO()){
				cout << "\n" << setw(37) << "" << "Update user info:";
				cout << "\n" << setw(37) << "" << "_________________\n";
				_ReadUserInfo(User);
				if (User.Save() == clsUser::svSucceeded){
					cout << "\nDone succeccfully.\n";
				}
				else {
					cout << "\nFailed to update.\n";
				}
			}
			else {
				cout << "\n Updating is cancelled.\n";
			}
		}
		else {
			cout << "\n" << "User With UserName [" << UserName << "] Doesn't exist\n";
		}
	}
};

