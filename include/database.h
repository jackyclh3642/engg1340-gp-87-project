#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "date.h"

/**
 * Hold the metadata of each singular entry
 */
struct Entry{
    int account;
    int category;
    double amount;
    std::string remarks;
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
    int max_size;
};

#endif