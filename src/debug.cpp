#include <iostream>
#include "date.h"
#include "database.h"

using namespace std;

int main(){
    /**
    cout<<"Please input day, month and year:"<<endl;
    Date d;
    cin >> d;
    cout << d << " is a " << d.WeekdayString() << endl;
    cout << d << " is a " << (d.IsLegitDate() ? "legit" : "not legit") << endl; 
    cout<<"Please input day, month and year:"<<endl;
    Date d2;
    cin >> d2;
    cout << d << " and " << d2 << " are " << (d==d2 ?"the same":"different")
        << endl;
    cout << d << (d < d2 ? "<" : (d > d2 ? ">" : "==")) << d2 << endl;
    **/
    
    DaysDatabase dd;
    dd.InitDatabase(2019);
    /** Test for valid dates
    for (int i = 0; i < dd.size; i++){
        cout << dd.days[i].date.Formatted() << " ";
    }
    **/
    Entry trans;
    cin >> trans;
    /**
    cout << "Enter a day, month, year" << endl;
    Date d;
    cin >> d;
    cout << "It is the " << dd.FindDateIndex(d, 0, dd.size) << " day of " << d.year << endl;
    **/
    dd.days[0] << trans;
    cout << dd.days[0].Formatted() << endl;
    return 0;
}