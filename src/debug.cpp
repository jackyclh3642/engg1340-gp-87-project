#include <iostream>
#include "calender.h"

using namespace std;

int main() {
    date d = {23, 4, 2019};
    // Assert Tuesday
    cout << ReturnWeekdayString(d) << endl;
    date i_d = {31, 4, 2019};
    // Assert illegal date
    cout << IsLegalDate(i_d) << endl;
    return 0;
}