#pragma once
#include <iostream>
#include <string>
#include "MyLib.h"
using namespace std;
#pragma warning (disable : 4996)

namespace Date
{
    enum enCompareDates { Before = -1, Equal, After };
    struct stDate
    {
        short Year = 0;
        short Month = 0;
        short Day = 0;
    };
    struct stDatePeriod
    {
        stDate StartDate;
        stDate EndDate;
    };

    bool IsLeapYear(short Year)
    {
        return Year % 400 == 0 ? true : Year % 100 == 0 ? false : Year % 4 == 0 ? true : false;
        //return (Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0;
    }

    short NumberOfDaysInAYear(short Year)
    {
        return IsLeapYear(Year) ? 366 : 365;
    }
    short NumberOfHoursInAYear(short Year)
    {
        return NumberOfDaysInAYear(Year) * 24;
    }
    int NumberOfMinsInAYear(short Year)
    {
        return NumberOfHoursInAYear(Year) * 60;
    }
    int NumberOfSecInAYear(short Year)
    {
        return NumberOfMinsInAYear(Year) * 60;
    }
    short NumberOfDaysInAMonth(short Month, short Year)
    {
        short Arr31Days[13] = { 30, 31, 30, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        return Month == 2 ? (IsLeapYear(Year) ? 29 : 28) : Arr31Days[Month];
    }

    string PrintDate(short Day, short Month, short Year)
    {
        return to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year);
    }
    string PrintDate(stDate Date)
    {
        return PrintDate(Date.Day, Date.Month, Date.Year);
    }

    short DayOfWeekOrder(short Year, short Month, short Day)
    {
        short a = (14 - Month) / 12;
        short y = Year - a;
        short m = Month + 12 * a - 2;

        return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }
    short DayOfWeekOrder(stDate Date)
    {
        return DayOfWeekOrder(Date.Year, Date.Month, Date.Day);
    }

