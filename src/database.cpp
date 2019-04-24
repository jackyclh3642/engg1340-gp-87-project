#include <iostream>
#include <string>
#include "database.h"

using namespace std;

istream& operator >> (istream& is, Entry& e){
    // Make a entry from record
    is >> e.account >> e.category >> e.amount;
    getline(is, e.remarks);
    e.remarks = e.remarks.substr(e.remarks.find_first_not_of(" "));
    return is;
}

ostream& operator << (ostream& os, const Entry& e){
    // Load from an output like the opertor >> to the entry struct
    os << e.account << " " << e.category << " " << e.amount << " " << e.remarks;
    return os;
}