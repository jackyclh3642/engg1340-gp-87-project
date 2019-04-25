#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "database.h"
#include "date.h"

using namespace std;

void transaction_instruction_text(){
    cout<<"Please input (account)[space](expenditure items/revenue items)[space][amount][space][remark]"<<endl;
    cout<<"For account:"<<endl;
    cout<<"Input 1 for Cash   account"<<endl;
    cout<<"Input 2 for Bank   account"<<endl;
    cout<<"Input 3 for Credit account"<<endl;
    cout<<"For expenditure items/revenue items"<<endl;
    cout<<"Input  0 for Salary(revenue item)"<<endl;
    cout<<"Input  1 for Other Income(revenue item)"<<endl;
    cout<<"Input  2 for Entertainment(expenditure item)"<<endl;
    cout<<"Input  3 for Transportation(expenditure item)"<<endl;
    cout<<"Input  4 for Living Expense(expenditure item)"<<endl;
    cout<<"Input  6 for Money transfer(expenditure item)"<<endl;
    cout<<"Input  7 for Settle Debt(expenditure item)"<<endl;
    cout<<"Input  8 for Fixed Expense(expenditure item)"<<endl;
    cout<<"Input  9 for Rents(expenditure item)"<<endl;
    cout<<"Input 10 for Other Expenditure(expenditure item)"<<endl;
    cout<<"For amount:"<<endl;
    cout<<"The amount should be positive when inputting revenue items, while the amount should be negative when inputting expenditure items"<<endl;
    
}

