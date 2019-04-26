#include <iostream>
#include "date.h"
#include "database.h"
#include <fstream>
#include <iomanip>
#include <string>
#include "variables.h"

using namespace std;

/**
 * A struct which holds the character that trigger the function, and the description
 * when displayed 
 */
struct Command{
    char key;
    string desc;
};

// Display length
const int kMaxCommandLength = 35;

// Number of commands and the list of the commands
const int kNumCommands = 12;
const Command kCommandList[kNumCommands] = {{'a', "Add a new entry to today."}, {'e', "Edit an entry of today."},{'d', "Delete an entry of today."},
    {'n', "Proceed to next day."}, {'j', "Jump to a specific day."}, {'s', "Save the current database."},
    {'v', "Filter, sort and view entries."}, {'r', "View monthly statistical report."},{'u', "Set up monthly automatic entries."},
    {'b', "Set up monthly budget"}, {'t',"Estimate your annual salary tax."}, {'q', "Save all and quit."}
};

// Save the previous saved place
string default_location = "";

// The whole database is saved globally in main.cpp
DaysDatabase* db = new DaysDatabase;
// The monthly budget is also saved globally in main.cpp
double budget_per_month = -1;

/**
 * Print endl to emulate system(CLS)
 */
void ClearScreen(){
    for (int i = 0; i < 10; i++){
        cout << endl;
    }
}

/**
 * Return a date after verifying the input
 * If year == -1, also ask for the year
 * If year is specified, just ask for day and month only
 */
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

/**
 * Print the all possible accounts in a table form
 */
void PrintAccounts(){
    cout << "List of Accounts:"<<endl;
    for (int i = 0; i < kMaxNumAccount; i++){
        cout << right << setw(3) << i+1 << ": " << setw(kAccountLength) <<left << kAccountStrings[i] << " ";
        if (((i+1)%3 == 0) and (i+1) != kMaxNumAccount)
            cout << endl;
    }
}

/**
 * Ask for a valid account for entry
 */
int InputAccount(int old){
    cout << "Input the account infomration for the entry: ";
    if (old != -1)
        cout << "[" << kAccountStrings[old] << "]";
    cout << endl << endl;
    PrintAccounts();
    int input;
    while (true){
        cout << endl << endl << "> ";
        cin >> input;
        if (input <= kMaxNumAccount and input > 0)
            return input -1;
        cout << "The number entered is not valid, please enter a valid account." << endl;
    }
}

/**
 * Print the list of category in tabular form
 */
void PrintCategory(){
    cout << "List of Categorys: (1-3 are incomes, 4-11 are expenses)" << endl;
    for (int i = 0; i < kMaxNumCategory; i++){
        cout << right << setw(3) << i+1 << ": " << setw(kCategoryLength) <<left << kCategoryStrings[i] << " ";
        if (((i+1)%3 == 0) and (i+1) != kMaxNumCategory)
            cout << endl;
    }
}

/**
 *  Ask for a valid category index
 */
int InputCategory(int old){
    cout << "Input the category information for the entry: "; 
    if (old != -1)
        cout << "[" << kCategoryStrings[old] << "]";
    cout << endl <<endl;
    PrintCategory();
    int input;
    while (true){
        cout << endl << endl << "> ";
        cin >> input;
        if (input <= kMaxNumCategory and input > 0)
            return input -1;
        cout << "The number entered is not valid, please enter a valid category." << endl;
    }
}

/**
 * The start of the program
 * Ask the user to init a new yearbook
 * or read from a file, init and read from the file and create DaysDatabase db
 */
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
                fin >> budget_per_month;
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

/**
 * Calculate the monthly expense based on today's month (found from index)
 */
float MonthsExpense(int i){
    Date today = (*db)[i].date;
    Date start = today;
    start.day = 1;
    Date end = today;
    end.day = end.LastDayInMonth();
    Enquiry eq = {start, end, -1, -1, 0, "", -1};
    EnquiryResults er = db->IquireFor(eq);
    float r = er.Sum();
    er.FreeMemory();
    return r;
}

