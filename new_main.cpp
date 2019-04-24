#include <iostream>
#include <iomanip>
#include <string>
#include "database.h"
#include "date.h"

using namespace std;

//function checking right here 
void initalize_the_database(DaysDatabase maps, int year){
        maps.InitDatabase(year);
}
//function 1
void appending_today_record(DaysDatabase map, int today_index){
        Enrty Appending_transactions_input;
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
        cout<<"For remark please enter a sentence to specify the transaction"<<endl;
        cout<<"e.g. I using my cash account for transportation which cost 5 cents"<<endl;
        cout<<"Please input 1 3 -0.5 I go to school by bus"<<endl;
        cin >> Appending_transaction_input;
        map->days[today]<< Appending_transaction_input;
}
//function 7
void end_of_today(int &today){
        char input;
        cout<<"Are you sure to end of today? Enter Y for YES and N for NO"<<endl;
        cin>>input;
        if (input == "Y")
                ++today;
        else
                return;
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

//fucntion 3
void editting_past_record(DaysDatabase map, int today){
        bool continue_edit_past_record = true;
        Date past;
        int past_index;
        while (continue_edit_past_record){
                cout<<"Please input the date before"<<map->days[today]<<"(Today) you want to edit"<<endl;
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
                else{
                    cout<<"Invalid date is input";
                }
                }
}

//function 2
void editting_today_record(DaysDatabse map, int today){



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
                cout<<"Welcome today is "<<map->days[today]->date->Formatted()<<endl;
                cout<<"Input 1 for adding expenses/revenue records of today"<<endl;
                cout<<"Input 2 for editing today record"<<endl;
                cout<<"Input 3 for editing/adding past record"<<endl;
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
