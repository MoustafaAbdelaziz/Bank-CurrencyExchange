#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
#include "Global.h"
class clsUserLoginScreen : protected clsScreen
{
	static bool _Login()
	{
		string UserName = "", Password = "";
		bool LoginFailed = false;

		short FailedCounter = 3;
		do
		{
			cout << "\n\n" << setw(37) << "" << "Please Enter The Username: ";
			UserName = clsInputValidate::ReadString();
			CurrentUser = clsUser::Find(UserName);
			if (CurrentUser.AccountStatus == clsUser::enAccStatus::Blocked)
			{
				cout << "\nYour card is Blocked, Please call the bank for help\n";
				return false;
			}
			LoginFailed = CurrentUser.IsUserExist(UserName);
			if (LoginFailed)
			{
				do
				{
					FailedCounter--;
					cout << "\n" << setw(37) << "" << "Please Enter The Password: ";
					Password = clsInputValidate::ReadString();
					CurrentUser = clsUser::Find(UserName, Password);
					if (CurrentUser.IsEmpty())
						cout << "\nWrong Password you have " << FailedCounter << " More Tries \n";
					else {
						CurrentUser.RegisterLogIn();
						return true;
					}
				} while (FailedCounter >= 1);
			}
			else {
				cout << "\nInvalid Username! \n";
			}
		} while (!LoginFailed);
		CurrentUser = clsUser::Find(UserName);
		CurrentUser.AccountStatus = clsUser::Blocked;
		CurrentUser.Save();
		cout << "\nYour card is Blocked, Please call the bank for help\n";
		return false;
	}

public:

	static void ShowLoginScreen() {
		system("cls");
		_DrawScreenHeader("  USER LOGIN SCREEN");
		if(_Login()) {
			clsMainScreen::ShowMainMenue();
		}
	}
};

