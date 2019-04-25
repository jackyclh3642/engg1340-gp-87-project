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
const int kNumCommands = 8;
const Command kCommandList[kNumCommands] = {{'a', "Add a new entry to today."}, {'e', "Edit an entry of today."},
    {'n', "Proceed to next day."}, {'j', "Jump to a specific day."}, {'s', "Save the current database."},
    {'d', "Delete an entry of today."}, {'u', "Set up automatic entries."}, {'q', "Save all and quit."}
};

string default_location = "";
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
        d.day = 0;
        d.month = 0;
        d.year = 0;
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
    int input;
    while (true){
        cout << endl << endl << "> ";
        cin >> input;
        if (input <= kMaxNumAccount and input > 0)
            return input -1;
        cout << "The number entered is not valid, please enter a valid account.";
    }
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
    int input;
    while (true){
        cout << endl << endl << "> ";
        cin >> input;
        if (input <= kMaxNumCategory and input > 0)
            return input -1;
        cout << "The number entered is not valid, please enter a valid category.";
    }
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
                fin.close();
                default_location = input;
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
        cout << "Please input a string less than 30 characters."<< endl;
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

void EditEntry(int i){
    Date d = (*db)[i].date;
    Enquiry eq = {d,d, -1, -1, -1, "", -1};
    EnquiryResults er = db->IquireFor(eq);
    if (er.size == 0)
        return;
    cout << er.Formatted() << endl << endl;
    int index;
    while (true){
        cout << "Input an index for editing:" << endl << "> ";
        cin >> index;
        if (index > 0 and index <= er.size)
            break;
        cout << "Please enter an appropriate index" << endl;
    }
    Entry& e = er[index];
    e.account = InputAccount(e.account);
    ClearScreen();
    e.category = InputCategory(e.category);
    ClearScreen();
    e.amount = InputAmount(e.amount);
    ClearScreen();
    cin.ignore(1);
    e.remarks = InputRemarks(e.remarks);
    
    er.FreeMemory();
}

void JumpDay(int&i){
    Date d;
    d = InputDate(db->year);
    i = db->FindDateIndex(d, 0, db->size);
}

void SaveDB(){
    string input = "N";
    if (!default_location.empty()){
        cout << "Save to '" << default_location << "'? (Y or N)" << endl;
        while (true){
            cin >> input;
            if (input == "Y" or input == "N")
                break;
            cout << "Please enter 'Y' or 'N'.";
        }
    }
    if (input == "N"){
        cout << "Enter a filename for saving the accounting database:" << endl;
        cin.ignore(1);
        getline(cin, default_location);
    }
    ofstream fou;
    fou.open(default_location);
    fou << (*db);
    fou.close();
}

void DeleteEntry(const int i){
    Date d = (*db)[i].date;
    Enquiry eq = {d,d, -1, -1, -1, "", -1};
    EnquiryResults er = db->IquireFor(eq);
    if (er.size == 0)
        return;
    cout << er.Formatted() << endl << endl;
    int index;
    while (true){
        cout << "Input an index for editing:" << endl << "> ";
        cin >> index;
        if (index > 0 and index <= er.size)
            break;
        cout << "Please enter an appropriate index"<< endl;
    }
    er.DeleteByIndex(index);
    er.FreeMemory();
}

void SetupAutomatic(int i){
    Date today = (*db)[i].date;
    cout << "At which day of the month would a recurring automatic entry (i.e. incomes or expenses) be set from " << today.Formatted() << "?" << endl;
    int input;
    while (true){
        cout << "> ";
        cin >> input;
        if (input <= 31 and input > 0)
            break;
        cout << "Please enter an appropriate day number of a month." << endl;
    }
    
    ClearScreen();
    
    Entry e;
    e.account = InputAccount(-1);
    ClearScreen();
    e.category = InputCategory(-1);
    ClearScreen();
    e.amount = InputAmount(0);
    ClearScreen();
    cin.ignore(1);
    e.remarks = InputRemarks("");
    
    int starting_month = (*db)[i].date.day < input ? today.month : today.month + 1;
    for (int j = starting_month; j < 13; j++){
        Date temp = {input, j, db->year};
        int temp_input = input;
        while(!temp.IsLegitDate()){
            cout << "Month " << kMonthString[j-1] << " does not have day " << temp_input << ". Please enter an appropriate one." << endl;
            cout << "> ";
            cin >> temp_input;
            temp.day = temp_input;
        }
        (*db)[temp] << e;
    }
}

int main(){
    int today_index = InitDatabaseForUser();
    char input;
    do{
        input = TodayAndInstructions(today_index);
        ClearScreen();
        switch(input){
            case 'a': AddEntry(today_index); break;
            case 'e': EditEntry(today_index); break;
            case 'n': ProceedDay(today_index); break;
            case 'j': JumpDay(today_index); break;
            case 's': SaveDB();break;
            case 'd': DeleteEntry(today_index);break;
            case 'u': SetupAutomatic(today_index);break;
            case 'q': SaveDB();break;
        }
        ClearScreen();
    } while (input != 'q');
    
    db->FreeDatabaseMemory();
    return 0;
}

