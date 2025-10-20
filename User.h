#ifndef USER_H
#define USER_H

#include <string>
#include <fstream>
#include <vector>

using namespace std;

class User
{
protected:
    string username;
    string password;
    char userType;

public:
    User(const string &username, const string &password, char type)
        : username(username), password(password), userType(type) {};

    ~User() {}

    string get_username() const { return username; };
    string get_password() const { return password; }
    bool check_password(const string &pass) const { return password == pass; }

    char getType() const { return userType; }
};

#endif