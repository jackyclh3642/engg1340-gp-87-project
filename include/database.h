#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "date.h"

/**
 * Holds a mult-condition enquiry
 */
struct Enquiry{
    Date start_date;
    // The start and end date are both inclusive
    Date end_date;
    int account;
    int category;
    int is_income;
    std::string search_string;
};

/**
 * Hold the metadata of each singular entry
 */
struct Entry{
    int account;
    int category;
    double amount;
    std::string remarks;
    
    /**
     * Check if the entry fit enquiry requirements
     */
     bool FitsEnquiry(Enquiry e){
        if (e.account != -1)
            if (account != e.account)
                return false;
        if (e.category != -1)
            if (category != e.category)
                return false;
        if (e.is_income != -1)
            if ((amount > 0) != e.is_income)
                return false;
        if (e.search_string != "")
            if (remarks.find(e.search_string) == std::string::npos)
                return false;
        return true;
     }
};

/**
 * Hold all entries within a given day in a dynamic list
 */
struct DayRecords{
    Date date;
    Entry *transactions;
    int size;
    int max_size;
};

/**
 * Hold all days recorded within the system in a dynamic list also
 */
struct DaysDatabase{
    DayRecords *days;
    int size;
    
    void InitDatabase(int year){
        size = (IsLeapYear(year) ? 366 : 365);
        days = new DayRecords[size];
        
        Date head = {1, 1, year};
        for (int i = 0; i < size; i++){
            days[i].date = head;
            head.day ++;
            if (!head.IsLegitDate()){
                head.day = 1;
                head.month++;
            }
        }
    }
};

#endif