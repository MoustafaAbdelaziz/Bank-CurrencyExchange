#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsFindCurrency : protected clsScreen
{
	enum enCodeOrCountry {Code = 1, Country};

	static void _PrintCurrencyCard(clsCurrency Currency) {

		cout << "\n\n" << setw(37) << "" << "Currency Card:";
		cout << "\n" << setw(37) << "" << "___________________";
		cout << "\n" << setw(37) << "" << "Country  : " << Currency.GetCountry();
		cout << "\n" << setw(37) << "" << "Code     : " << Currency.GetCurrencyCode();
		cout << "\n" << setw(37) << "" << "Name     : " << Currency.GetCurrencyName();
		cout << "\n" << setw(37) << "" << "Rate (1$): " << Currency.Rate();
		cout << "\n" << setw(37) << "" << "___________________\n";
	}

public:
	static void ShowFindCurrencyScreen() {
		
		_DrawScreenHeader(" FIND CURRENCY SCREEN");

		cout << "\n\n" << setw(37) << "" << "Find By: [1] Code or [2] Country? ";
		short Choice = clsInputValidate::ReadNumberBetween<short>(1, 2);
		if (Choice == enCodeOrCountry::Code)
		{
			cout << "\n" << setw(37) << "" << "Enter the currency code, please: ";
			string CurrencyCode = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

			if (!Currency.IsEmpty()) {
				_PrintCurrencyCard(Currency);
			}
			else {
				cout << "\nThe Currency Is NOT Found!\n";
			}
		}
		else {
			cout << "\n" << setw(37) << "" << "Enter the country name, please: ";
			string CountryName = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(CountryName);

			if (!Currency.IsEmpty()) {
				_PrintCurrencyCard(Currency);
			}
			else {
				cout << "\nThe Currency Is NOT Found!\n";
			}
		}
	}
};