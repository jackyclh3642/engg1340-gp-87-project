#include <string>
#include "calender.h"

struct date;

int ReturnWeekdayInt(date d){
    // Return the weekday of the date given as [0-6] : Sunday - Saturday
    int n;
    n = d.day + 2 * d.month + 3 * (d.month + 1) / 5 + d.year + d.year / 4 -
        d.year / 100 + d.year / 400 + 1;
    return n % 7;
}

std::string WeekdayIntToString(int w){
    // Convert the interger for weekday to string
    switch(w){
        case 0: return "Sunday";
        case 1: return "Monday";
        case 2: return "Tuesday";
        case 3: return "Wednesday";
        case 4: return "Thrusday";
        case 5: return "Friday";
        case 6: return "Saturday";  
    }
}

std::string ReturnWeekdayString(date d){
    return WeekdayIntToString(ReturnWeekdayInt(d));
}

bool IsLeapYear(int year){
    // Return if the given year is leap year
    if(year % 4 == 0){
        if(year % 100 == 0){
            if (year % 400 == 0)
                return true;
            else
                return false;
        }
        else
            return true;
    }
    else return false;
}

bool IsLegalDate(date d){
    // Check if the date given is legal or not
    if (d.year < 0 or d.day <= 0 or d.day > 31 or d.month <= 0 or d.month > 12)
        return false;
    if (d.month == 2 and (d.day > (IsLeapYear(d.year) ? 29 : 28)))
        return false;
    if ((d.month + (d.month >=8)) % 2 == 0 and d.day > 30)
        return false;
    return true;
}