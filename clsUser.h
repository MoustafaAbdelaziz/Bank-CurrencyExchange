#pragma once
#include "clsPerson.h"
#include "clsString.h"
#include <fstream>
#include "clsUtil.h"
#include "clsBankClient.h"
class clsUser : public clsPerson
{
	enum  enMode { EmptyMode = 0, UpdateMode, AddNewMode };
	enum enAccStatus;

	enMode _Mode = enMode::EmptyMode;
	string _UserName = "";
	string _Password = "";
	int _Permissions = 0;
	bool _MarkForDelete = false;
	enAccStatus _AccStatus = enAccStatus::Active;

	struct stLoginRegisterRecord;
	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Delim = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;

		vector <string> LoginRegisterDataLine = clsString::Split(Line, Delim);
		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
		LoginRegisterRecord.Password = clsUtil::DecryptText(LoginRegisterDataLine[2]);
		LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

		return LoginRegisterRecord;
	}

	static clsUser _ConvertLineToObject(string Line, string Delim = "#//#")
	{
		vector <string> vUserData;
		vUserData = clsString::Split(Line, Delim);
		enAccStatus AccStatus = (vUserData[6] == "Blocked") ? enAccStatus::Blocked : enAccStatus::Active;
		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
			vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5]), AccStatus, stoi(vUserData[7]));
	}

	string _ConvertObjectToLine(clsUser User, string Delim = "#//#")
	{
		string sUserRecord = "";

		sUserRecord += User._UserName + Delim;
		sUserRecord += User.FirstName + Delim;
		sUserRecord += User.LastName + Delim;
		sUserRecord += User.Email + Delim;
		sUserRecord += User.Phone + Delim;
		sUserRecord += clsUtil::EncryptText(User.Password) + Delim;
		if (User._AccStatus == enAccStatus::Blocked)
			sUserRecord += "Blocked" + Delim;
		else
			sUserRecord += "Active" + Delim;

		sUserRecord += to_string(User._Permissions);
		return sUserRecord;
	}

	static vector <clsUser> _LoadDataFromFile()
	{
		vector <clsUser> vUsers;

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line)) {
				vUsers.push_back(_ConvertLineToObject(Line));
			}
			MyFile.close();
		}
		return vUsers;
	}

	void _SaveUsersDataToFile(vector <clsUser> vUsers)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);
		if (MyFile.is_open()) {
			for (clsUser& User : vUsers) {
				if (User._MarkForDelete == false) {
					MyFile << _ConvertObjectToLine(User) << endl;
				}
			}
			MyFile.close();
		}
	}

	static clsUser _GetEmptyObject() {
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", enAccStatus::Active, 0);
	}

	void _Update()
	{
		vector <clsUser> vUsers = _LoadDataFromFile();

		for (clsUser& C : vUsers)
		{
			if (C.UserName == UserName) {
				C = *this;
				break;
			}
		}
		_SaveUsersDataToFile(vUsers);
	}

	void _AddNew() {
		_AddDataLineToFile(_ConvertObjectToLine(*this));
	}

	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

	string _PrepareLogInRecord(string Delim = "#//#") {
		string LogInRegister = "";
		LogInRegister += clsDate::GetSystemDateTimeString() + Delim;
		LogInRegister += _UserName + Delim;
		LogInRegister += clsUtil::EncryptText(Password) + Delim;
		LogInRegister += to_string(_Permissions);
		return LogInRegister;
	}

public:

	struct stLoginRegisterRecord {
		string DateTime = "";
		string UserName = "";
		string Password = "";
		int Permissions = 0;
	};

	static enum enAccStatus { Blocked = 0, Active };
	enum enMainMenuePermissions {
		eAll = -1, ePShowClientList = 1, ePAddNewClients = 2, ePDeleteClient = 4, ePUpdateClientInfo = 8,
		ePFindClient = 16, ePTransactions = 32, ePLoginRegister = 64, ePCurrencyExchange = 128 ,ePManageUsers = 256
	};

	clsUser(enMode Mode, string Username, string FirstName, string LastName, string Email, string Phone,
		string Password, enAccStatus AccStatus, int Permissions)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = Username;
		_Password = Password;
		_Permissions = Permissions;
		_AccStatus = AccStatus;
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDeleted()
	{
		return _MarkForDelete;
	}

	void SetUserName(string UserName) {
		_UserName = UserName;
	}
	string GetUserName() {
		return _UserName;
	}
	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassword(string Password) {
		_Password = Password;
	}
	string GetPassword() {
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions) {
		_Permissions = Permissions;
	}
	int GetPermissions() {
		return _Permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	void SetAccStatus(enAccStatus AccStatus)
	{
		_AccStatus = AccStatus;
	}
	enAccStatus GetAccStatus() {
		return _AccStatus;
	}
	__declspec(property(get = GetAccStatus, put = SetAccStatus)) enAccStatus AccountStatus;

	static clsUser Find(string UserName)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToObject(Line);

				if (clsString::LowerString(User.UserName) == clsString::LowerString(UserName)) {
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyObject();
	}

	static clsUser Find(string UserName, string Password)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToObject(Line);

				if (clsString::LowerString(User.UserName) == clsString::LowerString(UserName)
					&& User.Password == Password) {
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyObject();
	}

	static bool IsUserExist(string UserName) {
		clsUser User = Find(UserName);
		return (!User.IsEmpty());
	}

	enum enSaveResults { svFailedEmptyObject = 0, svSucceeded, svFaildUserNameExists };
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
			if (IsUserExist(_UserName)) {
				return enSaveResults::svFaildUserNameExists;
			}
			else {
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

	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, UserName, "", "", "", "", "", enAccStatus::Active, 0);
	}

	bool Delete()
	{
		vector <clsUser> vUsers = _LoadDataFromFile();

		for (clsUser& C : vUsers) {
			if (C.UserName == UserName) {
				C._MarkForDelete = true;
				break;
			}
		}
		_SaveUsersDataToFile(vUsers);
		//*this = _GetEmptyObject();
		return true;
	}

	static vector <clsUser> GetAllUsers()
	{
		return _LoadDataFromFile();
	}

	static vector <stLoginRegisterRecord> GetLoginRegisterList() {
		vector <stLoginRegisterRecord> vLoginRegisterRecord;
		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			stLoginRegisterRecord LoginRegisterRecord;
			while (getline(MyFile, Line)) {
				LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);
				vLoginRegisterRecord.push_back(LoginRegisterRecord);
			}
			MyFile.close();
		}
		return vLoginRegisterRecord;
	}

	bool CheckAccessPermission(enMainMenuePermissions Permission)
	{
		return(Permissions == enMainMenuePermissions::eAll || (Permission & Permissions) == Permission) ? true : false;
	}

	void RegisterLogIn()
	{
		string DataLine = _PrepareLogInRecord();
		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::out | ios::app);
		if (MyFile.is_open()) {
			MyFile << DataLine << endl;
			MyFile.close();
		}
	}
};