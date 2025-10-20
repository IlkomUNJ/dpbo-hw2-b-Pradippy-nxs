#include "Store.h"
#include <fstream>

void Store::saveData()
{
    ofstream userFile("users.txt");
    for (int i = 0; i < allUsers.size(); i++)
    {
        userFile << allUsers[i]->get_username() << " " << allUsers[i]->get_password() << " " << allUsers[i]->getType() << endl;
    }
    userFile.close();

    ofstream accFile("accounts.txt");
    for (int i = 0; i < allAccounts.size(); i++)
    {
        allAccounts[i]->save(accFile);
    }
    accFile.close();

    ofstream itemFile("items.txt");
    for (int i = 0; i < allItems.size(); i++)
    {
        allItems[i]->save(itemFile);
    }
    itemFile.close();

    ofstream transactionFile("transactions.txt");
    for (int i = 0; i < allTransactions.size(); i++)
    {
        allTransactions[i]->save(transactionFile);
    }
    transactionFile.close();
}

void Store::loadData()
{
    ifstream userFile("users.txt");
    string user, pass;
    char type;
    while (userFile >> user >> pass >> type)
    {
        if (type == 'S')
            allUsers.push_back(new Seller(user, pass));
        else
            allUsers.push_back(new Buyer(user, pass));
    }
    userFile.close();

    ifstream accFile("accounts.txt");
    string owner;
    double balance;
    while (accFile >> owner >> balance)
    {
        BankAccount *acc = new BankAccount(owner);
        acc->balance = balance;
        allAccounts.push_back(acc);
    }
    accFile.close();

    ifstream itemFile("items.txt");
    while (itemFile.peek() != EOF)
    {
        Item *item = new Item();
        item->load(itemFile);
        if (!item->name.empty())
            allItems.push_back(item);
        else
            delete item;
    }
    itemFile.close();

    ifstream transactionFile("transactions.txt");
    while (transactionFile.peek() != EOF)
    {
        Transaction *transaction = new Transaction();
        transaction->load(transactionFile);
        if (!transaction->type.empty())
            allTransactions.push_back(transaction);
        else
            delete transaction;
    }
    transactionFile.close();
}