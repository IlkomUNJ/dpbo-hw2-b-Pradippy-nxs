#include "Store.h"
#include <iostream>

void Store::user_register()
{
    cout << "Enter new username: ";
    string user;
    cin >> user;
    if (findUser(user) != NULL)
    {
        cout << "Username taken." << endl;
        return;
    }
    cout << "Enter new password: ";
    string pass;
    cin >> pass;
    cout << "Register as (1) Buyer or (2) Seller: ";
    int type;
    cin >> type;
    if (type == 2)
    {
        allUsers.push_back(new Seller(user, pass));
        cout << "Seller registered." << endl;
    }
    else
    {
        allUsers.push_back(new Buyer(user, pass));
        cout << "Buyer registered." << endl;
    }
}

void Store::user_login()
{
    cout << "Enter username: ";
    string user;
    cin >> user;
    cout << "Enter password: ";
    string pass;
    cin >> pass;
    User *found = findUser(user);
    if (found != NULL && found->check_password(pass))
    {
        currentUser = found;
        cout << "Login successful." << endl;
    }
    else
    {
        cout << "Wrong username or password." << endl;
    }
}