#include <iostream>
#include <iomanip>
#include "date.h"

using namespace std;

int IsLeapYear(int year){
    if(year % 4 == 0){
        if(year % 100 == 0){
            if (year % 400 == 0){
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }
    else return 0;
}

istream& operator >> (istream& is, Date& d){
    // A operator >> override which allows using istream as direct input
    is >> d.day >> d.month >> d.year;
    return is;
}

ostream& operator << (ostream& os, const Date& d){
    // Treat the struct as dd/mm/yyyy when needed output
    os << d.day << " " << d.month << " " << d.year;
    return os;
}

bool operator == (const Date& a, const Date& b){
    // Compare day, month, year one by one and return as long as false
    return a.day == b.day and a.month == b.month and a.year == b.year;
}

bool operator != (const Date&a, const Date& b){
    // Operator != is the opposite of ==
    return !(a == b);
}

bool operator < (const Date&a, const Date& b){
    // Test if date a is before of date b
    if (a.year == b.year)
        if (a.month == b.month)
            return a.day < b.day;
        else
            return a.month < b.month;
    else
        return a.year < b.year;
}

bool operator > (const Date&a, const Date& b){
    // Operator > is basically a combined condition of < and ==
    return !(a < b) and a != b;
}