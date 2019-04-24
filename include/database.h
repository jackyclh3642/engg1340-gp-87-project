#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <iomanip>
#include "date.h"
#include "variables.h"

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
     
     /**
      * Output presentable string
      */
     std::string Formatted(){
         std::string r;
         r += kAccountStrings[account] + " | " + kCatagoryStrings[category] +
            " | " + std::to_string(amount) + " | " + remarks;
         return r;
     }
};

std::istream& operator >> (std::istream& is, Entry& e);
std::ostream& operator << (std::ostream& os, const Entry& e);

/**
 * Hold all entries within a given day in a dynamic list
 */
struct DayRecords{
    Date date;
    Entry *transactions;
    int size;

    /**
    * Extend the size of the transactions by 1
    */
    void ExtendTransDynamic(Entry* &transaction, int &size){
    	Entry *temp = new Entry[size + 1];
    	for(int i = 0; i < size; i++){
    		temp[i] = transaction[i];
    	}
    	delete [] transaction;
    	transaction = temp;
    }
};

/**
 * Hold all days recorded within the system in a dynamic list also
 */
struct DaysDatabase{
    DayRecords *days;
    int size;
    
    /*
    * Init the year database depends on the year
    */
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

    /*
    * Remove all memory used by the database
    */
    void FreeDatabaseMemory(){
    	// Remove the dynamic list under each days
    	for(int i = 0; i < size; i++){
    		delete [] days[i].transactions;
    	}
    	// Remove the database's days dynamic itself
    	delete[] days;
	}
	
	/*
	* Return the index of the date in the database, -1 if not found
	* Since days is a sorted dynamic list, binear search is used
	*/
	int FindDateIndex(Date d, int lower, int higher){
	    int mid = (lower + higher)/2;
	    Date d_2 = days[mid].date;
	    if (d_2 == d)
	        return mid;
        if (mid == lower)
            return -1;
        return FindDateIndex(d, d < d_2 ? lower : mid, d > d_2 ? higher : mid);
	}
};

#endif
