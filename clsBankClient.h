#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;
class clsBankClient : public clsPerson
{
	enum enMode { EmptyMode = 0, UpdateMode, AddNewMode };
    enum enAccStatus;
    struct stTransferLogRecord;
    enMode _Mode;
	string _AccountNumber = "";
	string _PinCode = "";
	double _AccountBalance = 0.0;
    bool _MarkForDelete = false;
    enAccStatus _AccStatus = enAccStatus::Active;

    static clsBankClient _ConvertLineToObject(string Line, string Delim = "#//#")
    {
        vector <string> vClientData;
        vClientData = clsString::Split(Line, Delim);
        enAccStatus AccStatus = (vClientData[6] == "Blocked") ? enAccStatus::Blocked : enAccStatus::Active;

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]), AccStatus);
    }
    static string _ConvertObjectToLine(clsBankClient Client, string Delim = "#//#")
    {
        string sClientRecord = "";

        sClientRecord += Client.FirstName + Delim;
        sClientRecord += Client.LastName + Delim;
        sClientRecord += Client.Email + Delim;
        sClientRecord += Client.Phone + Delim;
        sClientRecord += Client.GetAccountNumber() + Delim;
        sClientRecord += Client.PinCode + Delim;
        sClientRecord += to_string(Client.GetAccountBalance()) + Delim;
        if (Client._AccStatus == enAccStatus::Blocked)
            sClientRecord += "Blocked";
        else
            sClientRecord += "Active";
        return sClientRecord;
    }

    static stTransferLogRecord _ConvertTransLogLineToRecord(string Line, string Delim = "#//#") {
        vector <string> vTrasferLogDataLine = clsString::Split(Line, Delim);
        stTransferLogRecord TransferLogRecord;
        TransferLogRecord.DateTime = vTrasferLogDataLine[0];
        TransferLogRecord.SourceAccNumber = vTrasferLogDataLine[1];
        TransferLogRecord.ReceiverAccNumber = vTrasferLogDataLine[2];
        TransferLogRecord.Amount = stoi(vTrasferLogDataLine[3]);
        TransferLogRecord.SrcBalanceAfter = stoi(vTrasferLogDataLine[4]);
        TransferLogRecord.RecieverBalanceAfter = stoi(vTrasferLogDataLine[5]);
        TransferLogRecord.UserName = vTrasferLogDataLine[6];
        return TransferLogRecord;
    }

    static vector <clsBankClient> _LoadDataFromFile()
    {
        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line)) {
                vClients.push_back(_ConvertLineToObject(Line));
            }
            MyFile.close();
        }
        return vClients;
    }
    static clsBankClient _GetEmptyObject() {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0.0, enAccStatus::Active);
    }
    static void _SaveClientsDataToFile(vector <clsBankClient> vClients)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);
        if (MyFile.is_open()){
            for (clsBankClient& Client : vClients){
                if (Client._MarkForDelete == false) {
                    MyFile << _ConvertObjectToLine(Client) << endl;
                }
            }
            MyFile.close();
        }
    }

    void _Update()
    {
        vector <clsBankClient> vClients = _LoadDataFromFile();

        for (clsBankClient& C : vClients)
        {
            if (C.GetAccountNumber() == GetAccountNumber()) {
                C = *this;
                break;
            }
        }
        _SaveClientsDataToFile(vClients);
    }

    void _AddDataLineToFile(string DataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << DataLine << endl;
            MyFile.close();
        }
    }

    void _AddNew() {
        _AddDataLineToFile(_ConvertObjectToLine(*this));
    }

    string _PrepareTransferLogRecord(clsBankClient Receiver, string UserName, double Amount, string Delim = "#//#") {
        string TransferLogRecord = "";
        TransferLogRecord += clsDate::GetSystemDateTimeString() + Delim;
        TransferLogRecord += GetAccountNumber() + Delim;
        TransferLogRecord += Receiver.GetAccountNumber() + Delim;
        TransferLogRecord += to_string(Amount) + Delim;
        TransferLogRecord += to_string(AccountBalance) + Delim;
        TransferLogRecord += to_string(Receiver.AccountBalance) + Delim;
        TransferLogRecord += UserName;
        return TransferLogRecord;
    }

    void _RegisterTransferLog(clsBankClient Receiver, string UserName, double Amount) {
        string Line = _PrepareTransferLogRecord(Receiver, UserName, Amount);
        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::out | ios::app);
        if (MyFile.is_open()) {
            MyFile << Line << endl;
            MyFile.close();
        }
    }
