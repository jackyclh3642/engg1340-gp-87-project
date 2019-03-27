# ENGG1340 Group 87 Course Project

## Problem statement

Implement an accounting/budgeting system for personal financial tracking and management.

## Problem setting

Assume that the program would be installed for each user only, in a secure directory in the user's personal computer.

Hence:

* Minimum security would be needed for the database of the software, hence plain-text file should work.
* Only data from 1 user is needed to be taken into account, there is no need to handle multiple database at once.

## Problem functions

### Basic functions

1. Add and removal of records of income and expenses;
1. Basic information per each records (amount, date, types of income or expense and account);
1. Allow the user to delete and edit records at any time;
1. Present the records after filtered/sorted by the metadata;
1. Provide statistical report of user's financial state as summaries;
1. Allow budget setting and alert for each types of income.


### Proposed extended functions

1. Preliminary forcast of expense using previous months' data using linear regression;
1. Export of the records to different format (ie. csv) to be analyzed and plotted in spreadsheet software;
1. Allow setting of automatic records (ie salary, fixed expense);
1. Alert for credit card/bill payment;
1. Calculation of simple/compound interest stored in bank account.