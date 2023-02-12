#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
using namespace std;
#pragma warning (disable : 4996)

class clsDate
{
	short _Day = 1, _Month = 1, _Year = 1900;

public:

	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		_Year = now->tm_year + 1900;
		_Month = now->tm_mon + 1;
		_Day = now->tm_mday;
	}
	clsDate(string Date)
	{
		vector <string> vDate;
		vDate = clsString::Split(Date, "/");
		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}
	clsDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}
	clsDate(short DateOrderInYear, short Year)
	{
		clsDate Date = GetDateFromDayOrderInYear(DateOrderInYear, Year);
		_Day = Date._Day;
		_Month = Date._Month;
		_Year = Date._Year;
	}

	void setDay(short Day) {
		_Day = Day;
	}
	short getDay() {
		return _Day;
	}
	__declspec(property(get = getDay, put = setDay)) short Day;
	
	void setMonth(short Month) {
		_Month = Month;
	}
	short getMonth() {
		return _Month;
	}
	__declspec(property(get = getMonth, put = setMonth)) short Month;
	
	void setYear(short Year) {
		_Year = Year;
	}
	short getYear() {
		return _Year;
	}
	__declspec(property(get = getYear, put = setYear)) short Year;

	void Print()
	{
		cout << DateToString();
	}

	static clsDate GetSystemDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year;
		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		return clsDate(Day, Month, Year);
	}

	static string GetSystemDateTimeString()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year, Hour, Minute, Second;
		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		return(to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year) + " - "
			+ to_string(Hour) + ":" + to_string(Minute) + ":" + to_string(Second));
	}

	static bool IsValidDate(clsDate Date)
	{
		return Date.Day > NumberOfDaysInAMonth(Date.Month, Date.Year) ? false : (Date.Month > 12 || Date.Month < 1) 
			? false : (Date.Year <1)? false : true;
	}
	bool IsValidDate() {
		return IsValidDate(*this);
	}

	static string DateToString(clsDate Date) {
		return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
	}
	string DateToString()
	{
		return DateToString(*this);
	}

	static bool IsLeapYear(short Year)
	{
		//return Year % 400 == 0 ? true : Year % 100 == 0 ? false : Year % 4 == 0 ? true : false;
		return (Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0;
	}
	bool IsLeapYear()
	{
		return IsLeapYear(_Year);
	}

	static short NumberOfDaysInAYear(short Year)
	{
		return IsLeapYear(Year) ? 366 : 365;
	}
	short NumberOfDaysInAYear() {
		return NumberOfDaysInAYear(_Year);
	}

	static short NumberOfHoursInAYear(short Year)
	{
		return NumberOfDaysInAYear(Year) * 24;
	}
	short NumberOfHoursInAYear() {
		return NumberOfHoursInAYear(_Year);
	}

	static int NumberOfMinsInAYear(short Year)
	{
		return NumberOfHoursInAYear(Year) * 60;
	}
	int NumberOfMinsInAYear() {
		return NumberOfMinsInAYear(_Year);
	}

	static int NumberOfSecInAYear(short Year)
	{
		return NumberOfMinsInAYear(Year) * 60;
	}
	int NumberOfSecInAYear() {
		return NumberOfSecInAYear(_Year);
	}

	static short NumberOfDaysInAMonth(short Month, short Year)
	{
		short Arr31Days[13] = { 30, 31, 30, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		return Month == 2 ? (IsLeapYear(Year) ? 29 : 28) : Arr31Days[Month];
	}
	short NumberOfDaysInAMonth() {
		return NumberOfDaysInAMonth(_Month, _Year);
	}

	static short NumberOfHoursInAMonth(short Month, short Year)
	{
		return  NumberOfDaysInAMonth(Month, Year) * 24;
	}
	short NumberOfHoursInAMonth()
	{
		return  NumberOfDaysInAMonth(_Month, _Year) * 24;
	}

	static int NumberOfMinutesInAMonth(short Month, short Year)
	{
		return  NumberOfHoursInAMonth(Month, Year) * 60;
	}
	int NumberOfMinutesInAMonth()
	{
		return  NumberOfHoursInAMonth(_Month, _Year) * 60;
	}

	static int NumberOfSecondsInAMonth(short Month, short Year)
	{
		return  NumberOfMinutesInAMonth(Month, Year) * 60;
	}
	int NumberOfSecondsInAMonth()
	{
		return  NumberOfMinutesInAMonth(_Month, _Year) * 60;
	}

	static short DayOfWeekOrder(short Year, short Month, short Day)
	{
		short a = (14 - Month) / 12;
		short y = Year - a;
		short m = Month + 12 * a - 2;

		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}
	short DayOfWeekOrder() {
		return DayOfWeekOrder(_Year, _Month, _Day);
	}
	
	static string DayName(short DayOrder)
	{
		string ArrDayNames[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		return ArrDayNames[DayOrder];
	}
	string DayName()
	{
		return DayName(_Day);
	}

	static string MonthName(short Month)
	{
		string ArrMonthName[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		return ArrMonthName[Month - 1];
	}
	string MonthName()
	{
		return MonthName(_Month);
	}

	static void PrintMonthCalender(short Year, short Month)
	{
		short NumberOfDays = NumberOfDaysInAMonth(Month, Year);
		short Current = DayOfWeekOrder(Year, Month, 1);

		printf("\n\n  ________________%s________________\n\n", MonthName(Month).c_str());

		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
		short i;
		for (i = 0; i < Current; i++)
			cout << "     ";

		for (short x = 1; x <= NumberOfDays; x++)
		{
			printf("%5d", x);

			if (++i == 7)
			{
				i = 0;
				cout << endl;
			}
		}
		printf("\n  ___________________________________\n");
	}
	void PrintMonthCalender() {
		PrintMonthCalender(_Year, _Month);
	}

	static void PrintYearCalender(short Year)
	{
		cout << "\n\n  __________________________________\n\n";
		cout << "\t    Calender - " << Year;
		printf("\n  __________________________________\n");
		for (short i = 1; i <= 12; i++)
		{
			PrintMonthCalender(Year, i);
			cout << endl;
		}
	}
	void PrintYearCalender() {
		PrintYearCalender(_Year);
	}

	static short NumberOfDaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
	{
		short TotalDays = 0;

		for (short i = 1; i < Month; i++)
		{
			TotalDays += NumberOfDaysInAMonth(i, Year);
		}
		TotalDays += Day;
		return TotalDays;
	}
	short NumberOfDaysFromTheBeginingOfTheYear() {
		return NumberOfDaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
	}

	static clsDate GetDateFromDayOrderInYear(short DayOrderInYear, short Year)
	{
		clsDate Date;
		short RemainderDays = DayOrderInYear;
		short MonthDays = 0;

		Date._Year = Year;
		Date._Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInAMonth(Date._Month, Year);

			if (RemainderDays > MonthDays)
			{
				RemainderDays -= MonthDays;
				Date._Month++;
			}
			else
			{
				Date._Day = RemainderDays;
				break;
			}
		}
		return Date;
	}

	void AddDays(short Days)
	{
		short RemainingDays = Days + NumberOfDaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
		short MonthDays = 0;

		_Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInAMonth(_Month, _Year);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				_Month++;

				if (_Month > 12)
				{
					_Month = 1;
					_Year++;
				}
			}
			else
			{
				_Day = RemainingDays;
				break;
			}
		}
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return  (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ?
			true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
	}
	bool IsDate1BeforeDate2(clsDate Date2)
	{
		return IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.Year == Date2.Year) && (Date1.Month == Date2.Month) && (Date1.Day == Date2.Day);
	}
	bool IsDate1EqualDate2( clsDate Date2)
	{
		return IsDate1EqualDate2(*this, Date2);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return !IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2);
	}
	bool IsDate1AfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	enum enCompareDates { Before = -1, Equal, After };
	static short CompareDates(clsDate Date1, clsDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
			return enCompareDates::Before;

		if (IsDate1EqualDate2(Date1, Date2))
			return enCompareDates::Equal;

		return enCompareDates::After;
	}
	short CompareDates(clsDate Date2)
	{
		return CompareDates(*this, Date2);
	}

	static bool IsLastDayInMonth(clsDate Date)
	{
		return Date.Day == NumberOfDaysInAMonth(Date.Month, Date.Year);
	}
	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month)
	{
		return Month == 12;
	}
	
	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate TempDate;

		TempDate.Day = Date1.Day;
		TempDate.Month = Date1.Month;
		TempDate.Year = Date1.Year;

		Date1.Day = Date2.Day;
		Date1.Month = Date2.Month;
		Date1.Year = Date2.Year;

		Date2.Day = TempDate.Day;
		Date2.Month = TempDate.Month;
		Date2.Year = TempDate.Year;
	}
	void SwapDates(clsDate& Date2) {
		 SwapDates(*this, Date2);
	}

	static clsDate AddOneDay(clsDate Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date.Month))
			{
				Date.Year++;
				Date.Month = 1;
				Date.Day = 1;
			}
			else
			{
				Date.Day = 1;
				Date.Month++;
			}
		}
		else
			Date.Day++;

		return Date;
	}
	clsDate AddOneDay() {
		*this = AddOneDay(*this);
	}

	static clsDate AddXDays(clsDate& Date, short DaysToAdd)
	{
		for (short i = 1; i <= DaysToAdd; i++)
		{
			Date = AddOneDay(Date);
		}
		return Date;
	}
	clsDate AddXDays(short DaysToAdd) {
		return AddXDays(*this, DaysToAdd);
	}

	static clsDate AddOneWeek(clsDate &Date)
	{
		for (short i = 1; i <= 7; i++)
		{
			Date = AddOneDay(Date);
		}
		return Date;
	}
	clsDate AddOneWeek() {
		return AddOneWeek(*this);
	}

	static clsDate AddXWeeks(clsDate &Date, short WeeksToAdd)
	{
		for (short i = 1; i <= WeeksToAdd; i++)
		{
			Date = AddOneWeek(Date);
		}
		return Date;
	}
	clsDate AddXWeeks(short WeeksToAdd) {
		return AddXWeeks(*this, WeeksToAdd);
	}

	static clsDate AddOneMonth(clsDate& Date)
	{
		if (IsLastMonthInYear(Date.Month))
		{
			Date.Month = 1;
			Date.Year++;
		}
		else if (IsLastDayInMonth(Date) || (Date.Month == 1 && (Date.Day == 30 || Date.Day == 29)))
		{
			Date.Month++;
			short MonthDays = NumberOfDaysInAMonth(Date.Month, Date.Year);
			if (MonthDays < Date.Day)
				Date.Day = MonthDays;
		}
		else
			Date.Month++;
		return Date;
	}
	clsDate AddOneMonth() {
		return AddOneMonth(*this);
	}

	static clsDate AddXMonths(clsDate &Date, short MonthsToAdd)
	{
		for (short i = 1; i <= MonthsToAdd; i++)
			Date = AddOneMonth(Date);

		return Date;
	}
	clsDate AddXMonths(short MonthsToAdd) {
		return AddXMonths(*this, MonthsToAdd);
	}

	static clsDate AddOneYear(clsDate& Date)
	{
		return AddXMonths(Date,12);
	}
	clsDate AddOneYear() {
		return AddOneYear(*this);
	}

	static clsDate AddXYears(clsDate& Date, short YearsToAdd)
	{
		for (short i = 1; i <= YearsToAdd; i++)
			Date = AddOneYear(Date);

		return Date;
	}
	clsDate AddXYears(short YearsToAdd)
	{
		return AddXYears(*this, YearsToAdd);
	}

	static clsDate AddOneDecade(clsDate& Date)
	{
		return AddXYears(Date, 10);
	}
	clsDate AddOneDecade() {
		return AddOneDecade(*this);
	}

	static clsDate AddXDecades(clsDate Date, short DecatesToAdd)
	{
		for (short i = 1; i <= DecatesToAdd; i++)
			Date = AddOneDecade(Date);

		return Date;
	}
	clsDate AddXDecades(short DecatesToAdd) {
	return AddXDecades(*this, DecatesToAdd);
	}

	static clsDate AddOneCentury(clsDate &Date)
	{
		return AddXDecades(Date, 10);
	}
	clsDate AddOneCentury() {
		return AddOneCentury(*this);
	}

	static clsDate AddXCenturies(clsDate Date, short CenturiesToAdd)
	{
		for (short i = 1; i <= CenturiesToAdd; i++)
			Date = AddOneCentury(Date);

		return Date;
	}
	clsDate AddXCenturies(short CenturiesToAdd) {
		return AddXCenturies(*this, CenturiesToAdd);
	}

	static clsDate AddOneMillennnium(clsDate &Date)
	{
		return AddXCenturies(Date, 10);
	}
	clsDate AddOneMillennnium() {
		return AddOneMillennnium(*this);
	}

	static clsDate DecreaseOneDay(clsDate &Date)
	{
		if (Date.Day ==1)
		{
			if (Date.Month == 1)
			{
				Date.Year--;
				Date.Month = 12;
				Date.Day = 31;
			}
			else
			{
				--Date.Month;
				short MonthDays = NumberOfDaysInAMonth(Date.Month, Date.Year);
				Date.Day = MonthDays;
			}
		}
		else
			Date.Day--;

		return Date;
	}
	clsDate DecreaseOneDay() {
		return DecreaseOneDay(*this);
	}

	static clsDate DecreaseXDays(clsDate &Date, short DaysToSubtract)
	{
		for (short i = 1; i <= DaysToSubtract; i++)
		{
			Date = DecreaseOneDay(Date);
		}
		return Date;
	}
	clsDate DecreaseXDays(short DaysToSubtract) {
		return DecreaseXDays(*this, DaysToSubtract);
	}

	static clsDate DecreaseOneWeek(clsDate &Date)
	{
		for (short i = 1; i <= 7; i++)
		{
			Date = DecreaseOneDay(Date);
		}
		return Date;
	}
	clsDate DecreaseOneWeek() {
		return DecreaseOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(clsDate &Date, short WeeksToAdd)
	{
		for (short i = 1; i <= WeeksToAdd; i++)
		{
			Date = DecreaseOneWeek(Date);
		}
		return Date;
	}
	clsDate DecreaseDateByXWeeks(short WeeksToAdd) {
		return DecreaseDateByXWeeks(*this, WeeksToAdd);
	}

	static clsDate DecreaseOneMonth(clsDate &Date)
	{
		if (Date.Month == 1)
		{
			Date.Month = 12;
			Date.Year--;
		}
		else if (IsLastDayInMonth(Date) || (Date.Month == 3 && (Date.Day == 30 || Date.Day == 29)))
		{
			Date.Month--;
			short MonthDays = NumberOfDaysInAMonth(Date.Month, Date.Year);
			Date.Day = MonthDays;
		}
		else
			Date.Month--;
		return Date;
	}
	clsDate DecreaseOneMonth() {
		return DecreaseOneMonth(*this);
	}

	static clsDate DecreaseXMonths(clsDate& Date, short MonthsToDecrease)
	{
		for (short i = 1; i <= MonthsToDecrease; i++)
			Date = DecreaseOneMonth(Date);

		return Date;
	}
	clsDate DecreaseXMonths(short MonthsToDecrease) {
		return DecreaseXMonths(*this, MonthsToDecrease);
	}

	static clsDate DecreaseOneYear(clsDate& Date)
	{
		return DecreaseXMonths(Date, 12);
	}
	clsDate DecreaseOneYear() {
		return DecreaseOneYear(*this);
	}

	static clsDate DecreaseXYears(clsDate& Date, short YearsToDecrease)
	{
		for (short i = 1; i <= YearsToDecrease; i++)
			Date = DecreaseOneYear(Date);

		return Date;
	}
	clsDate DecreaseXYears(short YearsToDecrease) {
		return DecreaseXYears(*this, YearsToDecrease);
	}

	static clsDate DecreaseOneDecade(clsDate& Date)
	{
		return DecreaseXYears(Date, 10);
	}
	clsDate DecreaseOneDecade() {
		return DecreaseOneDecade(*this);
	}

	static clsDate DecreaseXDecades(clsDate& Date, short DecatesToDecrease)
	{
		for (short i = 1; i <= DecatesToDecrease; i++)
			Date = DecreaseOneDecade(Date);

		return Date;
	}
	clsDate DecreaseXDecades(short DecatesToDecrease) {
		return DecreaseXDecades(*this, DecatesToDecrease);
	}

	static clsDate DecreaseOneCentury(clsDate& Date)
	{
		return DecreaseXDecades(Date, 10);
	}
	clsDate DecreaseOneCentury()
	{
		return DecreaseOneCentury(*this);
	}

	static clsDate DecreaseXCentury(clsDate& Date, short CenturiesToDecrease)
	{
		for (short i = 1; i <= CenturiesToDecrease; i++)
			Date = DecreaseOneDecade(Date);

		return Date;
	}
	clsDate DecreaseXCentury(short CenturiesToDecrease) {
		return DecreaseXCentury(*this, CenturiesToDecrease);
	}

	static clsDate DecreaseOneMillennnium(clsDate& Date)
	{
		return DecreaseXCentury(Date, 10);
	}
	clsDate DecreaseOneMillennnium() {
		return DecreaseOneMillennnium(*this);
	}

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		int Days = 0;

		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			SwapDates(Date1, Date2);
		}
		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = AddOneDay(Date1);

		}
		return IncludeEndDay ? ++Days : Days;
	}
	int GetDifferenceInDays(clsDate& Date2, bool IncludeEndDay = false) {
		return GetDifferenceInDays(*this, Date2, IncludeEndDay);
	}

	static int CalculateMyAgeInDays(clsDate DateOfBirth, bool IncludeEndDay = false)
	{
		return GetDifferenceInDays(DateOfBirth, GetSystemDate(), IncludeEndDay);
	}

	static bool IsEndOfWeek(clsDate& Date)
	{
		if (DayName(DayOfWeekOrder(Date.Year, Date.Month, Date.Day)) == "Sat")
			return true;

		return false;
	}
	bool IsEndOfWeek() {
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate& Date)
	{
		string NameOfDay = DayName(DayOfWeekOrder(Date.Year, Date.Month, Date.Day));
		if (NameOfDay == "Fri" || NameOfDay == "Sat")
			return true;

		return false;
	}
	bool IsWeekEnd() {
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate& Date)
	{
		return !IsWeekEnd(Date);
	}
	bool IsBusinessDay() {
		return IsBusinessDay(*this);
	}

	static short DaysUntillTheEndOfweek(clsDate& Date)
	{
		return 6 - (DayOfWeekOrder(Date.Year, Date.Month, Date.Day));
	}
	short DaysUntillTheEndOfweek() {
		return DaysUntillTheEndOfweek(*this);
	}

	static short DaysUntillTheEndOfMonth(clsDate& Date)
	{
		return NumberOfDaysInAMonth(Date.Month, Date.Year) - Date.Day;
	}
	short DaysUntillTheEndOfMonth() {
		return DaysUntillTheEndOfMonth(*this);
	}

	static short DaysUntillTheEndOfYear(clsDate& Date)
	{
		short DaysFromTheBeginingOfTheYear = NumberOfDaysFromTheBeginingOfTheYear(Date.Day, Date.Month, Date.Year);
		return IsLeapYear(Date.Year) ? 366 - DaysFromTheBeginingOfTheYear : 365 - DaysFromTheBeginingOfTheYear;
	}
	short DaysUntillTheEndOfYear() {
		return DaysUntillTheEndOfYear(*this);
	}

	static short CalculateVacationDays(clsDate& DateFrom, clsDate& DateTo)
	{
		return CalculateBusinessDays(DateFrom, DateTo);
	}
	short CalculateVacationDays(clsDate& DateTo) {
		return CalculateVacationDays(*this, DateTo);
	}

	static clsDate CalculateVacationReturnDate(clsDate& Date, short VacationDays)
	{
		while (VacationDays > 0 || IsWeekEnd(Date))
		{
			if (IsBusinessDay(Date))
			{
				Date = AddOneDay(Date);
				VacationDays--;
			}
			else
				Date = AddOneDay(Date);
		}
		return Date;
	}
	clsDate CalculateVacationReturnDate(short VacationDays) {
		return CalculateVacationReturnDate(*this, VacationDays);
	}

	static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
	{
		short Days = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				Days++;
			DateFrom = AddOneDay(DateFrom);
		}
		return Days;
	}
};