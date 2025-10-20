#include "Store.h"
#include "Timer.h"
#include <iostream>

void Store::showBankMenu()
{
    cout << "\n--- Bank Admin Menu ---" << endl;
    cout << "1. List All Customers" << endl;
    cout << "2. List Dormant Accounts (no transaction in 1 month)" << endl;
    cout << "3. List Transactions (Last Week)" << endl;
    cout << "4. List Top N Users (Transactions Today)" << endl;
    cout << "0. Back" << endl;
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        for (int i = 0; i < allAccounts.size(); i++)
        {
            cout << "User: " << allAccounts[i]->ownerUsername << ", Balance: $" << allAccounts[i]->balance << endl;
        }
    }
    else if (choice == 2)
    {
        cout << "--- Dormant Accounts (no Transaction in 1 month) ---" << endl;
        for (int i = 0; i < allAccounts.size(); i++)
        {
            bool hasRecentTransaction = false;
            for (int j = 0; j < allTransactions.size(); j++)
            {
                if (allTransactions[j]->buyerUsername == allAccounts[i]->ownerUsername)
                {
                    if (TimeUtil::isLastMonth(allTransactions[j]->timestamp))
                    {
                        hasRecentTransaction = true;
                        break;
                    }
                }
            }
            if (!hasRecentTransaction)
            {
                cout << allAccounts[i]->ownerUsername << " is dormant." << endl;
            }
        }
    }

    else if (choice == 3)
    {
        bank_listTransactionsLastWeek();
    }

    else if (choice == 4)
    {
        bank_topNUsersToday();
    }
}

void Store::showStoreMenu()
{
    cout << "\n--- Store Admin Menu ---" << endl;
    cout << "1. List All Transactions (Paid but not Completed)" << endl;
    cout << "2. Manage Transaction Status (Set Complete/Cancelled)" << endl;
    cout << "3. List Transactions (Last K Days)" << endl;
    cout << "4. List Most Frequent Items (Top M)" << endl;
    cout << "5. List Most Active Users (Today)" << endl;
    cout << "0. Back" << endl;
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        for (int i = 0; i < allTransactions.size(); i++)
        {
            if (allTransactions[i]->status == "paid")
            {
                cout << "Item: " << allTransactions[i]->itemName << ", Buyer: " << allTransactions[i]->buyerUsername << endl;
            }
        }
    }

    else if (choice == 2)
    {
        store_manageTransactions();
    }

    else if (choice == 3)
    {
        store_listTransactionsKDays();
    }

    else if (choice == 4)
    {
        store_mostFrequentItems();
    }

    else if (choice == 5)
    {
        store_mostActiveUsers();
    }
}