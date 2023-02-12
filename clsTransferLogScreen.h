#pragma once
#include "clsScreen.h"
#include <iomanip>
#include <iostream>
#include "clsBankClient.h"

class clsTransferLogScreen : protected clsScreen
{
    static void PrinTransferLogRecord(clsBankClient::stTransferLogRecord TransferLog)
    {
        cout << "| " << setw(30) << left << TransferLog.DateTime;
        cout << "| " << setw(10) << left << TransferLog.SourceAccNumber;
        cout << "| " << setw(10) << left << TransferLog.ReceiverAccNumber;
        cout << "| " << setw(10) << left << TransferLog.Amount;
        cout << "| " << setw(10) << left << TransferLog.SrcBalanceAfter;
        cout << "| " << setw(10) << left << TransferLog.RecieverBalanceAfter;
        cout << "| " << setw(10) << left << TransferLog.UserName;
    }

public:
    static void ShowTransferLogScreen()
    {
        vector <clsBankClient::stTransferLogRecord> vTransferLogList = clsBankClient::GetTransferLogList();
        string SubTitle = "      (" + to_string(vTransferLogList.size()) + ") Record(s).";

        _DrawScreenHeader("TRANSFER LOG LIST SCREEN", SubTitle);

        cout << "\n_______________________________________________________________________________________________________________________\n" << endl;
        cout << "| " << setw(30) << left << "Date / Time";
        cout << "| " << setw(10) << left << "S.Acc-Num";
        cout << "| " << setw(10) << left << "R.Acc-Num";
        cout << "| " << setw(10) << left << "Amount";
        cout << "| " << setw(10) << left << "S.Balance";
        cout << "| " << setw(10) << left << "R.Balance";
        cout << "| " << setw(10) << left << "User";
        cout << "\n_______________________________________________________________________________________________________________________\n" << endl;
        if (vTransferLogList.size() == 0) {
            cout << "\n\n There Are No Transfers Yet In The System!.\n";
        }
        else
        {
            for (clsBankClient::stTransferLogRecord& LoginRegister : vTransferLogList)
            {
                PrinTransferLogRecord(LoginRegister);
                cout << endl;
            }
            cout << "\n_______________________________________________________________________________________________________________________\n" << endl;
        }
    }
};