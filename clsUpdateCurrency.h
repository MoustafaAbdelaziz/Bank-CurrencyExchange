#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsUpdateCurrency : protected clsScreen
{
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

	static void ShowUpdateCurrencyScreen() {

		_DrawScreenHeader("UPDATE CURRUNCY SCREEN");

		cout << "\n\n" << setw(37) << "" << "Enter The Currency Code: ";
		string CurrencyCode = clsInputValidate::ReadString();
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		if (!Currency.IsEmpty()) {
			_PrintCurrencyCard(Currency);
			cout << "Are You Sure You Want To Update The Rate Of This Currency [Y/n]: ";
			if (clsInputValidate::ReadYES_NO()) {
				cout << "\n" << setw(37) << "" << "Update Currency Rate:";
				cout << "\n" << setw(37) << "" << "____________________";
				cout << "\n" << setw(37) << "" << "Enter New Rate: ";
				float NewRate = clsInputValidate::ReadNumber<float>();
				Currency.UpdateRate(NewRate);
				cout << "\nCurrency Rate Updated Successfully :-)\n";
				_PrintCurrencyCard(Currency);
			}
			else {
				cout << "\nUpdating Currency Rate Is Cancelled\n";
			}
		}
		else {
			cout << "\nThe Currency Is NOT Found!\n";
		}
	}
};

