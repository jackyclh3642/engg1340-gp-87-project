#include <string>
#include "database.h"
#include "calendar.h"

struct Entry;
struct DayRecord;
struct RecordDatabase;

void FreeAllEntries(Entry *head){
    Entry *temp;
    while(head != nullptr){
        temp = head;
        head = head->next;
        delete temp;
    }
}

void FreeRecordDatabase(RecordDatabase rd){
    for (int i = 0; i<rd.size; i++){
        FreeAllEntries(rd.list[i].expenses);
        FreeAllEntries(rd.list[i].incomes);
    }
    delete [] rd.list;
}

void ExtendDatabase(RecordDatabase &rd){
    DayRecord * new_list = new DayRecord[rd.max_size + kSizeDefaultRate];
    for (int i = 0; i < rd.size; i++){
        new_list[i] = rd.list[i];
    }
    rd.list = new_list;
}

RecordDatabase InitEmptyDatabase(int max_size){
    DayRecord * l = new DayRecord[max_size];
    RecordDatabase r = {l, 0, max_size};
    return r;
}