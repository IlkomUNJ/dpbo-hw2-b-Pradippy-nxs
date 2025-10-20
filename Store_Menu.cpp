#include "Store.h"
#include <iostream>
#include <ctime>

void Store::buyer_createBankAccount()
{
    if (findAccount(currentUser->get_username()) != NULL)
    {
        cout << "You already have an account." << endl;
        return;
    }
    allAccounts.push_back(new BankAccount(currentUser->get_username()));
    cout << "Account created." << endl;
}

void Store::showUserMenu()
{
    if (currentUser->getType() == 'S')
    {
        cout << "\n--- Seller Menu (" << currentUser->get_username() << ") ---" << endl;
        cout << "1. Purchase Item" << endl;
        cout << "2. Manage Items (Register, Replenish, etc)" << endl;
        cout << "3. View Seller Analytics" << endl;
        cout << "\n--- Banking (as Seller) ---" << endl;
        cout << "4. Create Bank Account" << endl;
        cout << "5. Deposit Money" << endl;
        cout << "6. Withdraw Money" << endl;
        cout << "7. List My Cash Flow (Today/Month)" << endl;
        cout << "8. List My Past Orders" << endl;
        cout << "9. Check Total Spending (Last K Days)" << endl;
        cout << "0. Back" << endl;
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        if (choice == 1)
            buyer_purchaseItem();
        else if (choice == 2)
            seller_manageItems();
        else if (choice == 3)
            seller_analyticsMenu();
        else if (choice == 4)
            buyer_createBankAccount();
        else if (choice == 5)
            buyer_topUp();
        else if (choice == 6)
            buyer_withdraw();
        else if (choice == 7)
            buyer_listCashFlow();
        else if (choice == 8)
            buyer_listOrders();
        else if (choice == 9)
            buyer_checkSpending();
    }
    else
    {
        cout << "\n--- Buyer Menu (" << currentUser->get_username() << ") ---" << endl;
        cout << "1. Create Bank Account" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Purchase Item" << endl;
        cout << "5. List My Cash Flow (Today/Month)" << endl;
        cout << "6. List My Past Orders" << endl;
        cout << "7. Check Total Spending (Last K Days)" << endl;
        cout << "0. Back" << endl;
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        if (choice == 1)
            buyer_createBankAccount();
        else if (choice == 2)
            buyer_topUp();
        else if (choice == 3)
            buyer_withdraw();
        else if (choice == 4)
            buyer_purchaseItem();
        else if (choice == 5)
            buyer_listCashFlow();
        else if (choice == 6)
            buyer_listOrders();
        else if (choice == 7)
            buyer_checkSpending();
    }
}

void Store::buyer_purchaseItem()
{
    BankAccount *buyerAcc = findAccount(currentUser->get_username());
    if (buyerAcc == NULL)
    {
        cout << "You need a bank account to buy things." << endl;
        return;
    }
    cout << "\n--- Items for Sale ---" << endl;
    for (int i = 0; i < allItems.size(); i++)
    {
        cout << i + 1 << ". " << allItems[i]->name << " ($" << allItems[i]->price << ")" << endl;
    }
    cout << "Enter item number to buy: ";
    int choice;
    cin >> choice;
    if (choice < 1 || choice > allItems.size())
    {
        cout << "Bad choice." << endl;
        return;
    }
    Item *item = allItems[choice - 1];

    if (item->sellerUsername == currentUser->get_username())
    {
        cout << "Can't buy your own item!" << endl;
        return;
    }

    BankAccount *sellerAcc = findAccount(item->sellerUsername);
    if (sellerAcc == NULL)
    {
        cout << "Seller has no bank account, cannot buy." << endl;
        return;
    }

    if (buyerAcc->balance < item->price)
    {
        cout << "Not enough money." << endl;
        return;
    }

    buyerAcc->withdraw(item->price);
    sellerAcc->deposit(item->price);
    item->stock--;

    Transaction *transaction = new Transaction();
    transaction->type = "PURCHASE";
    transaction->buyerUsername = currentUser->get_username();
    transaction->sellerUsername = item->sellerUsername;
    transaction->itemName = item->name;
    transaction->totalPrice = item->price;
    transaction->status = "paid";
    transaction->timestamp = time(0);
    allTransactions.push_back(transaction);

    cout << "Purchase successful!" << endl;
}

void Store::buyer_topUp()
{
    BankAccount *acc = findAccount(currentUser->get_username());
    if (acc == NULL)
    {
        cout << "No bank account." << endl;
        return;
    }
    cout << "Enter amount to deposit: ";
    double amount;
    cin >> amount;
    acc->deposit(amount);

    Transaction *transaction = new Transaction();
    transaction->type = "TOPUP";
    transaction->buyerUsername = currentUser->get_username();
    transaction->totalPrice = amount;
    transaction->timestamp = time(0);
    allTransactions.push_back(transaction);

    cout << "New balance: $" << acc->balance << endl;
}

void Store::seller_registerItem()
{
    cout << "Enter new item name: ";
    string name;
    cin.ignore();
    getline(cin, name);
    cout << "Enter price: ";
    double price;
    cin >> price;
    cout << "Enter stock: ";
    int stock;
    cin >> stock;
    allItems.push_back(new Item(name, price, stock, currentUser->get_username()));
    cout << "Item listed." << endl;
}
