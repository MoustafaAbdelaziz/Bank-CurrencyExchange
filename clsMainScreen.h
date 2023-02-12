#pragma once
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsers.h"
#include "Global.h"
#include "clsUser.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeScreen.h"
class clsMainScreen : protected clsScreen
{
    enum enMainMenueChooses {
        eShowClientList = 1, eAddNewClients, eDeleteClient, eUpdateClientInfo,
        eFindClient, eTransactions, eManageUsers, eLoginRegister, eCurrencyExchange, eLogout
    };

    static enMainMenueChooses _ReadMainMenuOptions(vector <short> MainMenueOptions)
    {
        short Size = MainMenueOptions.size();
        cout << "\n" << setw(36)<< "" << "Choose What You Want To Do [1:" << to_string(Size) << "] ";
        short MainMenueChooses = clsInputValidate::ReadNumberBetween<short>(1, Size);
        return (enMainMenueChooses)MainMenueOptions[MainMenueChooses - 1];
    }

    static bool CheckAccessRights(clsUser::enMainMenuePermissions Permissions)
    {
        if (CurrentUser.CheckAccessPermission(Permissions))
        {
            return true;
        }
        return false;
    }

    static void _GoBackToMainMenue()
    {
        cout << "\n" << setw(37)<< "" << "Press Any Key To Show The Main Menue Screen...";
        system("pause>0");
        ShowMainMenue();
    }

    static void _ShowAllClientsScreen()
    {
        clsClientListScreen::ShowClientsList();
    }

    static void _ShowAddNewClientsScreen()
    {
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::showDeleteClientScreen();
    }
    
    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::ShowClientUpdateScreen();
    }

    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenue()
    {
        //cout << "\nTransactions Menue Will be here...\n";
        clsTransactionsScreen::ShowTransactionsMenueScreen();
    }

    static void _ShowManageUsersMenue()
    {
        //cout << "\nUsers Menue Will be here...\n";
        clsManageUsers::ShowManageUsersMenue();
    }
    
    static void _ShowLoginRegisterScreen() {
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }

    static void _ShowCurrencyExchangeScreen() {
        clsCurrencyExchangeScreen::ShowCurrencyExchangeMenueScreen();
    }

    static void _LogOut()
    {
        //cout << "\nEnd Screen Will be here...\n";
        CurrentUser = clsUser::Find("", "");
        /*_DrawScreenHeader("     G O O D  B Y E");
        cout << "\n\n" << setw(37) << "" << "Press Any Key To Exit...";
        system("pause>0");
        cout << "\n\n";*/
    }

    static void _PerformMainMenueOptions(enMainMenueChooses MainMenueOption)
    {
        switch (MainMenueOption)
        {
        case enMainMenueChooses::eShowClientList:
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;
        case enMainMenueChooses::eAddNewClients:
            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenue();
            break;
        case enMainMenueChooses::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;
        case enMainMenueChooses::eUpdateClientInfo:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;
        case enMainMenueChooses::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;
        case enMainMenueChooses::eTransactions:
            system("cls");
            _ShowTransactionsMenue();
            ShowMainMenue();
            break;
        case enMainMenueChooses::eManageUsers:
            system("cls");
            _ShowManageUsersMenue();
            ShowMainMenue();
            break;
        case enMainMenueChooses::eLoginRegister:
            system("cls");
            _ShowLoginRegisterScreen();
            _GoBackToMainMenue();
            break;
        case enMainMenueChooses::eCurrencyExchange:
            system("cls");
            _ShowCurrencyExchangeScreen();
            ShowMainMenue();
        case enMainMenueChooses::eLogout:
            system("cls");
            _LogOut();
            break;
        default:
            break;
        }
    }

public:
   static void ShowMainMenue()
    {
        system("cls");
        _DrawScreenHeader("\tMAIN SCREEN");
        vector <short> UserOptions;
        short OptionNumber = 0;

        cout << "\n\n"<< setw(28) << "" << "______________________________________________________";
        cout << "\n\n" << setw(37) << right << "|" << setw(25) << "MAIN MENUE SCREEN" << setw(11) << right << "|\n";
        cout << setw(28) << "" <<"______________________________________________________\n";

        if (CheckAccessRights(clsUser::ePShowClientList))
        {
            cout << "\n" << setw(37) << "|" << setw(9) << "[" << ++ OptionNumber << "] Show Clients List." << setw(5) << right << "|";
            UserOptions.push_back(1);
        }
        if (CheckAccessRights(clsUser::ePAddNewClients))
        {
            cout << "\n" << setw(37) << "|" << setw(9) << "[" << ++OptionNumber << "] Add New Clients." << setw(8) << right << " | ";
            UserOptions.push_back(2);
        }
        if (CheckAccessRights(clsUser::ePDeleteClient))
        {
            cout << "\n" << setw(37) << "|" << setw(9) << "[" << ++OptionNumber << "] Delete Client." << setw(9) << right << "|";
            UserOptions.push_back(3);
        }
        if (CheckAccessRights(clsUser::ePUpdateClientInfo))
        {
            cout << "\n" << setw(37) << "|" << setw(9) << "[" << ++OptionNumber << "] Update Client." << setw(9) << right << "|";
            UserOptions.push_back(4);
        }
        if (CheckAccessRights(clsUser::ePFindClient))
        {
            cout << "\n" << setw(37) << "|" << setw(9) << "[" << ++OptionNumber << "] Find Client." << setw(11) << right << "|";
            UserOptions.push_back(5);
        }
        if (CheckAccessRights(clsUser::ePTransactions))
        {
            cout << "\n" << setw(37) << "|" << setw(9) << "[" << ++OptionNumber << "] Transactions." << setw(10) << right << "|";
            UserOptions.push_back(6);
        }
        if (CheckAccessRights(clsUser::ePManageUsers))
        {
            cout << "\n" << setw(37) << "|" << setw(9) << "[" << ++OptionNumber << "] Manage Users." << setw(10) << right << "|";
            UserOptions.push_back(7);
        }
        if (CheckAccessRights(clsUser::ePLoginRegister))
        {
            cout << "\n" << setw(37) << "|" << setw(9) << "[" << ++OptionNumber << "] Login Register." << setw(8) << right << "|";
            UserOptions.push_back(8);
        }
        if (CheckAccessRights(clsUser::ePCurrencyExchange)) {
            cout << "\n" << setw(37) << "|" << setw(9) << "[" << ++OptionNumber << "] Currency Exchange." << setw(5) << right << "|";
            UserOptions.push_back(9);
        }
        OptionNumber++;
        cout << "\n" << setw(37) << "|" << setw(9) << "[" << OptionNumber << "] Logout." << ((OptionNumber == 10)?setw(16) : setw(17)) << right << "|\n";
        UserOptions.push_back(10);

        cout << setw(28) << "" << "______________________________________________________";
        _PerformMainMenueOptions(_ReadMainMenuOptions(UserOptions));
    }
};