/**
 * Print today's record and command lists
 */
char TodayAndInstructions(int i){

    cout << (*db)[i].Formatted() << endl << endl;
    
    cout << "Command List:"<<endl;
    for (int i = 0; i < kNumCommands; i++){
        cout << right << setw(3) << kCommandList[i].key << ": " << setw(kMaxCommandLength) <<left << kCommandList[i].desc << " ";
        if (((i+1)%3 == 0) and (i+1) != kNumCommands)
            cout << endl;
    }
    
    char input;
    cout << endl << endl;
    cout << "Monthly budget: " << setw(kMaxAmountLength);
    if (budget_per_month>0)
        cout << fixed << setprecision(2) << budget_per_month;
    else
        cout << "unset";
    cout << "     Monthly quota: " << setw(kMaxAmountLength);
    if (budget_per_month>0){
        float quota = budget_per_month + MonthsExpense(i);
        cout << fixed << setprecision(2) << quota;
        if (quota < 0)
            cout << "(EXCEEDED)";
        else if (quota < budget_per_month * 0.1)
            cout << "(ALERT)";
        else if (quota < budget_per_month * 0.2)
            cout << "(WARNING)";
        else if (quota < budget_per_month * 0.3)
            cout << "(CAUTION)";
    }
    else
        cout << "unlimited";
    cout << endl << "> ";
    cin >> input;
    return input;
}

/**
 * Incremet the index of today to point as next day
 */
void ProceedDay(int& i){
    if (i < (db->size-1))
        i++;
    else
        cout << "Cannot proceed to next year, please init a new database for next year." << endl;
}

/**
 * Input the amount for transaction, if given (show old also)
 */
float InputAmount(float old){
    cout << "Input the amount of the transaction, negative for expenses: ";
    if (old != 0)
        cout << "[" << old << "]" << endl;
    cout << endl << "> ";
    double a;
    cin >> a;
    return a;
}

/**
 * Input a remarks for a transaction, if given old (show it also)
 */
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

/**
 * Add an entry after asking for all information with verification functions
 * and insert it in today's DayRecords
 */
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

/**
 * Enquire for todays and get all index and pointer
 * Then use the index to find the Entry struct for editing
 */
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
        cout << "Please enter an appropriate index." << endl;
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

/**
 * Jump to some date by changing today's index
 */
void JumpDay(int&i){
    Date d;
    d = InputDate(db->year);
    i = db->FindDateIndex(d, 0, db->size);
}

/**
 * Save to the default location or ask the user to enter a new filename
 */
void SaveDB(){
    string input = "N";
    if (!default_location.empty()){
        cout << "Save to '" << default_location << "'? (Y or N)" << endl;
        while (true){
            cin >> input;
            if (input == "Y" or input == "N")
                break;
            cout << "Please enter 'Y' or 'N'." << endl;
        }
    }
    if (input == "N"){
        cout << "Enter a filename for saving the accounting database:" << endl;
        cin.ignore(1);
        getline(cin, default_location);
    }
    ofstream fou;
    fou.open(default_location);
    fou << budget_per_month << " ";
    fou << (*db);
    fou.close();
}

/**
 * Enquire for today, get the pointer and use the function in DaysRecord of
 * today to delete an shrink dynamic by the pointer
 */
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

/**
 * Set up automatic by asking the day, and if the day (e.g. 31) is valid in every months
 * and ask to input a alternative day if needed
 * All automatic record only get added after today's day
 */
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

/**
 * Utilize the advance enquiry function to its fullness and work as specific search for the user
 */
