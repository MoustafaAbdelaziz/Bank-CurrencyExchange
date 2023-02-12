#pragma once
#include <iostream>
#include "clsDate.h"
using namespace std;

class clsInputValidate
{
public:

	template <typename T>
	static bool IsNumberBetween(T Number, T From, T To)
	{
		return (Number >= From && Number <= To);
	}

	template <typename T>
	static T ReadNumber()
	{
		T Number;
		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::digits, '\n');
			cout << "Invalid Input, Try Again.\n";
		}
		return Number;
	}

	template <typename T>
	static T ReadNumberBetween(T From, T To)
	{
		T Number;
		while (!(cin >> Number) || (Number < From || Number > To))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::digits, '\n');
			cout << "Invalid Input, Try Again.\n";
		}
		return Number;
	}

	template <typename T>
	static T ReadPositiveNumber()
	{
		T number;
		cin >> number;
		while (cin.fail() || number <= 0)
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::digits, '\n');
			cout << "Invalid Input, Try Again.\n";
			cin >> number;
		}
		return number;
	}

	static string ReadString()
	{
		string S = "";
		getline(cin >> ws, S);
		return S;
	}

	static bool ReadYES_NO()
	{
		string Char;
		cin >> Char;
		while ((clsString::LowerString(Char) != "y" && clsString::LowerString(Char) != "n"))
		{
			cout << "\nInvalid Input, Try Again! [Y/n] ";
			cin >> Char;
		}
		return clsString::LowerString(Char) == "y" ? true : false;
	}

	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		return (!(clsDate::CompareDates(Date, From) == clsDate::enCompareDates::Before
			|| clsDate::CompareDates(Date, To) == clsDate::enCompareDates::After)
			|| !(clsDate::CompareDates(Date, To) == clsDate::enCompareDates::Before
				|| clsDate::CompareDates(Date, From) == clsDate::enCompareDates::After));
	}

	static bool IsValidDate(clsDate Date)
	{
		return	clsDate::IsValidDate(Date);
	}
};

