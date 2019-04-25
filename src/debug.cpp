#include <iostream>
#include "date.h"
#include "database.h"
#include <fstream>
#include <iomanip>
#include <string>
#include "variables.h"

using namespace std;

struct Command{
    char key;
    string desc;
};

const int kMaxCommandLength = 30;
const int kNumCommands = 3;
const Command kCommandList[kNumCommands] = {{'a', "Add a new entry to today."}, {'e', "Edit an entry of today."},
    {'n', "Proceed to next day."}
};

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
            cout << "> ";
            d.year = year;
            scanf("%d/%d",&d.day,&d.month);
        }
        else{
            cout << "Please enter a date in (d)d/(m)m/yyyy: e.g. 31/8/2019 for 31st of August 2019" << endl;
            cout << "> ";
            scanf("%d/%d/%d", &d.day, &d.month, &d.year);
        }
        if (d.IsLegitDate())
            return d;
        cout << "The input date is not legit, please enter a new one:" << endl;
    }
}

int InputAccount(int old){
    cout << "Input the account infomration for the entry: ";
    if (old != -1)
        cout << "[" << kAccountStrings[old] << "]";
    cout << endl << endl;
    cout << "List of Accounts:"<<endl;
    for (int i = 0; i < kMaxNumAccount; i++){
        cout << right << setw(3) << i+1 << ": " << setw(kAccountLength) <<left << kAccountStrings[i] << " ";
        if (((i+1)%3 == 0) and (i+1) != kMaxNumAccount)
            cout << endl;
    }
    cout << endl << endl << "> ";
    int input;
    cin >> input;
    return input - 1;
}

int InputCategory(int old){
    cout << "Input the category information for the entry: "; 
    if (old != -1)
        cout << "[" << kCategoryStrings[old] << "]";
    cout << endl <<endl;
    cout << "List of Categorys:" << endl;
    for (int i = 0; i < kMaxNumCategory; i++){
        cout << right << setw(3) << i+1 << ": " << setw(kCategoryLength) <<left << kCategoryStrings[i] << " ";
        if (((i+1)%3 == 0) and (i+1) != kMaxNumCategory)
            cout << endl;
    }
    cout << endl << endl << "> ";
    int input;
    cin >> input;
    return input -1;
}

int InitDatabaseForUser(){
    string input;
    Date d;
    ClearScreen();
    while (true){
        cout << "Enter 'new' for new accounting year, or the filename of a saved year"
            << " to load the records." << endl;
        cout << "> ";
        getline(cin, input);
        if (input == "new"){
            ClearScreen();
            cout << "What is the date for the first records? (e.g. today)" << endl;
            d = InputDate(-1);
            db->InitDatabase(d.year);
            ClearScreen();
            cout << "Initialized a new database for " << d.year << "." << endl;
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

char TodayAndInstructions(int i){

    cout << (*db)[i].Formatted() << endl << endl;
    
    cout << "Command List:"<<endl;
    for (int i = 0; i < kNumCommands; i++){
        cout << right << setw(3) << kCommandList[i].key << ": " << setw(kMaxCommandLength) <<left << kCommandList[i].desc << " ";
        if (((i+1)%3 == 0) and (i+1) != kNumCommands)
            cout << endl;
    }
    
    char input;
    cout << endl << endl<< "> ";
    cin >> input;
    return input;
}

void ProceedDay(int& i){
    if (i < (db->size-1))
        i++;
    else
        cout << "Cannot proceed to next year, please init a new database for next year." << endl;
}

float InputAmount(float old){
    cout << "Input the amount of the transaction, negative for expenses: ";
    if (old != 0)
        cout << "[" << old << "]" << endl;
    cout << endl << "> ";
    double a;
    cin >> a;
    return a;
}

string InputRemarks(string old){
    cout << "Input the remarks for this entry, with max length 30 characters: ";
    if (!old.empty())
        cout << "[" << old << "]" << endl;
    cout << endl << "> ";
    string input;
    while(true){
        getline(cin, input);
        if (input.length() < 30)
            return input;
        cout << "Please input a string less than 30 characters.";
    }
}

void AddEntry(int i){
    Entry e;
    e.account = InputAccount(-1);
    ClearScreen();
    e.category = InputCategory(-1);
    ClearScreen();
    e.amount = InputAmount(0);
    ClearScreen();
    cin.ignore(1);
    e.remarks = InputRemarks("");
    (*db)[i] << e;
}

int main(){
    int today_index = InitDatabaseForUser();
    char input;
    do{
        input = TodayAndInstructions(today_index);
        ClearScreen();
        switch(input){
            case 'a': AddEntry(today_index); break;
            case 'n': ProceedDay(today_index); break;
        }
    } while (input != -1);
    Date start = {1, 1, 2019};
    Date end = {1, 12, 2019};
    Enquiry all = {start, end, -1, -1, -1, "", -1, false};
    EnquiryResults er = db->IquireFor(all);
    cout << er.Formatted() << endl;
}