//function checking right here
void initalize_the_database(DaysDatabase maps, int year){
        maps.InitDatabase(year);
}
//function 1
void appending_today_record(DaysDatabase map, int today_index){
        Enrty Appending_transactions_input;
        ////////////////
        transaction_instruction_text;
        cout<<"For remark please enter a sentence to specify the transaction"<<endl;
        cout<<"e.g. I using my cash account for transportation which cost 5 cents"<<endl;
        cout<<"Please input 1 3 -0.5 I go to school by bus"<<endl;
        cin >> Appending_transaction_input;
        map->days[today_index]<< Appending_transaction_input;
}
//function for automatic appending
//automatic setting of each month
void automatic_setting_for_every_month(DaysDatebase map, int year){
    //have bugs for setting 29th and 31th and need a function for setting every end of month
    cout<<"Please first input the fixed_transaction"
    Enrty Appending_transactions_input;
    //////////////
    transaction_instruction_text;
    cout<<"For remark please enter a sentence to specify the transaction and add (setting) at the end"<<endl;
    cout<<"e.g. I recieve 5000 for salary "<<endl;
    cout<<"Please input 2 0 5000 salary recieve(setting)"<<endl;
    cin>>Appending_transactions_input;
    cout<<"Please input the date for automatic set"
    int setting_index;
    cout<<"e.g. I recieve my salary on 7th every month";
    cout<<"Please input 7"
    cin>>date;
    if (!IsLeapYear && date == 29){
        int Feb_date;
        cout<<year<<"does not have 29th Febraray"<<endl;
        cout<<"Please input the date for Febrary"<<endl;
        cin>>Feb_date;
        Date target_date;
        int target_index;
        for(int month = 1; month < 13; month++){
            if(month == 2){
                target_date = {Feb_date, month, year};
                target_index = map->FindDateIndex(target_date, 0, map->size);
                map->days[target_index]<<Appending_transaction_input;
            }
            else{
                target_date = {date, month, year};
                target_index = map->FindDateIndex(target_date, 0, map->size);
                map->days[target_index]<<Appending_transaction_input;
            }
        }
    }
    if (date == 31){
        cout<<"There do not have 31th in Febrary, April, June, September and Novemeber"<<end;
        cout<<"Please input a date for them"<<endl;
        int smaller_month_date;
        cin>>smaller_month_date;
        if (smaller_month_date == 30){
            cout<<"There is no 30th in Febraray"<<endl;
            cout<<"Please input a date for Febrary"<<endl;
            int Febrary_date;
            cin>>Febrary_date;
            if ( !IsLeapYear(year) && Febrary_date == 29){
                cout<<"There does not have 29th Febrary in "<<year<<endl;
                cout<<"Please input another date for Febrary"<<endl;
                cin>>Febrary_date;
                Date target_date;
                int target_index;
                for (int month = 1; month < 13; month++){
                    if (month == 2|| month == 4|| month == 6|| month == 9|| month == 11||){
                        if(month == 2){
                            target_date = {Febrary_date, 2, year};
                            target_index = map->FindDateIndex(target_date, 0, map->size);
                            map->days[target_index]<<Appending_transaction_input;
                        }
                        else{
                            target_date = {smaller_month_date, month, year};
                            target_index = map->FindDateIndex(target_date, 0, map->size);
                            map->days[target_index]<<Appending_transaction_input;
                        }
                    }
                    else{
                        target_date = {date, month, year};
                        target_index = map->FindDateIndex(target_date, 0, map->size);
                        map->days[target_index]<<Appending_transaction_input;
                    }
                }           
            }
        }
    }
    else{
        Date target_date;
        int target_index;
        for (int month = 1; month <13; month++)
            target_date = {date, month, year};
            target_index = map->FindDateIndex(target_date, 0, map->size);
            map->days[target_index]<<Appending_transaction_input;
    }
}
//function 7
void end_of_today(DaysDatabase map, int &today){
        char input;
        while (true){
            cout<<"Are you sure to end of today? Enter Y for YES and N for NO"<<endl;
            cin>>input;
            if (input == "Y"){
                if(map->days[today]->date->day == 31 && map->days[today]->date->month == 12){
                    cout<<"Today is already the last day of "<<map->day[today]->date->year<<endl;
                    return;
                }
                else{
                    cout<<"End of "<<map->days->date<<endl;
                    ++today;
                    return;
                }
            }
            else if(input == 'N'){
                cout<<"return to the ENGG1340-GROUP-87 Main Menu"<<endl;
                return;
            }
            else{
                "Invalid character is input"<<endl;
            }
        
        }            
}
//function 0
void function_procssing(bool &processing){
        char input;
        cout<<"Are you sure to end the function? Enter Y for YES and N for NO"<<endl;
        cin>>input;
        if (input == "Y")
                processing = false;
        else
                processing = true;
}
void editting_past_record(DaysDatabase map, int today){
        bool continue_edit_past_record = true;
        Date past;
        int past_index;
        while (continue_edit_past_record){
                cout<<"Please input the date before"<<map->days[today]->date<<"(Today) you want to edit"<<endl;
                cin  >> past;
                if (past > map->days[today]){   
                        bool continue_editting;
                        int correction_location;
                        Entry new_transaction_input;
                        past_index = map->FindDateIndex(past, 0, map->size);
                        while(continue_editting){
                                map->days[past_index]->Formatted();
                                cout<<"Input the number you want to edit"<<endl;
                                cin>>correction_location;
                                ////////////
                                transaction_instruction_text();
                                cout<<"For remark please enter a sentence to specify the transaction"<<endl;
                                cout<<"e.g. I using my cash account for transportation which cost 5 cents"<<endl;
                                cout<<"Please input 1 3 -0.5 I go to school by bus"<<endl;
                                cin >> new_transaction_input;
                                map->days[past_index]->transactions[correction_location - 1] = new_transaction_input;
                                bool correct_continue_input = true;
                                char input;
                                while(correct_continue_input){
                                        cout<<"Do you want to continue edit? Input Y for yes meanwhile N for no"<<endl;
                                        cin>> input;
                                        if (input == 'Y')
                                            correct_continue_input = false;
                                        else if(input == 'N')
                                            return;
                                        else
                                            cout<<"Invalid input, please input again"<<endl;
                                }
                }


                }
                else{
                    cout<<"Invalid date is input";
                }
                }
}                   
void editting_today_record(DaysDatabse map, int today){
    bool continue_editting;
    int correction_location;
    Entry new_transaction_input;
    while(continue_editting){
        map->days[today]->Formatted();
        cout<<"Input the number you want to edit"<<endl;
        cin>>correction_location;
        transaction_instruction_text();
        cout<<"For remark please enter a sentence to specify the transaction"<<endl;
        cout<<"e.g. I using my cash account for transportation which cost 5 cents"<<endl;
        cout<<"Please input 1 3 -0.5 I go to school by bus"<<endl;
        cin >> new_transaction_input;
        map->days[today]->transactions[correction_location - 1] = new_transaction_input;
        bool correct_continue_input = true;
        while(correct_continue_input){
            cout<<"Do you want to continue edit? Input Y for yes meanwhile N for no"<<endl;
            cin>> correct_continue_input;
            if (input == 'Y')
                correct_continue_input = false;
                            else if(input == 'N')
                return;
            else
                cout<<"Invalid input, please input again"<<endl;
        }
    }
}
void appending_past_record(DaysDatabase map, int today_index){
    bool continue_edit_past_record = true;
    Date past;
    int past_index;
    while (continue_edit_past_record){
        cout<<"Please input the date before"<<map->days[today]<<"(Today) you want to edit in DD[space]MM[space]YY"<<endl;
        cin >> past;
        if (past > map->days[today]){   
            Entry new_transaction_input;
            past_index = map->FindDateIndex(past, 0, map->size);
            Enrty Appending_transactions_input;
            transaction_instruction_text();
            cout<<"For remark please enter a sentence to specify the transaction"<<endl;
            cout<<"e.g. I using my cash account for transportation which cost 5 cents"<<endl;
            cout<<"Please input 1 3 -0.5 I go to school by bus"<<endl;
            cin >> Appending_transaction_input;
            map->days[past]<< Appending_transaction_input;
            return;
            
        }
        else{
            cout<<"Invalid date is input;"
        }
    }    
}
//delete past record
void delete_past_transaction_record(DaysDatabase map){
        bool continue_delete_past_record = true;
        Date past;
        int past_index;
        while (continue_edit_past_record){
                cout<<"Please input the date before"<<map->days[today]->date<<"(Today) you want to edit"<<endl;
                cin  >> past;
                if (past > map->days[today]){   
                        bool continue_delete;
                        int delete_location;
                        past_index = map->FindDateIndex(past, 0, map->size);
                        while(continue_delete){
                            map->days[past_index]->Formatted();
                            cout<<"Input the number you want to delete";
                            cin>>delete_location;
                            map->days[past_index]<<delete_location;//the function i wrote in check_delete.txt
                            bool correct_continue_input = true;
                            char input;
                            while(correct_continue_input){
                                    cout<<"Do you want to continue delete? Input Y for yes meanwhile N for no"<<endl;
                                    cin>> input;
                                    if (input == 'Y')
                                        correct_continue_input = false;
                                    else if(input == 'N')
                                        return;
                                    else
                                        cout<<"Invalid input, please input again"<<endl;
                                }
                        }
                }
                else{
                    cout<<"Invalid date is input";
                }
        }
}
//delete today record
void delete_today_transaction_record(DaysDatabase map, int today_index){
    bool continue_delete;
    int delete_location;
    while(continue_delete){
        map->days[today]->Formatted();
        cout<<"Input the number you want to delete";
        cin>>delete_location;
        map->days[past_index]<<delete_location;//the function i wrote in check_delete.txt
        bool correct_continue_input = true;
        char input;
        while(correct_continue_input){
            cout<<"Do you want to continue delete? Input Y for yes meanwhile N for no"<<endl; 
            cin>> input;
            if (input == 'Y')
                correct_continue_input = false;
            else if(input == 'N')
                return;
            else
                cout<<"Invalid input, please input again"<<endl;
        }
    }
}



