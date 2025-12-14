#include "accountManager.h"
#include <iostream>
#include <fstream>
#include <sstream> 
#include <limits>

using namespace std;

AccountManager::AccountManager(string user) {
    currentUser = user;
    filename = currentUser + "_data.txt";
    loadFromFile();
}

int AccountManager::selectAccountIndex() {
    ui.showAllAccounts(accountList);
    if (accountList.empty()) return -1;

    int index = ui.getAccountIndex(accountList.size());
    if (index < 1 || index > (int)accountList.size()) return -1;
    
    return index - 1;
}

string AccountManager::addAccount() {
    string u, id, s;
    int ar, af, qp;

    ui.getNewAccountDetails(u, id, s, ar, af);
    qp = ui.selectQuestProgress();

    accountList.emplace_back(u, id, s, ar, af, qp);
    saveToFile();
    
    return "Account added successfully!";
}

void AccountManager::showAllAccounts() {
    ui.showAllAccounts(accountList);
}

void AccountManager::saveToFile() {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& acc : accountList) {
            file << acc.getUsername() << "|" 
                 << acc.getUid() << "|" 
                 << acc.getServer() << "|" 
                 << acc.getAdventureRank() << "|"
                 << acc.getAbyssFloors() << "|"
                 << acc.getQuestProgress() << "\n";
        }
        file.close();
    }
}

void AccountManager::loadFromFile() {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string u, id, s, temp;
            int ar, af, qp;
            
            getline(ss, u, '|');
            getline(ss, id, '|');
            getline(ss, s, '|');
            
            getline(ss, temp, '|'); ar = stoi(temp);
            getline(ss, temp, '|'); af = stoi(temp);
            getline(ss, temp, '|'); qp = stoi(temp);
            
            accountList.emplace_back(u, id, s, ar, af, qp);
        }
        file.close();
    }
}

string AccountManager::editAccount() {
    
    int index = selectAccountIndex();
    if (index == -1) return "Edit cancelled.";

    Account& acc = accountList[index]; 
    
    cout << "\nEditing Account: " << acc.getUsername(); 
    int fieldChoice = ui.getEditField();

    string strInput;
    int intInput;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    switch (fieldChoice) {
        case 1: acc.setUsername(ui.getLineInput("Enter new Username: ")); break;
        case 2: acc.setUid(ui.getLineInput("Enter new UID: ")); break;
        case 3: acc.setServer(ui.getLineInput("Enter new Server: ")); break;
        case 4: 
            cout << "Enter new AR: "; cin >> intInput; 
            acc.setAdventureRank(intInput); break;
        case 5: 
            cout << "Enter new Abyss Floors: "; cin >> intInput; 
            acc.setAbyssFloors(intInput); break;
        case 6: 
            intInput = ui.selectQuestProgress(); 
            acc.setQuestProgress(intInput); break;
        default: return "Invalid edit choice.";
    }

    saveToFile();
    return "Account edited successfully!";
}

string AccountManager::deleteAccount() {
    int index = selectAccountIndex();
    if (index == -1) return "Delete cancelled.";

    if (ui.confirmAction("DELETE", accountList[index].getUsername())) {
        accountList.erase(accountList.begin() + index);
        saveToFile();
        return "Account deleted successfully.";
    } 
    return "Deletion cancelled.";
}

void AccountManager::runMenu() {
    string statusMsg = "";

    while (true) {
        int choice = ui.showMainMenu(statusMsg); 
        
        statusMsg = "";

        switch (choice) {
            case 1: 
                statusMsg = addAccount();
                break; 
            case 2: 
                showAllAccounts(); 
                ui.pause();
                break;
            case 3: 
                statusMsg = editAccount(); 
                break;
            case 4: 
                statusMsg = deleteAccount(); 
                break;
            case 5: 
                ui.printMessage("Exiting..."); 
                return;
            default: 
                statusMsg = "Invalid choice. Please try again.";
        }
    }
}