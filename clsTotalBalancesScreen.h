#pragma once
#include "clsScreen.h"
#include <iomanip>
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsUtil.h"
class clsTotalBalancesScreen : protected clsScreen
{
	static void _PrintClientBalance(clsBankClient Client)
	{
		cout << "| " << setw(18) << left << Client.GetAccountNumber();
		cout << "| " << setw(45) << left << Client.FullName();
		cout << "| " << setw(15) << left << Client.AccountBalance;
	}

public:
	static void ShowTotalBalances()
	{
		vector <clsBankClient> vClients = clsBankClient::GetAllClients();
		string SubTitle = "    (" + to_string(vClients.size()) + ") Client(s).";
		_DrawScreenHeader("  BALANCES LIST SCREEN", SubTitle);

        cout << "\n_______________________________________________________________________________________________________________________\n" << endl;
        cout << "| " << setw(18) << left << "Account Number";
        cout << "| " << setw(45) << left << "Client Name";
        cout << "| " << setw(15) << left << "Account Balance";
        cout << "\n_______________________________________________________________________________________________________________________\n" << endl;

        double TotalBalances = 0;
        if (vClients.size() == 0)
        {
            cout << "\n\n\t\t\t\t\t   There Are No Clients In The System!.\n";
            cout << "\n_______________________________________________________________________________________________________________________\n" << endl;
        }
        else
        {
            for (clsBankClient& Client : vClients)
            {
                _PrintClientBalance(Client);
                cout << endl;
            }
            TotalBalances = clsBankClient::GetTotalBalances();
            cout << "\n_______________________________________________________________________________________________________________________\n";
            cout << "\t\t\t\t\t\t    Total Balances = " << TotalBalances;
            printf("\t\t\t\t\t\t    (%s)\n", clsUtil::NumberToText(TotalBalances).c_str());

        }
	}
};

