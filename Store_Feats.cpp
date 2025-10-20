#include "Store.h"
#include "Timer.h"
#include <iostream>
#include <string>
#include <limits>

void Store::buyer_withdraw()
{
    BankAccount *acc = findAccount(currentUser->get_username());
    if (acc == NULL)
    {
        cout << "You must have a bank account to withdraw." << endl;
        return;
    }
    cout << "Enter amount to withdraw: ";
    double amount;
    cin >> amount;
    if (amount > acc->balance)
    {
        cout << "Insufficient funds. Your balance is $" << acc->balance << endl;
        return;
    }

    acc->withdraw(amount);

    Transaction *transaction = new Transaction();
    transaction->type = "WITHDRAW";
    transaction->buyerUsername = currentUser->get_username();
    transaction->totalPrice = amount;
    transaction->timestamp = time(0);
    allTransactions.push_back(transaction);

    cout << "Withdrawal successful. New balance: $" << acc->balance << endl;
}

void Store::buyer_listCashFlow()
{
    cout << "\n--- Cash Flow for " << currentUser->get_username() << " ---" << endl;
    cout << "--- Today ---" << endl;
    bool foundToday = false;
    for (int i = 0; i < allTransactions.size(); i++)
    {
        Transaction *t = allTransactions[i];
        if (t->buyerUsername == currentUser->get_username() && TimeUtil::isToday(t->timestamp))
        {
            if (t->type == "TOPUP")
                cout << "[Credit] +$" << t->totalPrice << " (Deposit)" << endl;
            else if (t->type == "PURCHASE")
                cout << "[Debit] -$" << t->totalPrice << " (Purchase: " << t->itemName << ")" << endl;
            else if (t->type == "WITHDRAW")
                cout << "[Debit] -$" << t->totalPrice << " (Withdrawal)" << endl;
            foundToday = true;
        }
    }
    if (!foundToday)
        cout << "No transactions today." << endl;

    cout << "\n--- Last Month ---" << endl;
    bool foundMonth = false;
    for (int i = 0; i < allTransactions.size(); i++)
    {
        Transaction *t = allTransactions[i];
        if (t->buyerUsername == currentUser->get_username() && TimeUtil::isLastMonth(t->timestamp))
        {
            if (t->type == "TOPUP")
                cout << "[Credit] +$" << t->totalPrice << " (Deposit)" << endl;
            else if (t->type == "PURCHASE")
                cout << "[Debit] -$" << t->totalPrice << " (Purchase: " << t->itemName << ")" << endl;
            else if (t->type == "WITHDRAW")
                cout << "[Debit] -$" << t->totalPrice << " (Withdrawal)" << endl;
            foundMonth = true;
        }
    }
    if (!foundMonth)
        cout << "No transactions in the last month." << endl;
}

void Store::buyer_listOrders()
{
    cout << "Filter by status (paid, completed, cancelled, or 'all'): ";
    string filter;
    cin >> filter;

    cout << "\n--- Past Orders for " << currentUser->get_username() << " ---" << endl;
    bool found = false;
    for (int i = 0; i < allTransactions.size(); i++)
    {
        Transaction *t = allTransactions[i];
        if (t->type == "PURCHASE" && t->buyerUsername == currentUser->get_username())
        {
            if (filter == "all" || t->status == filter)
            {
                cout << "Item: " << t->itemName << " | Price: $" << t->totalPrice
                     << " | Status: " << t->status << " | Date: " << TimeUtil::a_time_t_to_string(t->timestamp) << endl;
                found = true;
            }
        }
    }
    if (!found)
        cout << "No orders found with filter '" << filter << "'." << endl;
}

void Store::buyer_checkSpending()
{
    cout << "Enter number of days (k) to check spending for: ";
    int k;
    cin >> k;

    double totalSpent = 0;
    for (int i = 0; i < allTransactions.size(); i++)
    {
        Transaction *t = allTransactions[i];
        if (t->type == "PURCHASE" && t->buyerUsername == currentUser->get_username() && TimeUtil::isLastKDays(t->timestamp, k))
        {
            totalSpent += t->totalPrice;
        }
    }
    cout << "Total spending in the last " << k << " days: $" << totalSpent << endl;
}

void Store::seller_manageItems()
{
    cout << "\n--- Item Management ---" << endl;
    cout << "1. Register New Item" << endl;
    cout << "2. Replenish Stock for Existing Item" << endl;
    cout << "3. Discard Item (Set stock to 0)" << endl;
    cout << "4. Change Item Price" << endl;
    cout << "0. Back" << endl;
    int choice;
    cin >> choice;

    if (choice == 1)
        seller_registerItem();
    else if (choice == 2)
        seller_replenishStock();
    else if (choice == 3)
        seller_discardItem();
    else if (choice == 4)
        seller_changePrice();
}

