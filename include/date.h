#ifndef DATE_H
#define DATE_H
// Header guard preventing redefinition

#include <string>

// Const string list for int => string conversion of week day
const std::string kWeekString[7] = {"Sunday", "Monday", "Tuesday", "Wednesday",
    "Thursday", "Friday", "Saturday"};
const std::string kWeekAbbr[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

// Const string list for int => string conversion of month
const std::string kMonthString[12] = {"January", "Febraray", "March",
    "April", "May", "June", "July", "August", "September", "October", 
    "November", "December"};

// Declared function with definition in cpp file
int IsLeapYear(int year);

/*
* A struct stores a date, and contain member methods for comparing and manipulating date
*/
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
    
    /**
    * Output presentable string 01/01/2019
    */
    std::string Formatted(){
        std::string r;
        r += (day < 10 ? "0" : "")  + std::to_string(day) + '/' +
            (month < 10 ? "0" : "") + std::to_string(month) + '/' + 
            std::to_string(year);
        return r;
    }
    
    /**
     * Return the maximum number of day given the day
     */
    int LastDayInMonth(){
        if (month == 2)
            return IsLeapYear(year) ? 29 : 28;
        if ((month + (month >=8)) % 2 == 0)
            return 30;
        return 31;
    }
    
    /**
     * Check if the date is a legit (possible in a calender)
     */
    bool IsLegitDate(){
        // Check if the Date given is legal or not
        if (year < 1900 or day <= 0 or day > 31 or month <= 0 or month > 12)
            return false;
        if (day > LastDayInMonth())
            return false;
        return true;
    }
};

// For inputing and outputing date in raw format for FileI/O
std::istream& operator >> (std::istream& is, Date& d);
std::ostream& operator << (std::ostream& os, const Date& d);

// Overload comparing operator for easiler date comparison
bool operator == (const Date& a, const Date& b);
bool operator != (const Date& a, const Date& b);
bool operator < (const Date&a, const Date& b);
bool operator > (const Date&a, const Date& b);

#endif
