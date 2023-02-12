#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include "clsInputValidate.h"

class clsUpdateClientScreen : protected clsScreen
{
    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\n\n" << setw(37) << "" << "Enter First Name: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << setw(37) << "" << "Enter Last Name: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << setw(37) << "" << "Enter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << setw(37) << "" << "Enter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << setw(37) << "" << "Enter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();

        if (Client.IsAddNewMode())
        {
            cout << setw(37) << "" << "Enter Account Balance: ";
            Client.AccountBalance = clsInputValidate::ReadNumber<float>();
        }
    }
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

	static void ShowClientUpdateScreen()
    {
        string AccountNumber = "";
        _DrawScreenHeader("  UPDATE CLIENT SCREEN");
        cout << "\n\n" << setw(37) << "" << "Please Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        if (clsBankClient::IsClientExist(AccountNumber)) {

            clsBankClient Client1 = clsBankClient::Find(AccountNumber);
            _PrintClient(Client1);

            cout << "\nDo you sure u want to UPDATE this Client? [Y/n]: ";
            if (clsInputValidate::ReadYES_NO())
            {
                cout << "\n\n" << setw(37) << "" << "Updating Client Info:";
                cout << "\n" << setw(37) << "" << "____________________\n";
                _ReadClientInfo(Client1);

                clsBankClient::enSaveResults SaveResult;
                SaveResult = Client1.Save();

                switch (SaveResult)
                {
                    case  clsBankClient::enSaveResults::svSucceeded:
                    {
                        cout << "\nAccount Updated Successfully :-)\n";
                        _PrintClient(Client1);
                        break;
                    }
                    case clsBankClient::enSaveResults::svFailedEmptyObject:
                    {
                        cout << "\nError account was not saved because it's Empty";
                        break;
                    }

                }
            }
        }
        else {
            cout << "\n\nClient with Account Number [" << AccountNumber << "] is not found!\n";
        }
    }
};

