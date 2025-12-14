#ifndef AUTHSYSTEM_H
#define AUTHSYSTEM_H

#include <string>
#include <functional>

using namespace std;

class AuthSystem {
private:
    const string userFile = "app_users.txt"; 
    bool isLoggedIn;

    void registerUser();
    string loginUser();

    size_t hashPassword(const string& password);

public:
    AuthSystem();
    string runAuthMenu(); 
};

#endif