Item *getSellerItemChoice(vector<Item *> &allItems, string sellerUsername)
{
    cout << "\n--- Your Items ---" << endl;
    vector<Item *> myItems;
    for (int i = 0; i < allItems.size(); i++)
    {
        if (allItems[i]->sellerUsername == sellerUsername)
        {
            cout << myItems.size() + 1 << ". " << allItems[i]->name
                 << " (Stock: " << allItems[i]->stock << ", Price: $" << allItems[i]->price << ")" << endl;
            myItems.push_back(allItems[i]);
        }
    }
    if (myItems.empty())
    {
        cout << "You have no items for sale." << endl;
        return NULL;
    }
    cout << "Enter item number: ";
    int choice;
    cin >> choice;
    if (choice < 1 || choice > myItems.size())
    {
        cout << "Invalid choice." << endl;
        return NULL;
    }
    return myItems[choice - 1];
}

void Store::seller_replenishStock()
{
    Item *itemToUpdate = getSellerItemChoice(allItems, currentUser->get_username());
    if (itemToUpdate == NULL)
        return;

    cout << "Enter amount to add: ";
    int amount;
    cin >> amount;
    if (amount < 0)
        amount = 0;
    itemToUpdate->addStock(amount);
    cout << itemToUpdate->name << " stock is now " << itemToUpdate->stock << "." << endl;
}

void Store::seller_discardItem()
{
    Item *itemToUpdate = getSellerItemChoice(allItems, currentUser->get_username());
    if (itemToUpdate == NULL)
        return;

    itemToUpdate->stock = 0;
    cout << itemToUpdate->name << " stock has been set to 0." << endl;
}

void Store::seller_changePrice()
{
    Item *itemToUpdate = getSellerItemChoice(allItems, currentUser->get_username());
    if (itemToUpdate == NULL)
        return;

    cout << "Enter new price for " << itemToUpdate->name << ": ";
    double newPrice;
    cin >> newPrice;
    if (newPrice < 0)
        newPrice = 0;

    itemToUpdate->price = newPrice;
    cout << itemToUpdate->name << " price is now $" << itemToUpdate->price << endl;
}

void Store::seller_analyticsMenu()
{
    cout << "\n--- Seller Analytics ---" << endl;
    cout << "1. Top K Most Popular Items (Last Month)" << endl;
    cout << "2. Most Loyal Customers (Last Month)" << endl;
    cout << "0. Back" << endl;
    int choice;
    cin >> choice;
    if (choice == 1)
        seller_topKItems();
    else if (choice == 2)
        seller_loyalCustomers();
}

void Store::bank_listTransactionsLastWeek()
{
    cout << "\n--- Transactions (Last Week) ---" << endl;
    bool found = false;
    for (int i = 0; i < allTransactions.size(); i++)
    {
        if (TimeUtil::isLastWeek(allTransactions[i]->timestamp))
        {
            Transaction *t = allTransactions[i];
            cout << t->type << " | Buyer: " << t->buyerUsername << " | Seller: " << t->sellerUsername
                 << " | Item: " << t->itemName << " | Amount: $" << t->totalPrice << endl;
            found = true;
        }
    }
    if (!found)
        cout << "No transactions in the last week." << endl;
}

void Store::store_manageTransactions()
{
    cout << "\n--- Manage Transactions (Status: paid) ---" << endl;
    vector<Transaction *> paidTransactions;
    for (int i = 0; i < allTransactions.size(); i++)
    {
        if (allTransactions[i]->status == "paid")
        {
            Transaction *t = allTransactions[i];
            cout << paidTransactions.size() + 1 << ". Item: " << t->itemName << " | Buyer: " << t->buyerUsername
                 << " | Date: " << TimeUtil::a_time_t_to_string(t->timestamp) << endl;
            paidTransactions.push_back(t);
        }
    }
    if (paidTransactions.empty())
    {
        cout << "No 'paid' transactions to manage." << endl;
        return;
    }
    cout << "Enter transaction number to update: ";
    int choice;
    cin >> choice;
    if (choice < 1 || choice > paidTransactions.size())
    {
        cout << "Invalid choice." << endl;
        return;
    }
    Transaction *transactionToUpdate = paidTransactions[choice - 1];

    cout << "Enter new status (completed, cancelled): ";
    string newStatus;
    cin >> newStatus;

    if (newStatus == "completed" || newStatus == "cancelled")
    {
        transactionToUpdate->status = newStatus;
        cout << "Transaction status updated to '" << newStatus << "'." << endl;
    }
    else
    {
        cout << "Invalid status." << endl;
    }
}

void Store::store_listTransactionsKDays()
{
    cout << "Enter number of days (k): ";
    int k;
    cin >> k;
    cout << "\n--- Transactions (Last " << k << " Days) ---" << endl;
    bool found = false;
    for (int i = 0; i < allTransactions.size(); i++)
    {
        if (TimeUtil::isLastKDays(allTransactions[i]->timestamp, k))
        {
            Transaction *t = allTransactions[i];
            cout << t->type << " | Buyer: " << t->buyerUsername << " | Seller: " << t->sellerUsername
                 << " | Amount: $" << t->totalPrice << " | Status: " << t->status << endl;
            found = true;
        }
    }
    if (!found)
        cout << "No transactions in the last " << k << " days." << endl;
}