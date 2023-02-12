#pragma once
#include "clsScreen.h"
#include <iomanip>
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"

class clsWithdrawScreen : protected clsScreen
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
	static void ShowWithdrawScreen()
	{
		string AccountNumber = "";

		_DrawScreenHeader("  WITHDRAW CLIENT SCREEN");
		cout << "\n\n" << setw(37) << "" << "Please Enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();
		if (clsBankClient::IsClientExist(AccountNumber))
		{
			clsBankClient Client = clsBankClient::Find(AccountNumber);
			_PrintClient(Client);

			double WithdrawAmount = 0.0;
			cout << setw(37) << "" << "Please Enter Withdraw Amount: ";
			WithdrawAmount = clsInputValidate::ReadPositiveNumber<double>();
			/*while (Client.AccountBalance < WithdrawAmount)
			{
				cout << "\n" << setw(37) << "" << "Amount Exceeds the balance, you can withdraw up to: " << Client.AccountBalance;
				cout << "\n" << setw(37) << "" << "Please enter Withdraw Amount? ";
				WithdrawAmount = clsInputValidate::ReadPositiveNumber<double>();
			}*/
			cout << "\nAre you sure you want to perform this action? [Y/n]: ";
			if (clsInputValidate::ReadYES_NO())
			{
				if (Client.Withdraw(WithdrawAmount)){
					cout << "\n" << setw(37) << "" << "Done Successfully.";
					cout << "\n" << setw(37) << "" << "New balance is: " << Client.AccountBalance;
				}
				else {
					cout << "\nCan't Withdraw, Insuffecient Balance!\n";
					cout << "\nAmount to Withdraw = " << WithdrawAmount;
					cout << "\nYour Balance = " << Client.AccountBalance;
				}
			}
			else {
				cout << "\nOperation Is Cancelled.\n";
			}
		}
		else {
			cout << "\n\nClient with Account Number [" << AccountNumber << "] is not found!\n";
		}
	}
};

