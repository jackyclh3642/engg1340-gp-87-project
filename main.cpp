#include <iostream>
#include <string>

using namespace std;

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



