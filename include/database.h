#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <iomanip>
#include <sstream>
#include "date.h"
#include "variables.h"

const int kMaxAmountLength = 10;

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
    
    /*
    * Output the header of the enquiry
    */
    std::string Formatted(){
        std::string r = "Enquiry for";
        r+= is_income == -1 ? " records" : (is_income == 1 ? " incomes" : " expenses");
        r += start_date == end_date ? " in " + start_date.Formatted() : " from " +
            start_date.Formatted() + " to " + end_date.Formatted();
        r += account == -1 ? "" : " by " + kAccountStrings[account];
        r += category == -1 ? "" : " of " + kCategoryStrings[category];
        r += search_string.empty() ? "" : " with remarks \"" + search_string + "\"";
        return r;
    }
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
         std::stringstream ss;
         ss << std::setw(kAccountLength) << kAccountStrings[account] << " | ";
         ss << std::setw(kCategoryLength) << kCategoryStrings[category] << " | ";
         ss << std::setw(kMaxAmountLength);
         ss << std::fixed << std::setprecision(2) << amount << " | ";
         ss << remarks;
         return ss.str();
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
    void ExtendTransDynamic(){
    	Entry *temp = new Entry[++size];
    	for(int i = 0; i < (size-1); i++){
    		temp[i] = transactions[i];
    	}
    	delete [] transactions;
    	transactions = temp;
    }
    
    /**
     * Output presentable day summary
     */
    std::string Formatted(){
        std::stringstream ss;
        ss << "Date: " << date.Formatted() << " (" << date.WeekdayString() 
            << ")" << std::endl;
         ss << std::setw(kAccountLength) << "Account" << " | ";
         ss << std::setw(kCategoryLength) << "Category" << " | ";
         ss << std::setw(kMaxAmountLength) << "Amount" << " | ";
         ss << "Remarks" << std::endl;
         ss << "----------------+----------------------+------------+-----------------------"
            <<std::endl;
        for (int i = 0; i < (size-1); i++){
            ss << transactions[i].Formatted() << std::endl;
        }
        if (size > 0)
            ss << (transactions[size-1].Formatted());
        return ss.str();
    };
};

DayRecords& operator << (DayRecords& dr, const Entry& e);

/*
* Hold the metadata and the pointer to a entry which is a enquiry result
*/
struct EnquiryEntry{
    Date date;
    Entry* record;
    
    /**
     * Include date in the output
     */
    std::string Formatted(){
        std::string r;
        r += date.Formatted() + " | " + (*record).Formatted();
        return r;
    }
};


/*
* Holds a dynamic list which gives the metadata and results for an enquiry
*/
struct EnquiryResults{
    Enquiry eq;
    EnquiryEntry *results;
    int size;
    
    /**
    * Extend the size of the enquiry entry by 1
    */
    void ExtendEntryDynamic(){
    	EnquiryEntry *temp = new EnquiryEntry[++size];
    	for(int i = 0; i < (size-1); i++){
    		temp[i] = results[i];
    	}
    	delete [] results;
    	results = temp;
    }
    
    /*
    * Output in a table format with index
    */
    std::string Formatted(){
        std::stringstream ss;
        ss << eq.Formatted() << std::endl;
        ss << std::setw(kIndexLength) << "i" << " | ";
        ss << std::setw(10) << "Date" << " | ";
         ss << std::setw(kAccountLength) << "Account" << " | ";
         ss << std::setw(kCategoryLength) << "Category" << " | ";
         ss << std::setw(kMaxAmountLength) << "Amount" << " | ";
         ss << "Remarks" << std::endl;
         ss << "----+------------+-----------------+----------------------+------------+-----------------------"
            <<std::endl;
        for (int i = 0; i < size-1; i++){
            ss << std::setw(kIndexLength) << i+1 << " | "
                << results[i].Formatted() << std::endl;
        }
        if (size > 0)
            ss << std::setw(kIndexLength) << size << " | " << results[size-1].Formatted();
        return ss.str();
    }
    
    /**
     * Sum up all the amount of the enquiry entries
     */
    double Sum(){
        double sum = 0;
        for (int i = 0; i < size; i++){
            sum += results[i].record->amount;
        }
        return sum;
    }
    
    /**
     * Return an entry by index for editing
     */
     
     
    Entry& operator[] (const int index){
        std::cout << results[index-1].record << std::endl;
        return *(results[index-1].record);
    }
};

EnquiryResults& operator << (EnquiryResults& er, const EnquiryEntry& e);
EnquiryResults& operator << (EnquiryResults& er, const Enquiry& e);
EnquiryResults& operator << (EnquiryResults& er, const DayRecords& dr);

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
	
	/*
	* Return the DayRecords for manipulation by date, assume legit date
	*/
	DayRecords& FindDateRecords(Date d){
	    return days[FindDateIndex(d, 0, size)];
	}
	
	/*
	* Search for all hits of an equiry and return a pointer to a EnquiryResults
	*/
	EnquiryResults IquireFor(const Enquiry e){
	    EnquiryResults er = {e, nullptr, 0};
	    int index = FindDateIndex(e.start_date, 0, size);
	    for (; (index < size) and (days[index].date < e.end_date) or (days[index].date == e.end_date); index++){
	        er << days[index];
	    }
	    return er;
	}
};

#endif
