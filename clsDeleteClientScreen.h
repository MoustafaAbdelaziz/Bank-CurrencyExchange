#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include "clsInputValidate.h"

class clsDeleteClientScreen : protected clsScreen
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
	static void showDeleteClientScreen()
    {
        string AccountNumber = "";

        _DrawScreenHeader("  DELETE CLIENT SCREEN");
        cout << "\n\n" << setw(37) << "" << "Please Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        if (clsBankClient::IsClientExist(AccountNumber))
        {
            clsBankClient Client = clsBankClient::Find(AccountNumber);
            _PrintClient(Client);

            cout << "\nAre you sure that you want to delete this Client? [Y/n]: ";
            if (clsInputValidate::ReadYES_NO())
            {
                if (Client.Delete())
                {
                    cout << "\n" << setw(37) << "" << "Client Deleted Successfully :-)\n";
                    _PrintClient(Client);
                }
                else
                    cout << "\nERROR, Client Was not Deleted\n";
            }
        }
        else {
            cout << "\n\nClient with Account Number [" << AccountNumber << "] is not found!\n";
        }
    }
};

