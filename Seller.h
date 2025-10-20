#ifndef SELLER_H
#define SELLER_H

#include "Buyer.h"
#include <string>
using namespace std;

class Seller : public Buyer
{
public:
    Seller(const string &username, const string &password)
        : Buyer(username, password)
    {
        userType = 'S';
    };
};

#endif