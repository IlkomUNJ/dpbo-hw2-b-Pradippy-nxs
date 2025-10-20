#include "Store.h"
#include "Timer.h"
#include <iostream>
#include <string>
#include <vector>

void bubbleSort(vector<string> &names, vector<int> &counts)
{
    int n = counts.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (counts[j] < counts[j + 1])
            {
                int tempCount = counts[j];
                counts[j] = counts[j + 1];
                counts[j + 1] = tempCount;

                string tempName = names[j];
                names[j] = names[j + 1];
                names[j + 1] = tempName;
            }
        }
    }
}
int findInVector(vector<string> &vec, string name)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] == name)
            return i;
    }
    return -1;
}

void Store::bank_topNUsersToday()
{
    cout << "Enter N: ";
    int n;
    cin >> n;

    vector<string> userNames;
    vector<int> userCounts;

    for (int i = 0; i < allTransactions.size(); i++)
    {
        if (TimeUtil::isToday(allTransactions[i]->timestamp))
        {
            Transaction *t = allTransactions[i];

            if (!t->buyerUsername.empty())
            {
                int pos = findInVector(userNames, t->buyerUsername);
                if (pos == -1)
                {
                    userNames.push_back(t->buyerUsername);
                    userCounts.push_back(1);
                }
                else
                {
                    userCounts[pos]++;
                }
            }

            if (t->type == "PURCHASE" && !t->sellerUsername.empty())
            {
                int pos = findInVector(userNames, t->sellerUsername);
                if (pos == -1)
                {
                    userNames.push_back(t->sellerUsername);
                    userCounts.push_back(1);
                }
                else
                {
                    userCounts[pos]++;
                }
            }
        }
    }

    if (userNames.empty())
    {
        cout << "No transactions today." << endl;
        return;
    }

    bubbleSort(userNames, userCounts);

    cout << "\n--- Top " << n << " Users by Transactions Today ---" << endl;
    for (int i = 0; i < n && i < userNames.size(); i++)
    {
        cout << i + 1 << ". " << userNames[i] << " (" << userCounts[i] << " transactions)" << endl;
    }
}

void Store::store_mostFrequentItems()
{
    cout << "Enter M: ";
    int m;
    cin >> m;

    vector<string> itemNames;
    vector<int> itemCounts;

    for (int i = 0; i < allItems.size(); i++)
    {
        itemNames.push_back(allItems[i]->name);
        itemCounts.push_back(0);
    }

    if (itemNames.empty())
    {
        cout << "There are no items in the store." << endl;
        return;
    }

    for (int i = 0; i < allTransactions.size(); i++)
    {
        if (allTransactions[i]->type == "PURCHASE")
        {
            int pos = findInVector(itemNames, allTransactions[i]->itemName);
            if (pos != -1)
            {
                itemCounts[pos]++;
            }
        }
    }

    bubbleSort(itemNames, itemCounts);

    cout << "\n--- Top " << m << " Most Frequent Items (All Time) ---" << endl;
    for (int i = 0; i < m && i < itemNames.size(); i++)
    {
        if (itemCounts[i] > 0)
        {
            cout << i + 1 << ". " << itemNames[i] << " (" << itemCounts[i] << " transactions)" << endl;
        }
    }
}

void Store::store_mostActiveUsers()
{
    cout << "(This report is identical to the Bank's 'Top N Users Today' report)" << endl;
    bank_topNUsersToday();
}

void Store::seller_topKItems()
{
    cout << "Enter K: ";
    int k;
    cin >> k;

    vector<string> itemNames;
    vector<int> itemCounts;
    for (int i = 0; i < allItems.size(); i++)
    {
        if (allItems[i]->sellerUsername == currentUser->get_username())
        {
            itemNames.push_back(allItems[i]->name);
            itemCounts.push_back(0);
        }
    }

    if (itemNames.empty())
    {
        cout << "You have no items for sale." << endl;
        return;
    }

    for (int i = 0; i < allTransactions.size(); i++)
    {
        Transaction *t = allTransactions[i];
        if (t->type == "PURCHASE" &&
            t->sellerUsername == currentUser->get_username() &&
            TimeUtil::isLastMonth(t->timestamp))
        {
            int pos = findInVector(itemNames, t->itemName);
            if (pos != -1)
            {
                itemCounts[pos]++;
            }
        }
    }

    bubbleSort(itemNames, itemCounts);

    cout << "\n--- Top " << k << " Your Top Items (Last Month) ---" << endl;
    for (int i = 0; i < k && i < itemNames.size(); i++)
    {
        if (itemCounts[i] > 0)
        {
            cout << i + 1 << ". " << itemNames[i] << " (" << itemCounts[i] << " purchases)" << endl;
        }
    }
}

void Store::seller_loyalCustomers()
{
    vector<string> customerNames;
    vector<int> customerCounts;

    for (int i = 0; i < allTransactions.size(); i++)
    {
        Transaction *t = allTransactions[i];
        if (t->type == "PURCHASE" &&
            t->sellerUsername == currentUser->get_username() &&
            TimeUtil::isLastMonth(t->timestamp))
        {
            int pos = findInVector(customerNames, t->buyerUsername);
            if (pos == -1)
            {
                customerNames.push_back(t->buyerUsername);
                customerCounts.push_back(1);
            }
            else
            {
                customerCounts[pos]++;
            }
        }
    }

    if (customerNames.empty())
    {
        cout << "You had no sales in the last month." << endl;
        return;
    }

    bubbleSort(customerNames, customerCounts);

    cout << "\n--- Your Most Loyal Customers (Last Month) ---" << endl;
    for (int i = 0; i < customerNames.size(); i++)
    {
        cout << i + 1 << ". " << customerNames[i] << " (" << customerCounts[i] << " purchases)" << endl;
    }
}