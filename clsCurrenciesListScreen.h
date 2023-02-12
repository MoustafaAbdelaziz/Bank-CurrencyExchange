#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>

class clsCurrenciesListScreen : protected clsScreen
{
    static void _PrintCurrencyRecord(clsCurrency Currency)
    {
        cout << "| " << setw(35) << left << Currency.GetCountry();
        cout << "| " << setw(8) << left << Currency.GetCurrencyCode();
        cout << "| " << setw(40) << left << Currency.GetCurrencyName();
        cout << "| " << setw(10) << left << Currency.Rate();
    }

public:

    static void ShowCurrunciesList()
    {
        vector <clsCurrency> vCurrencies = clsCurrency::GetAllUSDRates();
        string SubTitle = "    (" + to_string(vCurrencies.size()) + ") Curruncy.";
        _DrawScreenHeader("CURRUNCIES LIST SCREEN", SubTitle);
        cout << "\n\n_______________________________________________________________________________________________________________________\n" << endl;
        cout << "| " << setw(35) << left << "Country";
        cout << "| " << setw(8) << left << "Code";
        cout << "| " << setw(40) << left << "Curruncy Name";
        cout << "| " << setw(10) << left << "Rate/(1$)";
        cout << "\n_______________________________________________________________________________________________________________________\n" << endl;

        if (vCurrencies.size() == 0)
        {
            cout << "\n\nNo Currencies In The System!.\n";
        }
        else
        {
            for (clsCurrency& Currency : vCurrencies)
            {
                _PrintCurrencyRecord(Currency);
                cout << endl;
            }
            cout << "\n_______________________________________________________________________________________________________________________\n" << endl;
        }
    }
};

