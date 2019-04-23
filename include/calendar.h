#ifndef CALENDER_H
#define CALENDER_H

// This is a header guard

#include <string>

struct Date {
    int day, month, year;
};

int ReturnWeekdayInt(Date d);

std::string WeekdayIntToString(int w);

std::string ReturnWeekdayString(Date d);

bool IsLeapYear(int year);

bool IsLegalDate(Date d);

bool IsSameDates(Date a, Date b);

std::string FormatDateString(Date d);

bool AIsEarlierThanB(Date a, Date b);

#endif