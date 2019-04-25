#include <iostream>
#include "date.h"
#include "database.h"
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int kMaxCommandLength = 30;
const int kNumCommands = 3;
const string kCommandList[kNumCommands] = {"Add a new entry to today.","Edit today's records", "Proceed to next day."};

DaysDatabase* db = new DaysDatabase;

void ClearScreen(){
    for (int i = 0; i < 10; i++){
        cout << endl;
    }
}

Date InputDate(int year){
    Date d;
    while(true){
        if (year != -1){
            cout << "Please enter a date in (d)d/(m)m format: e.g. 31/8 for 31st of August" << endl;
            d.year = year;
            scanf("%d/%d",&d.day,&d.month);
        }
        else{
            cout << "Please enter a date in (d)d/(m)m/yyyy: e.g. 31/8/2019 for 31st of August 2019" << endl;
            scanf("%d/%d/%d", &d.day, &d.month, &d.year);
        }
        if (d.IsLegitDate())
            return d;
        cout << "The input date is not legit, please enter a new one:" << endl;
    }
}

int InitDatabaseForUser(){
    string input;
    Date d;
    ClearScreen();
    while (true){
        cout << "Enter 'new' for new accounting year, or the filename of a saved year"
            << " to load the records." << endl;
        getline(cin, input);
        if (input == "new"){
            ClearScreen();
            cout << "What is the date for the first records? (e.g. today)" << endl;
            d = InputDate(-1);
            db->InitDatabase(d.year);
            return db->FindDateIndex(d, 0, db->size);
        }
        else {
            ifstream fin;
            fin.open(input);
            if (fin.good()){
                fin >> (*db);
                int index = db->GetLatestIndex();
                ClearScreen();
                cout << "Loaded the accounting records for " << db->year << ", and showing last recorded day." << endl << endl;
                return index;
            }
            else{
                ClearScreen();
                cout << "File '" << input << "' cannot be found or unaccessible." << endl;
            }
        }
    }
}

int TodayAndInstructions(int i){

    cout << (*db)[i].Formatted() << endl << endl;
    
    cout << "Command List:"<<endl;
    for (int i = 0; i < kNumCommands; i++){
        cout << right << setw(3) << i+1 << ": " << setw(kMaxCommandLength) <<left << kCommandList[i] << " ";
        if (((i+1)%3 == 0) and (i+1) != kNumCommands)
            cout << endl;
    }
    
    int input;
    cout << endl << endl<< "> ";
    cin >> input;
}

int main(){
    int today_index = InitDatabaseForUser();
    int input;
    do{
        ClearScreen();
        input = TodayAndInstructions(today_index);
    } while (input != -1);
    Date start = {1, 1, 2019};
    Date end = {1, 12, 2019};
    Enquiry all = {start, end, -1, -1, -1, "", -1, false};
    EnquiryResults er = db->IquireFor(all);
    cout << er.Formatted() << endl;
}
