#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <iomanip>
#include <sstream>
#include "date.h"
#include "variables.h"

// The max width of a amount when printed in std::cout
const int kMaxAmountLength = 15;
// The corresponding string for sorting methods
const std::string kSortString[] = {"Account", "Category", "Amount"};

/**
 * Holds a mult-condition enquiry
 * Its conditions would be tested by entry and DayRecords
 */
struct Enquiry{
    Date start_date;
    // The start and end date are both inclusive
    Date end_date;
    int account;
    int category;
    int is_income;
    std::string search_string;
    int sort_by; // -1 no sorting, 0 = account, 1 = category, 2 = amount
    bool ascending;
    
    /*
    * Output the header of the enquiry
    * Such as
    * Enquiry for incomes from 01/01/2019 to 31/12/2019 by Cash
    */
    std::string Formatted(){
        std::string r = "Enquiry for";
        r+= is_income == -1 ? " records" : (is_income == 1 ? " incomes" : " expenses");
        r += start_date == end_date ? " in " + start_date.Formatted() : " from " +
            start_date.Formatted() + " to " + end_date.Formatted();
        r += account == -1 ? "" : " by " + kAccountStrings[account];
        r += category == -1 ? "" : " of " + kCategoryStrings[category];
        r += search_string.empty() ? "" : " with remarks \"" + search_string + "\"";
        r += sort_by == -1 ? "" : " sorted by " + kSortString[sort_by] + " in " +
            (ascending ? "Ascend" : "Descend");
        return r;
    }
};

/**
 * Hold the metadata of each singular entry
 * Is the basic unit of record within this system
 * Including accout, category, amount, remarks
 */
struct Entry{
    int account;
    int category;
    double amount;
    std::string remarks;
    
    /**
     * Check if the entry fit an enquiry requirements
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
         ss << std::setw(kRemarksLength) << remarks;
         return ss.str();
     }
};

// Overide the operators for easy file I/O functions (save and load)
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
     * Delete an entry by index within the transactions dynamic list
     */
    void DeleteByPointer(const Entry* e_ptr){
        Entry *temp = new Entry[--size];
        int offset = 0;
        for (int i = 0; i < size; i++){
            if (&transactions[i] == e_ptr)
                offset++;
            temp[i] = transactions[i+offset];
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
         ss <<std::setw(kRemarksLength) << "Remarks" << std::endl;
         ss << "----------------+----------------------+-----------------+--------------------------------"
            <<std::endl;
        for (int i = 0; i < (size-1); i++){
            ss << transactions[i].Formatted() << std::endl;
        }
        if (size > 0)
            ss << (transactions[size-1].Formatted());
        return ss.str();
    };
};

// Insert a entry record to a day's record
DayRecords& operator << (DayRecords& dr, const Entry& e);

/*
* Hold the metadata and the pointer to a entry and where the entry is from
* This is created when an enquiry found a hit result
*/
struct EnquiryEntry{
    Date date;
    DayRecords* day_records;
    Entry* record;
    
    /**
     * Include date in the output of presentation
     */
    std::string Formatted(){
        std::string r;
        r += date.Formatted() + " | " + (*record).Formatted();
        return r;
    }
};

// Define how to export and import a DayRecords (for save and load also)
std::istream& operator >> (std::istream& is, DayRecords& dr);
std::ostream& operator << (std::ostream& os, const DayRecords& dr);

/*
* Holds a dynamic list which gives the metadata (what requirements are searched)
* and results (what are found) for an enquiry
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
         ss << std::setw(kRemarksLength) << "Remarks" << std::endl;
         ss << "----+------------+-----------------+----------------------+-----------------+--------------------------------"
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
     * Return an entry by reference by index for editing (shown in the UI)
     */
    Entry& operator[] (const int index){
        return *(results[index-1].record);
    }
    
    /**
     * Delete a entry from corresponding DayRecords by index (shown in the UI)
     */
    void DeleteByIndex (const int index){
        results[index-1].day_records->DeleteByPointer(results[index-1].record);
    }
    
    /**
     * Free memory used by an enquiry records, since it contains a dynamic list
     */
    void FreeMemory(){
        delete [] results;
    }
};

// Operators for initing the Enquiry, inserting a success record, filtering a DayRecords
EnquiryResults& operator << (EnquiryResults& er, const EnquiryEntry& e);
EnquiryResults& operator << (EnquiryResults& er, const Enquiry& e);
EnquiryResults& operator << (EnquiryResults& er, DayRecords& dr);

/**
 * Hold all days recorded within the system in a dynamic list also
 * From 1/1 2/1 3/1 ... 31/12
 * With year variable to see if it is leap year or not
 * And each DaysDatabase only hold at most 1 year of records
 */
struct DaysDatabase{
    DayRecords *days;
    int year;
    int size;
    
    /*
    * Init the year database depends on the year
    */
    void InitDatabase(int y){
        year = y;
        size = (IsLeapYear(y) ? 366 : 365);
        days = new DayRecords[size];
        
        Date head = {1, 1, y};
        for (int i = 0; i < size; i++){
            days[i].date = head;
            days[i].transactions = nullptr;
            days[i].size = 0;
            head.day ++;
            if (!head.IsLegitDate()){
                head.day = 1;
                head.month++;
            }
        }
    }

    /*
    * Remove all memory used by the database, which is the days[] dyanmic itself, and
    * each transactions dynamic list in each DayRecords (365, 366)
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
	
	// Return a DayRecords when asking for a date in the database
	DayRecords& operator[](const Date d){
	    return days[FindDateIndex(d, 0, size)];
	}
	
	// Return a DayRecords when asking for a known integer, faster than asking 
	// for date, since, binary searches are not needed
	DayRecords& operator [](const int i){
	    return days[i];
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
	
	/**
	 * Return the latest index DayRecords with entrys
	 * For used when loaded a old DayRecords
	 */
    int GetLatestIndex(){
        int index = 0;
        for (int i = 0; i < size; i++){
            if (days[i].size > 0){
                index = i;
            }
        }
        return index;
    }
};

// These operators take care of real File/IO requirements, utilize all 
// DaysRecord, Entry's << and >> operator
std::istream& operator >> (std::istream& is, DaysDatabase& dd);
std::ostream& operator << (std::ostream& os, const DaysDatabase& dd);

#endif