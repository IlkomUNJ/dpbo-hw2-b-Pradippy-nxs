#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class BankAccount
{
public:
    string ownerUsername;
    double balance;

    BankAccount() : ownerUsername(""), balance(0.0) {}
    BankAccount(const string &username) : ownerUsername(username), balance(0.0) {};

    void deposit(double amount)
    {
        balance += amount;
    }
    void withdraw(double amount)
    {
        balance -= amount;
    }

    void save(ofstream &file) const
    {
        file << ownerUsername << " " << balance << endl;
    }
};

#endif
