#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>

class clsClientListScreen : protected clsScreen
{
    static void _PrintClientRecord(clsBankClient Client)
    {
        cout << "| " << setw(11) << left << Client.GetAccountNumber();
        cout << "| " << setw(20) << left << Client.FullName();
        cout << "| " << setw(15) << left << Client.Phone;
        cout << "| " << setw(21) << left << Client.Email;
        cout << "| " << setw(10) << left << Client.PinCode;
        cout << "| " << setw(12) << left << Client.AccountBalance;
        if (Client.AccountStatus == clsBankClient::enAccStatus::Blocked)
            cout << "| " << setw(8) << left << "Blocked";
        else
            cout << "| " << setw(8) << left << "Active";
    }

public:

    static void ShowClientsList()
    {
        vector <clsBankClient> vClients = clsBankClient::GetAllClients();
        string SubTitle = "    (" + to_string(vClients.size()) + ") Client(s).";
        _DrawScreenHeader("  ClIENT LIST SCREEN", SubTitle);
        cout << "\n\n_______________________________________________________________________________________________________________________\n" << endl;
        cout << "| " << setw(11) << left << "Acc. Number";
        cout << "| " << setw(20) << left << "Name";
        cout << "| " << setw(15) << left << "Phone";
        cout << "| " << setw(21) << left << "Email";
        cout << "| " << setw(10) << left << "Pin Code";
        cout << "| " << setw(12) << left << "Balance";
        cout << "| " << setw(12) << left << "Acc. Status";
        cout << "\n_______________________________________________________________________________________________________________________\n" << endl;

        if (vClients.size() == 0)
        {
            cout << "\n\n There Are No Clients In The System!.\n";
        }
        else
        {
            for (clsBankClient& Client : vClients)
            {
                _PrintClientRecord(Client);
                cout << endl;
            }
            cout << "\n_______________________________________________________________________________________________________________________\n" << endl;
        }
    }
};

