#ifndef VARIABLES_H
#define VARIABLES_H

#include <string>

const int kAccountLength = 15;
const int kCategoryLength = 20;
const int kIndexLength = 3;

const std::string kAccountStrings[] = {
    "Cash",
    "Bank Card",
    "Credit Card"
};

const std::string kCategoryStrings[] = {
    "Salary","Other Income",
       "Entertainment", "Transportation", "Living Expense", "Money Transfer", "Settle Debt", "Fixed Expense", "Rent", "Other Expense"};

/**const std:: string kCatagoryStrings[] = { const std:: string income[] ={"salary", "interest", "other_income"}, const std:: string expenditure[] ={"entertainment", "transportation", "living_expenditure", "money_transfer", "settle_debt", "stocks", "fixed_expenditure", "rents", "other_expenditures"}};



**/

/**        double entertainment;
        double transportation;
        double living_expenditure;
        double money_transfer;
        double settle_debt;
        double stocks;
        double fixed_expenditure;
        double rents;
        double other_expenditure;
	    double cash_account;
    double credit_account;
    double stocks_account;
    double saving_account;
            double salary;
        double interest;
        double gain_from_stocks;
        double others_income;

**/

#endif