void AdvancedSearch(){
    cout << "Are you searching for a range of time (as oppose to filtering a single day)?  (Y or N)" << endl;
    char input;
    while (true){
        cout << "> ";
        cin >> input;
        if (input == 'Y' or input == 'N')
            break;
        cout << "Please enter 'Y' or 'N'." << endl;
    }
    Date start;
    Date end;
    if(input == 'Y'){
        ClearScreen();
        cout << "What is the starting day of the time range?"<<endl<<endl;
        start = InputDate(db->year);
        ClearScreen();
        cout << "What is the ending day (inclusive) of the time range?" << endl << endl;
        end = InputDate(db->year);
    }
    else{
        ClearScreen();
        cout << "Which day's records would you like to search for?" << endl << endl;
        start = InputDate(db->year);
        end = start;
    }
    ClearScreen();
    cout << "Would you like to show entries of specific account only? (0 to show any accounts)" << endl << endl;
    PrintAccounts();
    int account;
    while (true){
        cout << endl << endl << "> ";
        cin >> account;
        if (account <= kMaxNumAccount and account >= 0)
            account--;
            break;
        cout << "The number entered is not valid, please enter a valid account." << endl;
    }
    ClearScreen();
    cout << "Would you like to show entries of specific category only? (0 to show any categories)" << endl << endl;
    PrintCategory();
    int category;
    while (true){
        cout << endl << endl << "> ";
        cin >> category;
        if (category <= kMaxNumCategory and category >= 0)
            category--;
            break;
        cout << "The number entered is not valid, please enter a valid category." << endl;
    }
    ClearScreen();
    cout << "Would you like to show certain transaction only? (0 for any records, +number for income, -number for expenses)" << endl << "> ";
    int is_income;
    cin >> is_income;
    is_income = is_income == 0 ? -1 : is_income > 0;
    ClearScreen();
    cout << "Would you like to search word in remarks? (leave empty for any remarks)"<< endl << "> ";
    string search_string;
    cin.ignore(1);
    getline(cin, search_string);
    ClearScreen();
    cout << "How would you like the record to be sorted by? (c for chronological order, a for account, e for category, m for amount)" << endl<< "> ";
    while (true){
        cin >> input;
        if (input == 'c' or input == 'a' or input == 'e' or input == 'm')
            break;
    }
    ClearScreen();
    int sort_by;
    switch (input){
        case 'c': sort_by = -1; break;
        case 'a': sort_by = 0; break;
        case 'e': sort_by = 1; break;
        case 'm': sort_by = 2; break;
    }
    bool ascending = true;
    if (sort_by == 2){
        ClearScreen();
        cout << "Would you like to have amount in ascending order? (Y or N)" << endl;
        while (true){
            cout << "> ";
            cin >> input;
            if (input == 'Y' or input == 'N')
                break;
            cout << "Please enter 'Y' or 'N'." << endl;
        }
        ascending = input == 'Y';
    }
    ClearScreen();
    Enquiry eq = {start, end, account, category, is_income, search_string, sort_by, ascending};
    EnquiryResults er = db->IquireFor(eq);
    cout << er.Formatted() << endl << endl;
    cout << "Press 'Enter' to quit this enquiry." << endl;
    cin.ignore(1);
    string temp;
    getline(cin, temp);
    er.FreeMemory();
}

/**
 * Adjust the global saved new monthly budget variable
 */
void SetupBudget(){
    cout << "What would be your new monthly budget? (0 or lower to unset budget) "<< "[";
    if (budget_per_month>0)
        cout << fixed << setprecision(2) << budget_per_month;
    else
        cout << "unset";
    cout << "]" << endl << "> ";
    cin >> budget_per_month;
}

/**
 * Output this months total income, expenses and category percentage
 */