int main(){
        //start of initalizing stage
        Date input_date;
        int today;
        DaysDatabase map;
        cout<<"Please input today's date in DD[space]MM[space]YY"<<end;
        cout<<"e.g. for 1st May 1999, please input 1 5 1999"<<endl;
        cin>>input_date;
        initalize_the_database(map, input_date->year);
        today = map->FindDateIndex(input_date, 0, map->size);
        
        /**recover function
        cout<<"Wlecome to ENGG1340-Group-87-Project"<<endl;
        cout<<"Are there any data you want to recovery?";
        cout<<"Please input Y for YES, else input N for NO";
        char recovery_input;
        bool recovery_process = true
        while(recovery_process){
            cout<<"Please input"<<endl;
            cin>>recovery_input;
            if (recovery_input = 'Y'){
                recovery function
            }
            else if(recovery == 'N'){
                recovery_process = false;
            }
            else{
                cout<<"Invalid character is input"<<endl;
            }
        }
        **/
        //End of the initializing stage
        //Move to the processing stage
        int processing_input;
        bool processing = true;
        while(processing){
                cout<<"Welcome to ENGG1340-GROUP-87 Main Menu, today is "<<map->days[today]->date->Formatted()<<endl;
                cout<<"Input 1 for adding expenses/revenue records of today"<<endl;
                cout<<"Input 2 for editing today record"<<endl;
                cout<<"Input 3 for editing/adding past record"<<endl;
                cout<<"Input 4 for adding past record"<<endl;
                cout<<"Input 4 for checking daily record"<<endl;
                cout<<"Input 5 for setting budget use in this month"<<endl;
                cout<<"Input 6 for setting fix expenses and fix income "<<endl;
                cout<<"Input 7 for reviewing financial report"<<endl;
                cout<<"Input 8 for end_of_today"<<endl;
                cout<<"Input 0 for save and quit"<<dnel;
                cin>>processing_input;
                switch(processing_input){
                        case 1:
                                appending_today_record(map, today)
                                break;
                        case 2:
                        
                                break;
                        case 3:
                                editing past function;
                                break;
                        case 4:
                                checking daily record;
                                break;
                        case 5:
                                setting budget;
                                break;
                        case 6:

                                break;
                        case 7:

                                break;
                        case 8:
                                end_of_today(today);
                                break;
                        case 0:
                                function_processing(processing);
                                break;
                        default:
                                cout<<"Invalid please input again!";
                }
        }
        return 0;
}
