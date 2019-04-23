#include <iostream>
#include "calendar.h"
#include "database.h"

using namespace std;

int main() {
    Date d = {23, 4, 2019};
    // Assert Tuesday
    cout << ReturnWeekdayString(d) << endl;
    Date i_d = {31, 4, 2019};
    // Assert illegal Date
    cout << IsLegalDate(i_d) << endl;
    Date d_2 = {23, 4, 2019};
    // Assert same Date
    cout << IsSameDates(d, d_2) << endl;
    Date d_3 = {1, 1, 1900};
    // Assert 01/01/2019
    cout << FormatDateString(d_3) << endl;
    
    cout << AIsEarlierThanB(d, d_3) << endl;
    
    RecordDatabase db = InitEmptyDatabase(50);
    
    return 0;
}