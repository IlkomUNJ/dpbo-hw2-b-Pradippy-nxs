#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <fstream>

using namespace std;

class Item
{
public:
    string name;
    double price;
    int stock;
    string sellerUsername;

    Item() : name(""), price(0.0), stock(0), sellerUsername("") {}
    Item(const string &name, double price, int stock, const string &seller)
        : name(name), price(price), stock(stock), sellerUsername(seller) {}

    void addStock(int amount)
    {
        stock += amount;
    }

    void save(ofstream &file) const
    {
        file << name << "|" << price << "|" << stock << "|" << sellerUsername << endl;
    }

    void load(ifstream &file)
    {
        getline(file, name, '|');
        if (name.empty())
            return;
        string temp;
        getline(file, temp, '|');
        price = stod(temp);
        getline(file, temp, '|');
        stock = stoi(temp);
        getline(file, sellerUsername);
    }
};

#endif