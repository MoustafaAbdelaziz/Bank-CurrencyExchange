#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsCurrencyCalculatorScreen : protected clsScreen
{
	static void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:") {

		cout << "\n\n" << setw(37) << "" << Title;
		cout << "\n" << setw(37) << "" << "___________________";
		cout << "\n" << setw(37) << "" << "Country  : " << Currency.GetCountry();
		cout << "\n" << setw(37) << "" << "Code     : " << Currency.GetCurrencyCode();
		cout << "\n" << setw(37) << "" << "Name     : " << Currency.GetCurrencyName();
		cout << "\n" << setw(37) << "" << "Rate (1$): " << Currency.Rate();
		cout << "\n" << setw(37) << "" << "___________________\n";
	}

public:

	static void ShowCurrencyCalculatorScreen() {
		_DrawScreenHeader("CURRENCY CALCULATOR SCREEN");

		cout << "\n\n" << setw(37) << "" << "Enter The First Currency Code: ";
		string CurrencyCode1 = clsInputValidate::ReadString();
		clsCurrency Currency1 = clsCurrency::FindByCode(CurrencyCode1);
		
		if (!Currency1.IsEmpty())
		{
			cout << "\n\n" << setw(37) << "" << "Enter The Second Currency Code: ";
			string CurrencyCode2 = clsInputValidate::ReadString();
			clsCurrency Currency2 = clsCurrency::FindByCode(CurrencyCode2);
			if (!Currency2.IsEmpty())
			{
				cout << "\n" << setw(37) << "" << "Enter The Amount To Exchange: ";
				float Amount = clsInputValidate::ReadNumber<float>();
				_PrintCurrencyCard(Currency1, "Convert From");
				if (Currency1.GetCurrencyCode() == "usd" || Currency1.GetCurrencyCode() == "USD")
				{
					_PrintCurrencyCard(Currency2, "To ");

					cout << "\n" << setw(37) << "" << Amount << " " << Currency1.GetCurrencyCode()
						<< " = " << Currency1.ConvertToOtherCurrency(Amount, Currency2) << " " 
						<< Currency2.GetCurrencyCode() << "\n\n";
				}
				else if (Currency2.GetCurrencyCode() != "usd" && Currency2.GetCurrencyCode() != "USD") {

					cout << "\n" << setw(37) << "" << Amount << " " << Currency1.GetCurrencyCode()
						<< " = " << Currency1.ConvertToUSD(Amount) << " USD\n";

					cout << "\n" << setw(37) << " " << "Converting From USD To:";
					_PrintCurrencyCard(Currency2, "To");

					cout << "\n" << setw(37) << "" << Amount << " " << Currency1.GetCurrencyCode() << " = "
						<< Currency1.ConvertToOtherCurrency(Currency1.ConvertToUSD(Amount), Currency2)
						<< " " << Currency2.GetCurrencyCode();
				}
				else {
					_PrintCurrencyCard(Currency2, "To ");
					cout << "\n" << setw(37) << "" << Amount << " " << Currency1.GetCurrencyCode()
						<< " = " << Currency1.ConvertToUSD(Amount) << " USD\n";
				}
			}
			else {
				cout << "\nThe Currency Is NOT Found!\n";
			}
		}
		else {
			cout << "\nThe Currency Is NOT Found!\n";
		}
	}
};