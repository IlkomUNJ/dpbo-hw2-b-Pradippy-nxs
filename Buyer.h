#ifndef BUYER_H
#define BUYER_H

#include "User.h"
#include <string>
#include <vector>

using namespace std;

class Buyer : public User
{
public:
    Buyer(const string &username, const string &password)
        : User(username, password, 'B') {};
};

#endif