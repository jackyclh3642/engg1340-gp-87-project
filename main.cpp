#include "variables.h"
#include "date.h"
#include "database.h"
#include <iostream>
#include <string>
using namespace std;


void initalize_the_databas(DaysDatabase maps, int year){
	maps.InitDatabase(year);
}
//function 1
void appending_today_record(DaysDatabase map, int today){
	Enrty err;
	cout<<"Please input (account)[space](expenditure items/revenue items)[space][amount][space][remark]"<<endl;
	cout<<"For account:"<<endl;
	cout<<"Input 1 for Cash   account"<<endl;
	cout<<"Input 2 for Bank   account"<<endl;
	cout<<"Input 3 for Credit account"<<endl;
	cout<<"For expenditure/revenue "<<endl;
	cout<<"Input  0 for Salary(revenue)"<<endl;
	cout<<"Input  1 for Other Income(revenue)"<<endl;
	cout<<"Input  2 for Entertainment(expenditure)"<<endl;
	cout<<"Input  3 for Transportation(expenditure)"<<endl;
	cout<<"Input  4 for Living Expense(expenditure)"<<endl;
	cout<<"Input  6 for Money transfer(expenditure)"<<endl;
	cout<<"Input  7 for Settle Debt(expenditure)"<<endl;
	cout<<"Input  8 for Fixed Expense(expenditure)"<<endl;
	cout<<"Input  9 for Rents(expenditure)"<<endl;
	cout<<"Input 10 for Other Expenditure(expenditure"<<endl;
	cout<<"For amount:"<<endl;
	cout<<"The amount should be positive when inputting revenue items, while the amount should be negative when inputting expenditure items"<<endl;
	cout<<"For remark please enter a sentence to specify the usage"<<endl;
	cout<<"e.g. I using my cash account for transportation which cost me 5 cents"<<endl;
	cout<<"Please input 1 3 -0.5 I go to school by bus"<<endl;
	cin >> err;
	map.days[today] << err;
}
//function 2
void editting_today_record(DaysDatabse map, int today){
	




















}
//fucntion 3
void editting_past_record(DaysDatabase map, int today){
	bool correct_input = true;
	Date past;
	while (correct_input){
		cout<<"Please input the date you want to edit"<<endl;
		cin  >> past;	
		if (past > map.days[today]){
			cout<<"Invaild date is input, please input again"<<endl;
		}
		else{
			while(true){
				bool con = true;
				xx
				cout<<"Input the number you want to edit"<<endl;
				xx
				while(con){
					cout<<"Do you want to continue edit? Input Y for yes meanwhile N for no"<<endl;
					cin>>input;
					if (input == 'Y')	
						con = false;
					else if(input == 'N')
						return;
					else
						cout<<"Invalid input, please input again"<<endl;
						

			}
		}


	}
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

int main(){
	Date input_date;
	int day, month, year;
	int today;
	DaysDatabase map;
	cout<<"Please input today's date in DD[space]MM[space]YY"<<end;
	cout<<"e.g. for 1st May 1999, please input 1 5 1999"<<endl;
	cin>>input_date;
	today = FindDateIndex(input_date, 0, map.size);
	initalize_the_database(map, year);
	int input;
	bool processing = true;
	while(processing){
		cout<<"Welcome today is "<<map.days[today].date.Formatted()<<endl;
		cout<<"Input 1 for adding expenses/revenue record of today"<<endl;
		cout<<"Input 2 for editing today record"<<endl;
		cout<<"Input 3 for editing past record"<<endl;
		cout<<"Input 4 for checking daily record"<<endl;
		cout<<"Input 5 for setting budget use in this month"<<endl;
		cout<<"Input 6 for setting fix expenses and fix income "<<endl;
		cout<<"Input 7 for reviewing financial report"<<endl;
		cout<<"Input 8 for end_of_today"<<endl;
		cout<<"Input 0 for save and quit"<<dnel;
		cin>>input;
		switch(input){
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
