#include <iostream>
#include "date.h"

using namespace std;

int main(){
    cout<<"Please input day, month and year:"<<endl;
    Date d;
    cin >> d;
    cout << d << " is a " << d.WeekdayString() << endl;
    cout<<"Please input day, month and year:"<<endl;
    Date d2;
    cin >> d2;
    cout << d << " and " << d2 << " are " << (d==d2 ?"the same":"different")
        << endl;
    cout << d << (d < d2 ? "<" : (d > d2 ? ">" : "==")) << d2 << endl;
    return 0;
}