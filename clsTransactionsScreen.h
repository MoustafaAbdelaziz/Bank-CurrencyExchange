#pragma once
#include "clsScreen.h"
#include <iomanip>
#include <iostream>
#include "clsInputValidate.h"
#include "clsDepositeScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTransferScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferLogScreen.h"

class clsTransactionsScreen : protected clsScreen
{
	enum enTransactionsOptions { enDeposit = 1, enWithdraw, enTransfer, enTotalBalance, enTransferLog, eMainMenue };

   static enTransactionsOptions _ReadTransactionMenueOptions()
    {
        cout << "\n" << setw(37) << "" << "Choose What You Want To Do [1:6] ";
        short MainMenueChooses = clsInputValidate::ReadNumberBetween<short>(1, 6);
        return (enTransactionsOptions)MainMenueChooses;
    }

    static void _BackToTheTransactionsScreen()
    {
        cout << "\n" << setw(37) << "Press Any Key To Show The Transactions Screen...";
        system("pause>0");
        ShowTransactionsMenueScreen();
    }

    static void _ShowDepositScreen()
    {
        clsDepositeScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen()
    {
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTransferScreen()
    {
        clsTransferScreen::ShowTransferScreen();
    }

    static void _ShowTransferLogScreen() {
        clsTransferLogScreen::ShowTransferLogScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        clsTotalBalancesScreen::ShowTotalBalances();
    }

    static void _PerformTransactionsScreenOptions(enTransactionsOptions TransactionsOptions)
    {
        switch (TransactionsOptions)
        {
        case enTransactionsOptions::enDeposit:
            system("cls");
            _ShowDepositScreen();
            _BackToTheTransactionsScreen();
            break;
        case clsTransactionsScreen::enWithdraw:
            system("cls");
            _ShowWithdrawScreen();
            _BackToTheTransactionsScreen();
            break;
        case clsTransactionsScreen::enTransfer:
            system("cls");
            _ShowTransferScreen();
            _BackToTheTransactionsScreen();
            break;
        case clsTransactionsScreen::enTotalBalance:
            system("cls");
            _ShowTotalBalancesScreen();
            _BackToTheTransactionsScreen();
            break;
        case clsTransactionsScreen::enTransferLog:
            system("cls");
            _ShowTransferLogScreen();
            _BackToTheTransactionsScreen();
        case clsTransactionsScreen::eMainMenue:
            break;
        default:
            break;
        }
    }

public:

   static void ShowTransactionsMenueScreen()
    {
        system("cls");
        _DrawScreenHeader("  TRANSACTIONS SCREEN");
        cout << "\n\n" << setw(28) << "" << "______________________________________________________";
        cout << "\n\n" << setw(37) << right << "|" << setw(29) << "TRANSACTIONS MENUE SCREEN" << setw(6) << right << "|";
        cout << "\n" << setw(28) << "" << "______________________________________________________\n";
        cout << "\n" << setw(37) << "|" << setw(20) << "[1] Deposit." << setw(15) << right << "|";
        cout << "\n" << setw(37) << "|" << setw(21) << "[2] Withdraw." << setw(14) << right << "|";
        cout << "\n" << setw(37) << "|" << setw(21) << "[3] Transfer." << setw(14) << right << "|";
        cout << "\n" << setw(37) << "|" << setw(27) << "[4] Total Balances." << setw(8) << right << "|";
        cout << "\n" << setw(37) << "|" << setw(25) << "[5] Transfer Log." << setw(10) << right << "|";
        cout << "\n" << setw(37) << "|" << setw(23) << "[6] Main Menue." << setw(12) << right << "|";
        cout << "\n" << setw(28) << "" << "______________________________________________________\n";
        _PerformTransactionsScreenOptions(_ReadTransactionMenueOptions());
    }
};