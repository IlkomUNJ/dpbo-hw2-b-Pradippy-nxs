#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

class Transaction
{
public:
    string type;
    string buyerUsername;
    string sellerUsername;
    string itemName;
    int quantity;
    double totalPrice;
    string status;
    time_t timestamp;

    Transaction() {}

    void save(ofstream &file) const
    {
        file << type << "|" << buyerUsername << "|" << sellerUsername << "|" << itemName << "|"
             << quantity << "|" << totalPrice << "|" << status << "|" << timestamp << endl;
    }

    void load(ifstream &file)
    {
        getline(file, type, '|');
        if (type.empty())
            return;
        getline(file, buyerUsername, '|');
        getline(file, sellerUsername, '|');
        getline(file, itemName, '|');
        string temp;
        getline(file, temp, '|');
        quantity = stoi(temp);
        getline(file, temp, '|');
        totalPrice = stod(temp);
        getline(file, temp, '|');
        status = temp;
        getline(file, temp);
        timestamp = (time_t)stoll(temp);
    }
};

#endif