#pragma once
#include "clsDate.h"
class clsPeriod
{
public:
    clsDate StartDate;
    clsDate EndDate;

    clsPeriod(clsDate StartDate, clsDate EndDate)
    {
        this->StartDate = StartDate;
        this->EndDate = EndDate;
    }

    static bool IsPeriodsOverlaped(clsPeriod Period1, clsPeriod Period2)
    {
        return !(clsDate::CompareDates(Period1.StartDate, Period2.EndDate) == clsDate::enCompareDates::After
            || clsDate::CompareDates(Period1.EndDate, Period2.StartDate) == clsDate::enCompareDates::Before);
    }
    bool IsPeriodsOverlaped(clsPeriod Period2) {
        return IsPeriodsOverlaped(*this, Period2);
    }

    static int PeriodLengthInDays(clsPeriod Period, bool IncludeEndDay = false)
    {
        return clsDate::GetDifferenceInDays(Period.StartDate, Period.EndDate, IncludeEndDay);
    }
    int PeriodLengthInDays(bool IncludeEndDay = false) {
        return PeriodLengthInDays(*this, IncludeEndDay);
    }

    static bool IsDateWithinPeriod(clsPeriod& Period, clsDate& Date)
    {
        return !(clsDate::CompareDates(Date, Period.StartDate) == clsDate::enCompareDates::Before
            || clsDate::CompareDates(Date, Period.EndDate) == clsDate::enCompareDates::After);
    }
    bool IsDateWithinPeriod(clsDate Date) {
        return IsDateWithinPeriod(*this, Date);
    }

    static short CalculateOverlapDays(clsPeriod Period1, clsPeriod Period2)
    {
        if (IsPeriodsOverlaped(Period1, Period2))
        {
            if (IsDateWithinPeriod(Period2, Period1.StartDate)
                && IsDateWithinPeriod(Period2, Period1.EndDate))
                return clsDate::GetDifferenceInDays(Period1.StartDate, Period1.EndDate, true);

            else if (IsDateWithinPeriod(Period1, Period2.StartDate)
                && IsDateWithinPeriod(Period1, Period2.EndDate))
                return clsDate::GetDifferenceInDays(Period2.StartDate, Period2.EndDate, true);

            else if ((clsDate::CompareDates(Period1.StartDate, Period2.EndDate) == clsDate::enCompareDates::Before
                || clsDate::CompareDates(Period1.StartDate, Period2.EndDate) == clsDate::enCompareDates::Equal)

                && clsDate::CompareDates(Period1.EndDate, Period2.EndDate) == clsDate::enCompareDates::After)
                return clsDate::GetDifferenceInDays(Period1.StartDate, Period2.EndDate, true);

            else if ((clsDate::CompareDates(Period1.EndDate, Period2.StartDate) == clsDate::enCompareDates::After
                || clsDate::CompareDates(Period1.EndDate, Period2.StartDate) == clsDate::enCompareDates::Equal)

                && clsDate::CompareDates(Period1.StartDate, Period2.StartDate) == clsDate::enCompareDates::Before)
                return clsDate::GetDifferenceInDays(Period1.EndDate, Period2.StartDate, true);
        }
        return 0;
    }
    short CalculateOverlapDays(clsPeriod Period2) {
        return CalculateOverlapDays(*this, Period2);
    }

    void Print()
    {
        cout << "Period Start: ";
        StartDate.Print();

        cout << "Period End: ";
        EndDate.Print();

    }
};

