#include "Store.h"
#include <iostream>
#include <limits> 

Store::Store()
{
    currentUser = NULL;
    loadData();
    cout << "Welcome to Store!" << endl;
}

Store::~Store()
{
    saveData();
    for (int i = 0; i < allUsers.size(); i++)
        delete allUsers[i];
    for (int i = 0; i < allAccounts.size(); i++)
        delete allAccounts[i];
    for (int i = 0; i < allItems.size(); i++)
        delete allItems[i];
    for (int i = 0; i < allTransactions.size(); i++)
        delete allTransactions[i];
    cout << "Data saved. Store closed." << endl;
}

void Store::run()
{
    bool running = true;
    while (running)
    {
        cout << "\n" << endl;
        if (currentUser == NULL)
        {
            cout << "1. Login\n2. Register\n5. Bank Menu (Admin)\n6. Store Menu (Admin)\n0. Exit" << endl;
        }
        else
        {
            cout << "Logged in as: " << currentUser->get_username() << endl;
            cout << "3. My Menu\n4. Logout\n5. Bank Menu (Admin)\n6. Store Menu (Admin)\n0. Exit" << endl;
        }
        cout << "--------------------" << endl;
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        if (cin.fail())
        {
            cout << "Not a number!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1)
            user_login();
        else if (choice == 2)
            user_register();
        else if (choice == 3 && currentUser != NULL)
            showUserMenu();
        else if (choice == 4 && currentUser != NULL)
        {
            cout << "Logging out." << endl;
            currentUser = NULL;
        }
        else if (choice == 5)
            showBankMenu();
        else if (choice == 6)
            showStoreMenu();
        else if (choice == 0)
            running = false;
        else
            cout << "Invalid choice." << endl;
    }
}