#include <string>

struct date {
    int day, month, year;
};

int ReturnWeekdayInt(date d);

std::string WeekdayIntToString(int w);

std::string ReturnWeekdayString(date d);

bool IsLeapYear(int year);

bool IsLegalDate(date d);