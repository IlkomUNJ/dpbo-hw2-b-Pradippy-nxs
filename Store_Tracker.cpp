#include "Store.h"

User *Store::findUser(string name)
{
    for (int i = 0; i < allUsers.size(); i++)
    {
        if (allUsers[i]->get_username() == name)
        {
            return allUsers[i];
        }
    }
    return NULL;
}

BankAccount *Store::findAccount(string name)
{
    for (int i = 0; i < allAccounts.size(); i++)
    {
        if (allAccounts[i]->ownerUsername == name)
        {
            return allAccounts[i];
        }
    }
    return NULL;
}

Item *Store::findItem(string name)
{
    for (int i = 0; i < allItems.size(); i++)
    {
        if (allItems[i]->name == name)
        {
            return allItems[i];
        }
    }
    return NULL;
}