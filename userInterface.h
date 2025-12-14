#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "account.h"
#include <vector>
#include <string>

using namespace std;

class UserInterface {
public:
    void printMessage(const string& msg);
    void pause();
    void clearScreen();
    int showMainMenu(const string& statusMessage = "");
    
    // Inputs
    void getNewAccountDetails(string& u, string& uid, string& s, int& ar, int& af);
    int selectQuestProgress(); 
    int getAccountIndex(int maxIndex); // Helper for Edit/Delete
    int getEditField();
    
    // Outputs
    void showAllAccounts(const vector<Account>& accounts);
    
    // Confirmations
    bool confirmAction(const string& actionName, const string& targetName);
    
    // Input Helper
    string getLineInput(const string& prompt);
};

#endif