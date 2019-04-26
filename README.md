# ENGG1340 Group 87 Course Project

## Problem statement

Implement an accounting/budgeting system for personal financial tracking and management.

## Problem setting

Assume that the program would be installed for each user only, in a secure directory in the user's personal computer.

Hence:

* Minimum security would be needed for the database of the software, hence plain-text file should work.
* Only data from 1 user is needed to be taken into account, there is no need to handle multiple database at once.

### input/output specifications

1. iomanip is used to print out the financial report, taxation report and daily transaction report more clearly
1. iostream is used for basic I/O
1. fstream is used for saving and loading the record
1. database.h is used for custome operator(e.g. when using cin>> Entry it will input the account, cateogory, amouny and remark)
1. date.h is used for custome operator(e.g.when using cin>> Date it will inout the date, month and year)

### Basic functions

1. Add and removal of records of income and expenses;
1. Basic information per each records (amount, date, types of income or expense and account);
1. Allow the user to delete and edit records at any time;
1. Present the records after filtered/sorted by the metadata;
1. Provide statistical report of user's financial state as summaries;
1. Allow budget setting and alert for each types of income.

### Proposed extended functions
1. Allow setting of automatic records (ie salary, fixed expense);
1. Allow the user to load and save the record
1. Help the user to estimate the tax he needs to pay in that year.

###Code requirment

1. dynamic memory management() in Database, Entry transaction, DayRecords all memory are freed after end the programme 
1. File input/output in Saving and loading 
1. Data manipulation binary search is used in Day seraching; insertion sort is used for appending new days;
1. multiple file database.h, date.h... is available 
1. naming style Google c++ naming style
1. In-code documentation main.cpp database.cpp date.h
