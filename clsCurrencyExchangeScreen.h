#pragma once
#include "clsScreen.h"
#include <iomanip>
#include <iostream>
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrency.h"
#include "clsUpdateCurrency.h"
#include "clsCurrencyCalculatorScreen.h"
class clsCurrencyExchangeScreen : protected clsScreen
{
    enum eCurrencyExchangeOptions { eList = 1, eFind, eUpdate, eCurrencyCalc, eMainMenue };

    static eCurrencyExchangeOptions _ReadCurrencyExchangeMenueOptions() {
        cout << "\n" << setw(37) << "" << "Choose What You Want To Do [1:5] ";
        return (eCurrencyExchangeOptions) clsInputValidate::ReadNumberBetween<short>(1, 5);
    }

    static void _BackToCurrencyScreen()
    {
        cout << "\n" << setw(37) << "Press Any Key To Show The Currency Exchange Screen...";
        system("pause>0");
        ShowCurrencyExchangeMenueScreen();
    }

    static void _ShowCurrencyListScreen() {
        clsCurrenciesListScreen::ShowCurrunciesList();
    }
    static void _ShowCurrencyFindScreen() {
        clsFindCurrency::ShowFindCurrencyScreen();
    }
    static void _ShowCurrencyUpdate() {
        clsUpdateCurrency::ShowUpdateCurrencyScreen();
    }
    static void _ShowCurrencyCalcScreen() {
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }

    static void _PerformCurrencyExchangeScreenOptions(eCurrencyExchangeOptions CurrencyExchangeOptions) {
        switch (CurrencyExchangeOptions)
        {
        case clsCurrencyExchangeScreen::eList:
            system("cls");
            _ShowCurrencyListScreen();
            _BackToCurrencyScreen();
            break;
        case clsCurrencyExchangeScreen::eFind:
            system("cls");
            _ShowCurrencyFindScreen();
            _BackToCurrencyScreen();
            break;
        case clsCurrencyExchangeScreen::eUpdate:
            system("cls");
            _ShowCurrencyUpdate();
            _BackToCurrencyScreen();
            break;
        case clsCurrencyExchangeScreen::eCurrencyCalc:
            system("cls");
            _ShowCurrencyCalcScreen();
            _BackToCurrencyScreen();
            break;
        case clsCurrencyExchangeScreen::eMainMenue:
            break;
        default:
            break;
        }
    }
public:

    static void ShowCurrencyExchangeMenueScreen()
    {
        system("cls");
        _DrawScreenHeader("CURRENCY MAIN MENUE SCREEN");
        cout << "\n\n" << setw(28) << "" << "______________________________________________________";
        cout << "\n\n" << setw(37) << right << "|" << setw(32) << "CURRENCY EXCHANGE MENUE SCREEN" << setw(3) << right << "|";
        cout << "\n" << setw(28) << "" << "______________________________________________________\n";
        cout << "\n" << setw(37) << "|" << setw(23) << "[1] List Currencies." << setw(12) << right << "|";
        cout << "\n" << setw(37) << "|" << setw(21) << "[2] Find Currnecy." << setw(14) << right << "|";
        cout << "\n" << setw(37) << "|" << setw(19) << "[3] Update Rate." << setw(16) << right << "|";
        cout << "\n" << setw(37) << "|" << setw(27) << "[4] Currency Calculator." << setw(8) << right << "|";
        cout << "\n" << setw(37) << "|" << setw(18) << "[5] Main Menue." << setw(17) << right << "|";
        cout << "\n" << setw(28) << "" << "______________________________________________________\n";
        _PerformCurrencyExchangeScreenOptions(_ReadCurrencyExchangeMenueOptions());
    }
};