void MonthlyReport(int i){
    Date today = (*db)[i].date;
    Date start = today;
    start.day = 1;
    Date end = today;
    end.day = end.LastDayInMonth();
    float sum_category[kMaxNumCategory];
    float types_of_income[2];
    for (int i = 0; i < kMaxNumCategory; i++){
        Enquiry eq = {start, end, -1, i, -1, "", -1};
        EnquiryResults er = db->IquireFor(eq);
        sum_category[i] = er.Sum();
        er.FreeMemory();
    }
    for (int i = 0; i < 2; i++){
        Enquiry eq = {start, end, -1, -1, i, "", -1};
        EnquiryResults er = db->IquireFor(eq);
        types_of_income[i] = er.Sum();
        er.FreeMemory();
    }
    cout << "Statistical Report for " << kMonthString[today.month-1] << " of " << db->year << endl << endl;
    
    cout << setw(kCategoryLength) << "Total Incomes:" << "   " << fixed <<
        setw(kMaxAmountLength) << setprecision(2) << types_of_income[1] <<endl<<endl;
    cout << setw(kCategoryLength) << "Category" << " | " <<
        setw(kMaxAmountLength) << "Sum" << " | " << setw(kMaxAmountLength) << "Percentage (%)" << endl;
    cout << "---------------------+-----------------+-----------------"<<endl;
    for (int i =0; i < 3; i++){
        cout << setw(kCategoryLength) << kCategoryStrings[i] << " | " << setw(kMaxAmountLength) << fixed << setprecision(2) << sum_category[i] << " | " <<
            setw(kMaxAmountLength) << fixed << setprecision(2) << sum_category[i]/types_of_income[1]*100 << endl;
    }
    cout << endl;
    
    cout << setw(kCategoryLength) << "Total Expenses:" << "   " << fixed <<
        setw(kMaxAmountLength) << setprecision(2) << types_of_income[0] << endl <<endl;
    cout << setw(kCategoryLength) << "Category" << " | " <<
        setw(kMaxAmountLength) << "Sum" << " | " << setw(kMaxAmountLength) << "Percentage (%)" << endl;
    cout << "---------------------+-----------------+-----------------"<<endl;
    for (int i =3; i < 11; i++){
        cout << setw(kCategoryLength) << kCategoryStrings[i] << " | " << setw(kMaxAmountLength) << fixed << setprecision(2) << sum_category[i] << " | " <<
            setw(kMaxAmountLength) << fixed << setprecision(2);
        if (sum_category[i] == 0)
            cout << 0;
        else
            cout << sum_category[i]/types_of_income[0] *100;
        cout << endl;
    }
    
    cout << endl << "Press 'Enter' to quit this enquiry." << endl;
    cin.ignore(1);
    string temp;
    getline(cin, temp);
}

/**
 * Ask for an input of a positive float number
 */
float InputPositiveFloat(){
    float input;
    while (true){
        cout << "> ";
        cin >> input;
        if (input >= 0)
            return input;
        cout << "Please enter a positive number." << endl;
    }
}

/**
 * Ask for an input of a positive integer
 */
int InputPositiveInt(){
    int input;
    while (true){
        cout << "> ";
        cin >> input;
        if (input >= 0)
            return input;
        cout << "Please enter a positive integer." << endl;
    }
}

/**
 *  Print the amount in the general format used by the system
 */
void PrintInFixedAmount(float i){
    cout << fixed << setw(kMaxAmountLength) << setprecision(2) << right << i;
}

/**
 * Calculate tax based on total taxable amount
 * Using 2018-2019 tax report
 */
float CalculateTax(float t){
    float tax;
    if (t <= 0)
        return 0;
    if (t <= 50000)
        tax = t * 0.02;
    else if (t <=100000)
        tax = 1000 + (t-50000) * 0.06;
    else if (t <= 150000)
        tax = 4000 + (t- 100000) * 0.1;
    else if (t <= 200000)
        tax = 9000 + (t- 150000) * 0.14;
    else
        tax = 16000 + (t-200000) * 0.17;
        
    float stand = t * 0.15;
    return stand < tax ? stand : tax;
    
}

/**
 * Calculate personal tax based on Enquiry of this years total income
 * and additional information asked for from the users
 */
