#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include <vector>
#include <fstream>

class clsCurrency
{
	enum enMode {EmptyMode = 0, UpdateMode};
	
	enMode _Mode = enMode::EmptyMode;
	string _Country{ "" };
	string _CurrencyCode{ "" };
	string _CurrencyName{ "" };
	float _Rate = 0.0F;

	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Delim = "#//#") {
		vector<string> vCurrencyData;
		vCurrencyData = clsString::Split(Line, Delim);

		return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2],
			stod(vCurrencyData[3]));
	}
	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Delim = "#//#")
	{
		string stCurrencyRecord = "";
		stCurrencyRecord += Currency.GetCountry() + Delim;
		stCurrencyRecord += Currency.GetCurrencyCode() + Delim;
		stCurrencyRecord += Currency.GetCurrencyName() + Delim;
		stCurrencyRecord += to_string(Currency.Rate());

		return stCurrencyRecord;
	}


	static  vector <clsCurrency> _LoadCurrencysDataFromFile()
	{
		vector <clsCurrency> vCurrencies;

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open()){
			string Line;
			while (getline(MyFile, Line)){
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				vCurrencies.push_back(Currency);
			}
			MyFile.close();
		}
		return vCurrencies;
	}

	static void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrencies)
	{
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);

		string DataLine;
		if (MyFile.is_open()){
			for (clsCurrency& C : vCurrencies){
				DataLine = _ConvertCurrencyObjectToLine(C);
				MyFile << DataLine << endl;
			}
			MyFile.close();
		}
	}
	void _Update()
	{
		vector <clsCurrency> _vCurrencies;
		_vCurrencies = _LoadCurrencysDataFromFile();

		for (clsCurrency& C : _vCurrencies){
			if (C.GetCurrencyCode() == GetCurrencyCode()){
				C = *this;
				break;
			}
		}
		_SaveCurrencyDataToFile(_vCurrencies);
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}
public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate) {
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static vector <clsCurrency> GetAllUSDRates()
	{
		return _LoadCurrencysDataFromFile();
	}

	string GetCountry() {
		return _Country;
	}

	string GetCurrencyCode() {
		return _CurrencyCode;
	}

	string GetCurrencyName() {
		return _CurrencyName;
	}

	void UpdateRate(float NewRate) {
		_Rate = NewRate;
		_Update();
	}

	float Rate() {
		return _Rate;
	}

	static clsCurrency FindByCode(string CurrencyCode) {
		CurrencyCode = clsString::LowerString(CurrencyCode);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::LowerString(Currency.GetCurrencyCode()) == CurrencyCode) {
					MyFile.close();
					return Currency;
				}
			}
			MyFile.close();
		}
		return _GetEmptyCurrencyObject();
	}
	static clsCurrency FindByCountry(string Country) {
		Country = clsString::LowerString(Country);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::LowerString(Currency.GetCountry()) == Country) {
					MyFile.close();
					return Currency;
				}
			}
			MyFile.close();
		}
		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency C1 = clsCurrency::FindByCode(CurrencyCode);
		return (!C1.IsEmpty());
	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrencysDataFromFile();
	}

	float ConvertToUSD(float Amount) {
		return (float) Amount / Rate();
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency) {
		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency.GetCurrencyCode() == "USD" || Currency.GetCurrencyCode() == "usd") {
			return AmountInUSD;
		}

		return (float)(AmountInUSD * Currency.Rate());
	}
};