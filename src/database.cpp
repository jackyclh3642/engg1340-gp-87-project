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
    for (;index_insert < er.size-1;index_insert++){
        if(er.results[index_insert].record->amount < e.record->amount)
            break;
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