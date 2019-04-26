#include <iostream>
#include <string>
#include "database.h"

using namespace std;

DayRecords& operator << (DayRecords& dr, const Entry& e){
    // Insert an entry to the end of the list, preseving the order where the 
    // transactions are made
    dr.ExtendTransDynamic();
    dr.transactions[dr.size - 1] = e;
}

istream& operator >> (istream& is, Entry& e){
    // Make a entry from record
    is >> e.account >> e.category >> e.amount;
    getline(is, e.remarks);
    if (!e.remarks.empty())
        e.remarks = e.remarks.substr(e.remarks.find_first_not_of(" "));
    return is;
}

ostream& operator << (ostream& os, const Entry& e){
    // Load from an output like the opertor >> to the entry struct
    os << e.account << " " << e.category << " " << e.amount << " " << e.remarks;
    return os;
}


EnquiryResults& operator << (EnquiryResults& er, const EnquiryEntry& e){
    // Insert an entry to the end of the list, arranged by order of amount
    er.ExtendEntryDynamic();
    int index_insert = 0;
    if (er.eq.sort_by == -1)
        index_insert = er.size -1;
    else if (er.eq.sort_by == 0){
        for (;index_insert < er.size-1;index_insert++){
            if( (er.results[index_insert].record->account < e.record->account) ^ er.eq.ascending)
                break;
        }
    }
    else if (er.eq.sort_by == 1){
        for (;index_insert < er.size-1;index_insert++){
            if((er.results[index_insert].record->category < e.record->category) ^ er.eq.ascending)
                break;
        }
    }
    else if (er.eq.sort_by == 2){
        for (;index_insert < er.size-1;index_insert++){
            if((er.results[index_insert].record->amount < e.record->amount) ^ er.eq.ascending)
                break;
        }
    }
    for(int i = er.size-1; i > index_insert; i--){
        er.results[i] = er.results[i-1];
    }
    er.results[index_insert] = e;
    return er;
}

EnquiryResults& operator << (EnquiryResults& er, const Enquiry& e){
    delete [] er.results;
    er.eq =e;
    return er;
}

EnquiryResults& operator << (EnquiryResults& er, DayRecords& dr){
    // Use the DayRecords as the input to the enquiry
    EnquiryEntry ee = {dr.date, &dr, nullptr};
    for (int i = 0; i < dr.size; i++){
        if (dr.transactions[i].FitsEnquiry(er.eq)){
            ee.record = &dr.transactions[i];
            er << ee;
        }
    }
    return er;
}

istream& operator >> (istream& is, DayRecords& dr){
    // Read from a istream and save its entries to the DayRecords
    Entry er;
    is >> dr.date;
    int size;
    is >> size;
    for (int i = 0; i < size; i++){
        is >> er;
        dr << er;
    }
    return is;
}

ostream& operator << (std::ostream& os, const DayRecords& dr){
    // Output a DayRecords in a format that can be read (reseved) by >>
    os << dr.date << " " << dr.size << endl;
    for (int i = 0; i < dr.size; i++){
        os << dr.transactions[i] << endl;
    }
    return os;
}

istream& operator >> (istream& is, DaysDatabase& dd){
    // DaysDatabase equivalence for the above importing
    int year;
    is >> year;
    dd.InitDatabase(year);
    for (int i =0; i < dd.size; i++){
        is >> dd.days[i];
    }
    return is;
}

ostream& operator << (ostream& os, const DaysDatabase& dd){
    // DaysDatabase equivalence for the above exporting
    os << dd.year << endl;
    for (int i = 0; i < dd.size; i++){
        os << dd.days[i];
    }
    return os;
}