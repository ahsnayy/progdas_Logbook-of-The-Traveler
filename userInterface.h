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
   
    void getNewAccountDetails(string& u, string& uid, string& s, int& ar, int& af);
    int selectQuestProgress(); 
    int getAccountIndex(int maxIndex); 
    int getEditField();

    void showAllAccounts(const vector<Account>& accounts);
 
    bool confirmAction(const string& actionName, const string& targetName);

    string getLineInput(const string& prompt);
};


#endif
