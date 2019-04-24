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
    /**
    DaysDatabase dd;
    dd.InitDatabase(2019);
    **/
    /** Test for valid dates
    for (int i = 0; i < dd.size; i++){
        cout << dd.days[i].date.Formatted() << " ";
    }
    Entry trans;
    cin >> trans;
    cout << "Enter a day, month, year" << endl;
    Date d;
    cin >> d;
    cout << "It is the " << dd.FindDateIndex(d, 0, dd.size) << " day of " << d.year << endl;
    **/
    /**
    Date d;
    cin >> d;
    // This two
    dd.FindDateRecords(d) << trans;
    cout << dd.FindDateRecords(d).Formatted() << endl;
    return 0;
    **/
    /**
    Entry trans[5];
    Date d = {1, 1, 2019};
    Enquiry er = {d, d, 0 , 0, 1, "Something"};
    cout << er.Formatted() << endl;
    EnquiryResults eq_r = {er, nullptr, 0};
    for (int i = 0; i < 3; i++){
        cin >> trans[i];
        EnquiryEntry e = {d, &trans[i]};
        eq_r << e;
    }
    cout << eq_r.Formatted() << endl;
    **/
    DaysDatabase dd;
    Date start = {1, 1, 2019};
    Date end = {1, 12, 2019};
    dd.InitDatabase(2019);
    for (int i = 0; i < 2; i++){
        Date d;
        cout << "Input a date:" << endl;
        cin >> d;
        cout << "Input a entry:" << endl;
        Entry e;
        cin >> e;
        dd.FindDateRecords(d) << e;
    }
    Enquiry all = {start, end, -1, -1, -1, ""};
    EnquiryResults er = dd.IquireFor(all);
    cout << er.Formatted() << endl;
    cout << "Input a changing index:" << endl;
    int index;
    cin >> index;
    Entry &editing = er[index];
    cout << &editing << endl;
    cout << "Editing:" << endl << editing.Formatted() << endl;
    cin >> editing;
    er = dd.IquireFor(all);
    cout << er.Formatted() << endl;
}
