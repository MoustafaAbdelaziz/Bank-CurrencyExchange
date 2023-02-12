#pragma once
#include "clsScreen.h"
#include <iomanip>
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "Global.h"

class clsTransferScreen : protected clsScreen
{
	static void _PrintClient(clsBankClient Client)
	{
		cout << "\n\n" << setw(37) << "" << "Client Card:";
		cout << "\n" << setw(37) << "" << "___________________";
		cout << "\n" << setw(37) << "" << "First Name  : " << Client.FirstName;
		cout << "\n" << setw(37) << "" << "Last Name   : " << Client.LastName;
		cout << "\n" << setw(37) << "" << "Full Name   : " << Client.FullName();
		cout << "\n" << setw(37) << "" << "Email       : " << Client.Email;
		cout << "\n" << setw(37) << "" << "Phone       : " << Client.Phone;
		cout << "\n" << setw(37) << "" << "Acc. Number : " << Client.GetAccountNumber();
		cout << "\n" << setw(37) << "" << "Password    : " << Client.PinCode;
		cout << "\n" << setw(37) << "" << "Balance     : " << Client.AccountBalance;
		cout << "\n" << setw(37) << "" << "___________________\n";
	}

public:

	static void ShowTransferScreen()
	{
		string AccountNumber1 = "";
		string AccountNumber2 = "";
		double Amount = 0.0;
		_DrawScreenHeader("  TRANSFER CLIENT SCREEN");
		cout << "\n\n" << setw(37) << "" << "Please Enter Account Number To Transfer From: ";
		AccountNumber1 = clsInputValidate::ReadString();
		if (clsBankClient::IsClientExist(AccountNumber1))
		{
			clsBankClient Client = clsBankClient::Find(AccountNumber1);
			_PrintClient(Client);
			cout << "\n\n" << setw(37) << "" << "Please Enter Account Number To Transfer To: ";
			AccountNumber2 = clsInputValidate::ReadString();
			if (AccountNumber2 != AccountNumber1)
			{
				if (clsBankClient::IsClientExist(AccountNumber2))
				{
					clsBankClient Client2 = clsBankClient::Find(AccountNumber2);
					_PrintClient(Client2);
					cout << "\n" << setw(37) << "" << "Please Enter The Amount: ";
					Amount = clsInputValidate::ReadPositiveNumber<double>();
					if (Client.Transfer(Client2, CurrentUser.UserName , Amount))
					{
						cout << "\n" << setw(37) << "" << "Done Successfully";
					}
					else {
						cout << "\nERROR,Transaction doesn't proceeded.\n";
					}
				}
				else {
					cout << "\n\nClient with Account Number [" << AccountNumber1 << "] is not found!\n";
				}
			}
			else {
				cout << "\nYou Can NOT Transfer To The Same Account!\n";
			}
		}
		else {
			cout << "\n\nClient with Account Number [" << AccountNumber1 << "] is not found!\n";
		}
	}
};