
#include <iostream>
#include <string>

using namespace std;

string  findweekofthedate(int day, int month, int year){
    int N;
    N= day + 2 * month + 3 * (month + 1 ) / 5 + year + year / 4 - year / 100 + year / 400 + 1;
    int i = N % 7;
    switch(i){
        case 1: return "Monday";
        case 2: return "Tuesday";
        case 3: return "Wednesday";
        case 4: return "Thrusday";
        case 5: return "Friday";
        case 6: return "Saturday";  
        case 0: return "Sunday";

    }
}
int if_leap_year(int year){
    if(year % 4 == 0){
        if(year % 100 == 0){
            if (year % 400 == 0){
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }
    else return 0;
}
void initialize_the_calander(date* &head, int year){
        date* p = new date;
        head = p;
        temp = p;
        p->next = nullptr;
        p->Month = 1;
        p->month = "January";
        p->week_of_the_day = findweekofthedate(1,1,year);
        p->day = 1;
        for(int i = 2; i <= 31; i++){
            date* q = new date;
            temp->next = q;
            q->next = nullptr;
            q->Month = 1;
            q->month = "January";
            q->week_of_the_day = findweekofthedate(i,1,year);
            q->day = i;
            temp = q;
        }
        for(int i = 1; i <= 28 + if_leap_year(year); i++){
            date* q = new date;
            temp->next = q;
            q->next = nullptr;
            q->Month = 2;
            q->month = "Feburary";
            q->week_of_the_day = findweekofthedate(i,2,year);
            q->day = i;
            temp = q;
        for(int i = 1;i < 31; i++){
            date* q = new date;
            temp->next = q;
            q->next = nullptr;
            q->Month = 3;
            q->month = "March";
            q->week_of_the_day = findweekofthedate(i,3,year);
            q->day = i;
            temp = q;
        }
        for(int i = 1; i <= 30; i++){
            date* q = new date;
            temp->next = q;
            q->next = nullptr;
            q->Month = 4;
            q->month = "April";
            q->week_of_the_day = findweekofthedate(i,4,year);
            q->day = i;
            temp = q;
        }
        for(int i = 1; i <= 31; i++){
            date* q = new date;
            temp->next = q;
            q->next = nullptr;
            q->Month = 5;
            q->month = "May";
            q->week_of_the_day = findweekofthedate(i,5,year);
            q->day = i;
            temp = q;
        }
        for(int i = 1; i <= 30; i++){
            date* q = new date;
            temp->next = q;
            q->next = nullptr;
            q->Month = 6;
            q->month = "June";
            q->week_of_the_day = findweekofthedate(i,6,year);
            q->day = i;
            temp = q;
        }
        for(int i = 1; i <= 31; i++){
            date* q = new date;
            temp->next = q;
            q->next = nullptr;
            q->Month = 7;
            q->month = "July";
            q->week_of_the_day = findweekofthedate(i,7,year);
            q->day = i;
            temp = q;
        }
        for(int i = 1; i <= 31; i++){
            date* q = new date;
            temp->next = q;
            q->next = nullptr;
            q->Month = 8;
            q->month = "August";
            q->week_of_the_day = findweekofthedate(i,8,year);
            q->day = i;
            temp = q;
        }
        for(int i = 1; i <= 30; i++){
            date* q = new date;
            temp->next = q;
            q->next = nullptr;
            q->Month = 9;
            q->month = "September";
            q->week_of_the_day = findweekofthedate(i,9,year);
            q->day = i;
            temp = q;
        }
        for(int i = 1; i <= 31; i++){
            date* q = new date;
            temp->next = q;
            q->next = nullptr;
            q->Month = 10;
            q->month = "October";
            q->week_of_the_day = findweekofthedate(i,10,year);
            q->day = i;
            temp = q;
        }
        for(int i = 1; i <= 30; i++){
            date* q = new date;
            temp->next = q;
            q->next = nullptr;
            q->Month = 11;
            q->month = "November";
            q->week_of_the_day = findweekofthedate(i,11,year);
            q->day = i;
            temp = q;
        }
        for(int i = 1; i <= 31; i++){
            date* q = new date;
            temp->next = q;
            q->next = nullptr;
            q->Month = 12;
            q->month = "December";
            q->week_of_the_day = findweekofthedate(i,12,year);
            q->day = i;
            temp = q;
        }
}
//the above is the initial process
void end_of_the_day(date* &current){
    char input;
    cout<<"Are you sure end of today? Y/N";
    cout<<"Input Y for YES and N for No";
    while(true){
        cin>>input;
        if (input == 'Y'){
            current = current->next;
            return;
        }
        else if(input == 'N'){
            current = current;
            return;
        }
        else{
            cout<<"Invaid character input, please input again!";
        }
    }
}


void(date* head){
    processing = true;
    date *current_date = head;
    while(processing){
        cout<<"Choice the following function";
        cout<<"Input 1 for  expenses";
        cout<<"Input 2 for  revenue";
        cout<<"Input 3 for  automaic setting";
        cout<<"Input 4 for  edit past record";
        cout<<"Input 5 for  end_of_the_day";
        cout<<"Input 6 for  end_of_function";
        int i;
        cin>>i;
        switch(i){
            case(1):
                    break;
            case(2):
                    break;
            case(3):
                    break;
            case(4):
                    break;
            case(5):
                    break;
            case(6):
                    processing = false;
        }


    }
}
//meanwhile the above is function process
struct expenses{
        double entertainment;
        double transportation;
        double living_expenditure;
        double money_transfer;
        double settle_debt;
        double stocks;
        double fixed_expenditure;
        double rents;
        double other_expenditure;
};

struct revenue{
        double salary;
        double interest;
        double gain_from_stocks;
        double others_income;
};

struct date{
        int Month;
        string month;
        string week_of_the_day;
        int day;
        struct revenue ADD;
        struct expenditure MINUS;
        struct date* next;
}
int main(){
    date* head = nullptr;
    int year;
    initialize_the_calander(head, year);
}
