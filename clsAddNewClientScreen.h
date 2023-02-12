#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include "clsInputValidate.h"

class clsAddNewClientScreen : protected clsScreen
{
	static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\n\n" << setw(37)<< "" << "Enter First Name: ";
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

    static void ShowAddNewClientScreen()
    {
        _DrawScreenHeader("  ADD NEW CLIENT SCREEN");
        cout << "\n\n" << setw(37) << "" << "Please Enter Account Number: ";
        string AccNumber = clsInputValidate::ReadString();
        if (!clsBankClient::IsClientExist(AccNumber))
        {
            clsBankClient NewClient = clsBankClient::GetAddNewObject(AccNumber);

            _ReadClientInfo(NewClient);

            clsBankClient::enSaveResults SaveResults = NewClient.Save();

            switch (SaveResults)
            {
            case clsBankClient::svSucceeded:
            {
                cout << "\nAccount Addeded Successfully :-)\n";
                _PrintClient(NewClient);
                break;
            }
            case clsBankClient::svFailedEmptyObject:
            {
                cout << "\nError account was not saved because it's Empty";
                break;
            }
            case clsBankClient::svFaildAccountNumberExists:
                cout << "\nError account was not saved because account number is used!\n";
                break;
            }
        }
        else {
            cout << "\n\nClient with account number [" << AccNumber << "] is already exist!\n";
        }
    }
};

