#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include "account.h"
#include "userInterface.h"
#include <vector>
#include <string>

using namespace std;

class AccountManager {
private:
    vector<Account> accountList;
    UserInterface ui;
    string currentUser; 
    string filename;  
    
    void loadFromFile();
    void saveToFile();

public:
    AccountManager(string user);
    void runMenu();

    string addAccount();
    void showAllAccounts();
    string editAccount();
    string deleteAccount();
    int selectAccountIndex();

};

#endif