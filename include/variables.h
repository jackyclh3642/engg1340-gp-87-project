#ifndef VARIABLES_H
#define VARIABLES_H

#include <string>

// The maximum width used to display various kind of string or amount
const int kAccountLength = 15;
const int kCategoryLength = 20;
const int kIndexLength = 3;
const int kRemarksLength = 30;

// The size of accounts list and category lists, used for interation
const int kMaxNumAccount = 4;
const int kMaxNumCategory = 11;

const std::string kAccountStrings[kMaxNumAccount] = {
    "Cash",
    "Bank Card",
    "Credit Card",
    "Octopus Card"
};

const std::string kCategoryStrings[kMaxNumCategory] = {
    "Salary","Loan","Other Income",
       "Leisure", "Transportation", "Living Expense", "Money Transfer", "Repay Debt", "Fixed Expense", "Rent", "Other Expense"};

#endif