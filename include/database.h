#include <string>
#include "calendar.h"

const int kSizeDefaultRate = 30;

/**
 * Hold a single transaction entry
 * 
 * Also serves as a linked list, but no sorting algorithm is needed, but will
 * have filtering, summing, counting algorithm
 */
struct Entry{
    int account;
    int category;
    double amount;
    std::string comment;
    Entry *next;
};

/**
 * Hold a day's total expenses and incomes, which are both linked list
 *
 * Will be placed withing a dynamic list, sorted, with binary search and
 * inserting (would not be significant, assume everyday is added to the list
 * in order in the first place)
 */
struct DayRecord{
    Date date;
    Entry *expenses;
    Entry *incomes;
};

/**
 * This is a structure which holds the dynamic list and the int number of 
 * records and maximum number of the dynamic list
 * 
 * Should have function that free all memory, convert to string for output file
 * extend to longer dynamic list, find, filter, sum, and api for all
 * functions in Entry and DayRecord
 */
struct RecordDatabase{
    DayRecord *list;
    int size;
    int max_size;
};

void FreeAllEntries(Entry *head);
void FreeRecordDatabase(RecordDatabase rd);
void ExtendDatabase(RecordDatabase &rd);
RecordDatabase InitEmptyDatabase(int max_size);