public:
    static enum enAccStatus { Blocked = 0, Active };

    struct stTransferLogRecord {
        string DateTime{ "" };
        string SourceAccNumber{ "" };
        string ReceiverAccNumber{ "" };
        double Amount{ 0.0 };
        double SrcBalanceAfter{ 0.0 };
        double RecieverBalanceAfter{ 0.0 };
        string UserName{ "" };
    };

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone,
        string AccountNumber, string PinCode, double AccountBalance, enAccStatus AccStatus) :
        clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
    }

    bool IsEmpty() {
        return _Mode == EmptyMode;
    }
    bool IsAddNewMode()
    {
        return _Mode == AddNewMode;
    }
    bool GetMarkedForDeleted()
    {
        return _MarkForDelete;
    }
    string GetAccountNumber(){
        return _AccountNumber;
    }

    void SetPinCode(string Pincode) {
        _PinCode = Pincode;
    }
    string GetPinCode() {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccStatus(enAccStatus AccStatus)
    {
        _AccStatus = AccStatus;
    }
    enAccStatus GetAccStatus() {
        return _AccStatus;
    }
    __declspec(property(get = GetAccStatus, put = SetAccStatus)) enAccStatus AccountStatus;

    void SetAccountBalance(double AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }
    double GetAccountBalance() {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;

    static clsBankClient Find(string AccountNumber)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);
        if(MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLineToObject(Line);

                if (Client.GetAccountNumber() == AccountNumber) {
                    MyFile.close();
                    return Client;
                }
            }
            MyFile.close();
        }
        return _GetEmptyObject();
    }
    
    static clsBankClient Find(string AccountNumber, string PinCode)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);
        if(MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLineToObject(Line);

                if (Client.GetAccountNumber() == AccountNumber && Client.PinCode == PinCode) {
                    MyFile.close();
                    return Client;
                }
            }
            MyFile.close();
        }
        return _GetEmptyObject();
    }

    static bool IsClientExist(string AccountNumber) {
        clsBankClient Client = Find(AccountNumber);
        return (!Client.IsEmpty());
    }

    enum enSaveResults { svFailedEmptyObject = 0, svSucceeded, svFaildAccountNumberExists };

    enSaveResults Save()
    {
        switch (_Mode)
        {
            case enMode::EmptyMode:
                return enSaveResults::svFailedEmptyObject;
            case enMode::UpdateMode:
            {  
                _Update();
                return enSaveResults::svSucceeded; 
            }
            case enMode::AddNewMode:
            {
                if (IsClientExist(_AccountNumber)) {
                    return enSaveResults::svFaildAccountNumberExists;
                }
                else
                {
                    _AddNew();
                    _Mode = enMode::UpdateMode;
                    return enSaveResults::svSucceeded;
                }
            }
            default:
                break;
        }
        return enSaveResults::svFailedEmptyObject;
    }

    static clsBankClient GetAddNewObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0.0, enAccStatus::Active);
    }

    bool Delete()
    {
        vector <clsBankClient> vClients = _LoadDataFromFile();

        for (clsBankClient& C : vClients){
            if (C.GetAccountNumber() == _AccountNumber){
                C._MarkForDelete = true;
                break;
            }
        }
        _SaveClientsDataToFile(vClients);
        //*this = _GetEmptyObject();
        return true;
    }

    static vector <clsBankClient> GetAllClients()
    {
        return _LoadDataFromFile();
    }

    void Deposit(double Amount)
    {
        _AccountBalance += Amount;
        Save();
    }
    bool Withdraw(double Amount)
    {
        if (Amount > _AccountBalance) {
            return false;
        }
        else {
            _AccountBalance -= Amount;
            Save();
        }
        return true;
    }

    bool Transfer(clsBankClient& Receiver, string UserName, double Amount) {
        if (Withdraw(Amount)) {
            Receiver.Deposit(Amount);
            _RegisterTransferLog(Receiver, UserName, Amount);
            return true;
        }
        else {
            return false;
        }
    }

    static vector <stTransferLogRecord> GetTransferLogList() {
        vector <stTransferLogRecord> vTransferLogList;

        fstream MyFile;
        string Line;
        stTransferLogRecord TransferLogRecord;
        MyFile.open("TransferLog.txt", ios::in);
        if (MyFile.is_open()) {
            while (getline(MyFile, Line)) {
                TransferLogRecord = _ConvertTransLogLineToRecord(Line);
                vTransferLogList.push_back(TransferLogRecord);
            }
            MyFile.close();
        }
        return vTransferLogList;
    }

    static double GetTotalBalances()
    {
        double TotalBalances = 0;
        vector <clsBankClient> vClients = clsBankClient::GetAllClients();
        for (clsBankClient& Client : vClients)
        {
            TotalBalances += Client.AccountBalance;
        }
        return TotalBalances;
    }
};