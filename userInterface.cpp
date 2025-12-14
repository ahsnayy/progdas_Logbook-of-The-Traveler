#include "userInterface.h"
#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

void UserInterface::printMessage(const string& msg) {
    cout << msg << endl;
}

void UserInterface::pause() {
    cout << "\n";
    system("pause");
}

void UserInterface::clearScreen() {
    system("cls");
}

int UserInterface::showMainMenu(const string& statusMessage) {
    clearScreen();

    if (!statusMessage.empty()) {
        cout << "==========================================\n";
        cout << " >> " << statusMessage << "\n";
        cout << "==========================================\n";
    }

    cout << "\n=== GENSHIN ACCOUNT MANAGER ===\n";
    cout << "1. Add Account\n";
    cout << "2. Show All Accounts\n";
    cout << "3. Edit Account\n";
    cout << "4. Delete Account\n";
    cout << "5. Exit\n";
    cout << "Choice: ";
    
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 0;
    }
    return choice;
}

void UserInterface::getNewAccountDetails(string& u, string& uid, string& s, int& ar, int& af) {
    clearScreen();
    cout << "--- Add New Account ---\n";
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    u = getLineInput("Username: ");
    uid = getLineInput("UID: ");
    s = getLineInput("Server: ");
    
    while (true) {
        cout << "Adventure Rank (1-60): ";
        if (cin >> ar) {
            if (ar > 60) {
                cout << ">> Paimon thinks that number is too big! Let's stick to 60, okay?\n";
                ar = 60;
            } else if (ar < 1) {
                cout << ">> Level cannot be zero. Setting to 1.\n";
                ar = 1;
            }
            break;
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid number. Try again.\n";
        }
    }
    cout << "Abyss Floor: ";
    cin >> af;

    if (af > 12) {
        cout << ">> Abyss only goes to 12. Adjusted.\n";
        af = 12;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int UserInterface::selectQuestProgress() {
    cout << "\n--- Select Last Completed Quest ---\n";
    for (size_t i = 0; i < Account::QUEST_LIST.size(); i++) {
        cout << "[" << (i + 1) << "] " << Account::QUEST_LIST[i] << "\n";
    }
    cout << "[" << Account::QUEST_LIST.size() + 1 << "] I have finished everything.\n";
    cout << "[0] New Account (Prologue not done)\n";

    int input;
    while (true) {
        cout << "Enter number: ";
        if (cin >> input) {
            if (input >= 0 && input <= (int)Account::QUEST_LIST.size() + 1) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return input;
            }
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid selection. Try again.\n";
    }
}

void UserInterface::showAllAccounts(const vector<Account>& accounts) {
    clearScreen();
    cout << "\n--- Your Accounts ---\n";
    if (accounts.empty()) {
        cout << "No accounts found.\n";
        return;
    }

    cout << left << setw(4) << "ID" 
         << setw(20) << "Username" 
         << setw(15) << "UID" 
         << setw(15) << "Server" 
         << setw(5) << "AR" 
         << setw(8) << "Abyss" 
         << "Quest Progress" << endl; 
    cout << string(100, '-') << endl; 

    for (size_t i = 0; i < accounts.size(); ++i) {
        int qp = accounts[i].getQuestProgress();
        string questName;

        if (qp == 0) {
            questName = "New Account (Prologue)";
        } 
        else if (qp == (int)Account::QUEST_LIST.size() + 1) {
            questName = "All Content Finished";
        } 
        else if (qp > 0 && qp <= (int)Account::QUEST_LIST.size()) {
            questName = Account::QUEST_LIST[qp - 1]; 
        } 
        else {
            questName = "Unknown";
        }

        cout << left << setw(4) << (i + 1)
             << setw(20) << accounts[i].getUsername()
             << setw(15) << accounts[i].getUid()
             << setw(15) << accounts[i].getServer()
             << setw(5) << accounts[i].getAdventureRank()
             << setw(8) << accounts[i].getAbyssFloors() 
             << questName << endl;
    }
}

int UserInterface::getAccountIndex(int maxIndex) {
    int index;
    cout << "\nEnter Account # ID (0 to cancel): ";
    if (!(cin >> index)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 0;
    }
    return index;
}

int UserInterface::getEditField() {
    int choice;
    cout << "\n1. Username\n2. UID\n3. Server\n4. AR\n5. Abyss Floor\n6. Quest Progress\nChoice: ";
    cin >> choice;
    return choice;
}

bool UserInterface::confirmAction(const string& actionName, const string& targetName) {
    char confirm;
    cout << "Are you sure you want to " << actionName << " account: " << targetName << "? (y/n): ";
    cin >> confirm;
    return (confirm == 'y' || confirm == 'Y');
}

string UserInterface::getLineInput(const string& prompt) {
    string line;
    cout << prompt;
    getline(cin, line);
    return line;
}