void PersonalTax(){
    Date start = {1, 1, db->year};
    Date end = {31, 12, db->year};
    Enquiry eq = {start, end, -1, -1, 1, "", -1};
    EnquiryResults er = db->IquireFor(eq);
    float sum_income = er.Sum();
    float residence;
    float deduction;
    float child;
    float siblings;
    float parents;
    float other_allow;
    er.FreeMemory();
    
    
    cout << "Enter the value of any places of residence provided by your employter:" << endl;
    residence = InputPositiveFloat();
    cout << "Enter the value of deduction on the taxable incomes:" << endl;
    deduction = -InputPositiveFloat();
    
    cout << "How many dependent children (born in this year) do you have that is eligible for child allowance?" << endl;
    child = -240000 * InputPositiveInt();
    
    cout << "How many dependent children (born in other years) do you have that is eligible for child allowance?" << endl;
    child += -120000 * InputPositiveInt();
    
    cout << "How many dependent siblings do you have that is eligible for dependent brother or dependent sister allowance?" << endl;
    siblings = -37500 * InputPositiveInt();
    
    cout << "How many dependent parents (aged 55 to 59, and resided with you) do you have that is eligible for allowance?" << endl;
    parents = -50000 * InputPositiveInt();
    cout << "How many dependent parents (over 60, and resided with you) do you have that is eligible for allowance?" << endl;
    parents -= 50000 * 2 * InputPositiveInt();
    cout << "How many dependent parents (aged 55 to 59, and not resided with you) do you have that is eligible for allowance?" << endl;
    parents -= 25000 * InputPositiveInt();
    cout << "How many dependent parents (over 60, and not resided with you) do you have that is eligible for allowance?" << endl;
    parents -= 25000 *2* InputPositiveInt();
    
    cout << "Enter the amount of other allowances you have during the year (e.g. basic allowance):" << endl;
    other_allow -= InputPositiveFloat();
    
    ClearScreen();
    
    cout << "Report of the estimated tax in year " << db->year << endl << endl;
    
    float taxable_amount = sum_income + residence + deduction + child + siblings + parents + other_allow;
    
    cout << setw(kCategoryLength) << "Total Incomes" << " | "; PrintInFixedAmount(sum_income); cout << endl;
    cout << setw(kCategoryLength) << "Residence" << " | "; PrintInFixedAmount(residence); cout << endl;
    cout << setw(kCategoryLength) << "Total Deductions" << " | "; PrintInFixedAmount(deduction); cout << endl;
    cout << setw(kCategoryLength) << "Child Allowance" << " | "; PrintInFixedAmount(child); cout << endl;
    cout << setw(kCategoryLength) << "Sibling Allowance" << " | "; PrintInFixedAmount(siblings); cout << endl;
    cout << setw(kCategoryLength) << "Parents Allowance" << " | "; PrintInFixedAmount(parents); cout << endl;
    cout << setw(kCategoryLength) << "Other Allowance" << " | "; PrintInFixedAmount(other_allow); cout << endl;
    cout << "---------------------+-----------------" << endl;
    cout << setw(kCategoryLength) << "Taxable Amount" << " | "; PrintInFixedAmount(taxable_amount); cout << endl << endl;
    
    cout << setw(kCategoryLength) << "Estimated Tax:" << "   "; PrintInFixedAmount(CalculateTax(taxable_amount)); cout << endl << endl;
    
    cout << "Press 'Enter' to quit this enquiry." << endl;
    cin.ignore(1);
    string temp;
    getline(cin, temp);
    
}

int main(){
    int today_index = InitDatabaseForUser();
    char input;
    // The main input loop
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
            case 'v': AdvancedSearch();break;
            case 'b': SetupBudget();break;
            case 'r': MonthlyReport(today_index);break;
            case 't': PersonalTax();break;
        }
        ClearScreen();
    } while (input != 'q');
    
    db->FreeDatabaseMemory();
    return 0;
}