    string DayName(short DayOrder)
    {
        string ArrDayNames[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
        return ArrDayNames[DayOrder];
    }
    string MonthName(short Month)
    {
        string ArrMonthName[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
        return ArrMonthName[Month - 1];
    }
    
    void PrintMonthCalender(short Year, short Month)
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
    void PrintYearCalender(short Year)
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

    short NumberOfDaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
    {
        short TotalDays = 0;

        for (short i = 1; i < Month; i++)
        {
            TotalDays += NumberOfDaysInAMonth(i, Year);
        }
        TotalDays += Day;
        return TotalDays;
    }
    stDate GetDateFromDayOrderInYear(short DayOrderInYear, short Year)
    {
        stDate Date;
        short RemainderDays = DayOrderInYear;
        short MonthDays = 0;

        Date.Year = Year;
        Date.Month = 1;

        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(Date.Month, Year);

            if (RemainderDays > MonthDays)
            {
                RemainderDays -= MonthDays;
                Date.Month++;
            }
            else
            {
                Date.Day = RemainderDays;
                break;
            }
        }
        return Date;
    }

    stDate ReadFullDate()
    {
        stDate Date;
        cout << "\nPlease Enter A Day: ";
        Date.Day = MyLib::ReadNumber(1, 31);

        cout << "Please Enter A Month: ";
        Date.Month = MyLib::ReadNumber(1, 12);

        cout << "Please Enter A Year: ";
        Date.Year = MyLib::ReadPositiveNumber(0);
        return Date;
    }
    stDatePeriod ReadFullPeriod()
    {
        stDatePeriod Period;
        cout << "\nEnter Start Date:";
        Period.StartDate = ReadFullDate();
        cout << "\nEnter End Date:";
        Period.EndDate = ReadFullDate();
        return Period;
    }

    bool IsDate1BeforeDate2(stDate Date1, stDate Date2)
    {
        return  (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ?
            true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
    }
    bool IsDate1EqualDate2(stDate Date1, stDate Date2)
    {
        return (Date1.Year == Date2.Year) && (Date1.Month == Date2.Month) && (Date1.Day == Date2.Day);
    }
    bool IsDate1AfterDate2(stDate Date1, stDate Date2)
    {
        return !IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2);
    }
    short CompareDates(stDate Date1, stDate Date2)
    {
        if (IsDate1BeforeDate2(Date1, Date2))
            return enCompareDates::Before;

        if (IsDate1EqualDate2(Date1, Date2))
            return enCompareDates::Equal;

        /*if (IsDate1AfterDate2(Date1, Date2))
            return enCompareDates::After;*/

        return enCompareDates::After;
    }

    bool IsItLastDayInMonth(stDate Date)
    {
        return Date.Day == NumberOfDaysInAMonth(Date.Month, Date.Year);
    }
    bool IsItLastMonthInTheYear(short Month)
    {
        return Month == 12;
    }
    bool IsItFirstDayInMonth(short Day)
    {
        return Day == 1;
    }
    bool IsItFirstMonthInTheYear(short Month)
    {
        return Month == 1;
    }

    void SwapDates(stDate& Date1, stDate& Date2) 
    {
        stDate TempDate;

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

    stDate GetSystemDate()
    {
        stDate Date;
        time_t t = time(0);
        tm* now = localtime(&t);
        Date.Year = now->tm_year + 1900;
        Date.Month = now->tm_mon + 1;
        Date.Day = now->tm_mday;
        return Date;
    }

    stDate IncreaseDateByOneDay(stDate Date)
    {
        if (IsItLastDayInMonth(Date))
        {
            if (IsItLastMonthInTheYear(Date.Month))
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
    stDate IncreaseDateByXDays(stDate Date, short DaysToAdd)
    {
        for (short i = 1; i <= DaysToAdd; i++)
        {
            Date = IncreaseDateByOneDay(Date);
        }
        return Date;
    }
    stDate IncreaseDateByOneWeek(stDate Date)
    {
        for (short i = 1; i <= 7; i++)
        {
            Date = IncreaseDateByOneDay(Date);
        }
        return Date;
    }
    stDate IncreaseDateByXWeeks(stDate Date, short WeeksToAdd)
    {
        for (short i = 1; i <= WeeksToAdd; i++)
        {
            Date = IncreaseDateByOneWeek(Date);
        }
        return Date;
    }
    stDate IncreaseDateByOneMonth(stDate Date)
    {
        if (IsItLastMonthInTheYear(Date.Month))
        {
            Date.Month = 1;
            Date.Year++;
        }
        else if (IsItLastDayInMonth(Date) || (Date.Month == 1 && (Date.Day == 30 || Date.Day == 29)))
        {
            short MonthDays = NumberOfDaysInAMonth(++Date.Month, Date.Year);
            if (MonthDays < Date.Day)
                Date.Day = MonthDays;
        }
        else
            Date.Month++;
        return Date;
    }
    stDate IncreaseDateByXMonths(stDate Date, short MonthsToAdd)
    {
        for (short i = 1; i <= MonthsToAdd; i++)
            Date = IncreaseDateByOneMonth(Date);

        return Date;
    }
    stDate IncreaseDateByOneYear(stDate Date)
    {
        Date.Year++;
        return Date;
    }
    stDate IncreaseDateByXYears(stDate Date, short YearsToAdd)
    {
        for (short i = 1; i <= YearsToAdd; i++)
            Date = IncreaseDateByOneYear(Date);

        return Date;
    }
    stDate IncreaseDateByXYearsFaster(stDate Date, short YearsToAdd)
    {
        Date.Year += YearsToAdd;
        return Date;
    }
    stDate IncreaseDateByOneDecade(stDate Date)
    {
        Date.Year += 10;
        return Date;
    }
    stDate IncreaseDateByXDecades(stDate Date, short DecatesToAdd)
    {
        for (short i = 1; i <= DecatesToAdd; i++)
            Date = IncreaseDateByOneDecade(Date);

        return Date;
    }
    stDate IncreaseDateByXDecadesFaster(stDate Date, short DecatesToAdd)
    {
        Date.Year += DecatesToAdd * 10;
        return Date;
    }
    stDate IncreaseDateByOneCentury(stDate Date)
    {
        Date.Year += 100;
        return Date;
    }
    stDate IncreaseDateByOneMillennnium(stDate Date)
    {
        Date.Year += 1000;
        return Date;
    }

    stDate DecreaseDateByOneDay(stDate Date)
    {
        if (IsItFirstDayInMonth(Date.Day))
        {
            if (IsItFirstMonthInTheYear(Date.Month))
            {
                Date.Year--;
                Date.Month = 12;
                Date.Day = 31;
            }
            else
            {
                short MonthDays = NumberOfDaysInAMonth(--Date.Month, Date.Year);
                Date.Day = MonthDays;
            }
        }
        else
            Date.Day--;

        return Date;
    }
    stDate DecreaseDateByXDays(stDate Date, short DaysToSubtract)
    {
        for (short i = 1; i <= DaysToSubtract; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }
        return Date;
    }
    stDate DecreaseDateByOneWeek(stDate Date)
    {
        for (short i = 1; i <= 7; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }
        return Date;
    }
    stDate DecreaseDateByXWeeks(stDate Date, short WeeksToAdd)
    {
        for (short i = 1; i <= WeeksToAdd; i++)
        {
            Date = DecreaseDateByOneWeek(Date);
        }
        return Date;
    }
    stDate DecreaseDateByOneMonth(stDate Date)
    {
        if (IsItFirstMonthInTheYear(Date.Month))
        {
            Date.Month = 12;
            Date.Year--;
        }
        else if (IsItLastDayInMonth(Date) || (Date.Month == 3 && (Date.Day == 30 || Date.Day == 29)))
        {
            short MonthDays = NumberOfDaysInAMonth(--Date.Month, Date.Year);
            Date.Day = MonthDays;
        }
        else
            Date.Month--;
        return Date;
    }
    stDate DecreaseDateByXMonths(stDate Date, short MonthsToAdd)
    {
        for (short i = 1; i <= MonthsToAdd; i++)
            Date = DecreaseDateByOneMonth(Date);

        return Date;
    }
    stDate DecreaseDateByOneYear(stDate Date)
    {
        Date.Year--;
        return Date;
    }
    stDate DecreaseDateByXYears(stDate Date, short YearsToAdd)
    {
        for (short i = 1; i <= YearsToAdd; i++)
            Date = DecreaseDateByOneYear(Date);

        return Date;
    }
    stDate DecreaseDateByXYearsFaster(stDate Date, short YearsToAdd)
    {
        Date.Year -= YearsToAdd;
        return Date;
    }
    stDate DecreaseDateByOneDecade(stDate Date)
    {
        Date.Year -= 10;
        return Date;
    }
    stDate DecreaseDateByXDecades(stDate Date, short DecatesToAdd)
    {
        for (short i = 1; i <= DecatesToAdd; i++)
            Date = DecreaseDateByOneDecade(Date);

        return Date;
    }
    stDate DecreaseDateByXDecadesFaster(stDate Date, short DecatesToAdd)
    {
        Date.Year -= DecatesToAdd * 10;
        return Date;
    }
    stDate DecreaseDateByOneCentury(stDate Date)
    {
        Date.Year -= 100;
        return Date;
    }
    stDate DecreaseDateByOneMillennnium(stDate Date)
    {
        Date.Year -= 1000;
        return Date;
    }

    int GetDifferenceInDays(stDate Date1, stDate Date2, bool IncludeEndDay = false)
    {
        int Days = 0;

        if (!IsDate1BeforeDate2(Date1, Date2))
        {
            SwapDates(Date1, Date2);
        }
        while (IsDate1BeforeDate2(Date1, Date2))
        {
            Days++;
            Date1 = IncreaseDateByOneDay(Date1);

        }
        return IncludeEndDay ? ++Days : Days;
    }

    bool IsEndOfWeek(stDate Date)
    {
        if (DayName(DayOfWeekOrder(Date)) == "Sat")
            return true;

        return false;
    }
    bool IsWeekEnd(stDate Date)
    {
        string NameOfDay = DayName(DayOfWeekOrder(Date));
        if (NameOfDay == "Fri" || NameOfDay == "Sat")
            return true;

        return false;
    }
    bool IsBusinessDay(stDate Date)
    {
        return !IsWeekEnd(Date);
    }

    short DaysUntillTheEndOfweek(stDate Date)
    {
        return 6 - (DayOfWeekOrder(Date));
    }
    short DaysUntillTheEndOfMonth(stDate Date)
    {
        return NumberOfDaysInAMonth(Date.Month, Date.Year) - Date.Day;
    }
    short DaysUntillTheEndOfYear(stDate Date)
    {
        short DaysFromTheBeginingOfTheYear = NumberOfDaysFromTheBeginingOfTheYear(Date.Day, Date.Month, Date.Year);
        return IsLeapYear(Date.Year) ? 366 - DaysFromTheBeginingOfTheYear : 365 - DaysFromTheBeginingOfTheYear;
    }

    short CalculateVacationDays(stDate DateFrom, stDate DateTo)
    {
        short VacationDays = 0;
        while (IsDate1BeforeDate2(DateFrom, DateTo))
        {
            if (IsBusinessDay(DateFrom))
                VacationDays++;

            DateFrom = IncreaseDateByOneDay(DateFrom);
        }
        return VacationDays;
    }
    stDate CalculateVacationReturnDate(stDate Date, short VacationDays)
    {
        while (VacationDays > 0 || IsWeekEnd(Date))
        {
            if (IsBusinessDay(Date))
            {
                Date = IncreaseDateByOneDay(Date);
                VacationDays--;
            }
            else
                Date = IncreaseDateByOneDay(Date);
        }
        return Date;
    }
    
    bool IsPeriodsOverlaped(stDatePeriod Period1, stDatePeriod Period2)
    {
        return !(CompareDates(Period1.StartDate, Period2.EndDate) == enCompareDates::After
            || CompareDates(Period1.EndDate, Period2.StartDate) == enCompareDates::Before);
    }
    int PeriodLengthInDays(stDatePeriod Period, bool IncludeEndDay = false)
    {
        return GetDifferenceInDays(Period.StartDate, Period.EndDate, IncludeEndDay);
    }
    bool IsDateWithinPeriod(stDatePeriod Period, stDate Date)
    {
        return !(CompareDates(Date, Period.StartDate) == enCompareDates::Before
            || CompareDates(Date, Period.EndDate) == enCompareDates::After);
    }
    short CalculateOverlapDays(stDatePeriod Period1, stDatePeriod Period2)
    {
        if (IsPeriodsOverlaped(Period1, Period2))
        {
            if (IsDateWithinPeriod(Period2, Period1.StartDate)
                && IsDateWithinPeriod(Period2, Period1.EndDate))
                return GetDifferenceInDays(Period1.StartDate, Period1.EndDate, true);

            else if (IsDateWithinPeriod(Period1, Period2.StartDate)
                && IsDateWithinPeriod(Period1, Period2.EndDate))
                return GetDifferenceInDays(Period2.StartDate, Period2.EndDate, true);

            else if ((CompareDates(Period1.StartDate, Period2.EndDate) == enCompareDates::Before
                || CompareDates(Period1.StartDate, Period2.EndDate) == enCompareDates::Equal)

                && CompareDates(Period1.EndDate, Period2.EndDate) == enCompareDates::After)
                return GetDifferenceInDays(Period1.StartDate, Period2.EndDate, true);

            else if ((CompareDates(Period1.EndDate, Period2.StartDate) == enCompareDates::After
                || CompareDates(Period1.EndDate, Period2.StartDate) == enCompareDates::Equal)

                && CompareDates(Period1.StartDate, Period2.StartDate) == enCompareDates::Before)
                return GetDifferenceInDays(Period1.EndDate, Period2.StartDate, true);
        }
        return 0;
    }

    bool IsValidDate(stDate Date)
    {
        return Date.Day > Date::NumberOfDaysInAMonth(Date.Month, Date.Year) ? false : true;
    }

    stDate StringToDate(string StringDate)
    {
        Date::stDate Date;
        vector <string> vDate = MyLib::SplitString(StringDate, "/");

        Date.Day = stoi(vDate[0]);
        Date.Month = stoi(vDate[1]);
        Date.Year = stoi(vDate[2]);

        return Date;
    }
    string DateToString(stDate Date)
    {
        return Date::PrintDate(Date);
    }
    /*string FormatDate(stDate Date, string DateFormat = "dd/mm/yyyy")
    {
        string strFormatDate = "";
        strFormatDate = MyLib::ReplaceWordInString(DateFormat, "dd", to_string(Date.Day));
        strFormatDate = MyLib::ReplaceWordInString(strFormatDate, "mm", to_string(Date.Month));
        strFormatDate = MyLib::ReplaceWordInString(strFormatDate, "yyyy", to_string(Date.Year));

        return strFormatDate;
    }*/
}