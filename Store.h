#ifndef STORE_H
#define STORE_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "User.h"
#include "Buyer.h"
#include "Seller.h"
#include "BankAccount.h"
#include "Item.h"
#include "Transaction.h"

using namespace std;

class Store
{
private:
    vector<User *> allUsers;
    vector<BankAccount *> allAccounts;
    vector<Item *> allItems;
    vector<Transaction *> allTransactions;

    User *currentUser;

public:
    Store();
    ~Store();
    void run();

private:
    void loadData();
    void saveData();

    User *findUser(string name);
    BankAccount *findAccount(string name);
    Item *findItem(string name);

    void showMainMenu(); 
    void showUserMenu();
    void showBankMenu();
    void showStoreMenu();

    void user_register();
    void user_login();


    void buyer_createBankAccount();
    void buyer_topUp();
    void buyer_purchaseItem();
    void seller_registerItem();

    void buyer_withdraw();
    void buyer_listCashFlow();
    void buyer_listOrders();
    void buyer_checkSpending();


    void seller_manageItems();
    void seller_analyticsMenu();


    void bank_listTransactionsLastWeek();
    void bank_topNUsersToday();


    void store_manageTransactions();
    void store_listTransactionsKDays();
    void store_mostFrequentItems();
    void store_mostActiveUsers();


    void seller_replenishStock();
    void seller_discardItem();
    void seller_changePrice(); 


    void seller_topKItems();
    void seller_loyalCustomers();
};

#endif 