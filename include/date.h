#ifndef DATE_H
#define DATE_H
// Header guard preventing redefinition

#include <string>

// Const string list for int => string conversion of week day
const std::string kWeekString[7] = {"Sunday", "Monday", "Tuesday", "Wednesday",
    "Thursday", "Friday", "Saturday"};
const std::string kWeekAbbr[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

int IsLeapYear(int year);

struct Date {
    int day, month, year;
    
    /**
     * Output the day of week [0-6] => Sunday - Saturday
     */
    int WeekdayInt(){
        int d = day, y = year;
        // Algorithm from Michael Keith and Tom Craver used in Motola from 
        // Wikipeda
        return (d+=month<3?y--:y-2,23*month/9+d+4+y/4-y/100+y/400)%7;
    }
    /**
     * Output the exact wording of the day of week e.g. Sunday
     */
    std::string WeekdayString(){
        return kWeekString[WeekdayInt()];
    }
    /**
     * Output the abbreviation of the day of week e.g. Sun
     */
     std::string WeekdayAbbr(){
         return kWeekString[WeekdayInt()];
     }
    
    bool IsLegitDate(){
        // Check if the Date given is legal or not
        if (year < 1900 or day <= 0 or day > 31 or month <= 0 or month > 12)
            return false;
        if (month == 2 and (day > (IsLeapYear(year) ? 29 : 28)))
            return false;
        if ((month + (month >=8)) % 2 == 0 and day > 30)
            return false;
        return true;
    }
};

std::istream& operator >> (std::istream& is, Date& d);
std::ostream& operator << (std::ostream& os, const Date& d);

bool operator == (const Date& a, const Date& b);
bool operator != (const Date& a, const Date& b);
bool operator < (const Date&a, const Date& b);
bool operator > (const Date&a, const Date& b);

#endif