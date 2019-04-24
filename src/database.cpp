#include <iostream>
#include <string>
#include "database.h"

using namespace std;

istream& operator >> (istream& is, Entry& e){
    // Make a entry from record
    is >> e.account >> e.category >> e.amount;
    getline(is, e.remarks);
    return is;
}

ostream& operator << (ostream& os, const Entry& e){
}