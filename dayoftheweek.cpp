#include <iostream>
#include <string>

using namespace std;

string check_day_of_the_week(int day,int month, int year){
    int N;
    N = day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400 + 1;
    int i = N % 7 ;
    switch(i){
        case 1: return "Monday";
        case 2: return "Tuesday";
        case 3: return "Wednesday";
        case 4: return "Thursday";
        case 5: return "Friday";
        case 6: return "Saturday";
        case 0: return "Sunday";
    }

}


int main(){
    int day, month, year;
    cout<<"Please input day, month, year"<<endl;
    cin>>day>>month>>year;
    cout<<check_day_of_the_week(day, month, year);
    return 0;
    
}
