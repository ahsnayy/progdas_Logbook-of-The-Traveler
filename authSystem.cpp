#include "authSystem.h"
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

AuthSystem::AuthSystem() : isLoggedIn(false) {}

size_t AuthSystem::hashPassword(const string& password) {
    hash<string> hasher;
    return hasher(password);
}

void AuthSystem::registerUser() {
    string u, p;
    cout << "\n--- Register New User ---\n";
    cout << "Enter new username (No spaces): ";
    cin >> u;
    cout << "Enter new password (No spaces): ";
    cin >> p;

    size_t passwordHash = hashPassword(p);

    ofstream file(userFile, ios::app); 
    if (file.is_open()) {
        file << u << " " << passwordHash << "\n";
        file.close();
        cout << "Registration successful! You can now login.\n";
    } else {
        cout << "Error: Could not save user data.\n";
    }
}

string AuthSystem::loginUser() {
    string inputUser, inputPass;
    string fileUser;
    size_t filePassHash;
    
    cout << "\n--- Login ---\n";
    cout << "Username: ";
    cin >> inputUser;
    cout << "Password: ";
    cin >> inputPass;

    size_t inputHash = hashPassword(inputPass);

    ifstream file(userFile);
    if (file.is_open()) {
        while (file >> fileUser >> filePassHash) {
            if (fileUser == inputUser && filePassHash == inputHash) {
                cout << "Login successful! Welcome, " << inputUser << ".\n";
                return inputUser;
            }
        }
        file.close();
    }
    cout << "Invalid username or password.\n";
    return "";
}

string AuthSystem::runAuthMenu() {
    string activeUser;
    int choice;

    while (!isLoggedIn) {
        system("cls");

        cout << "\n=== WELCOME TO GENSHIN MANAGER ===\n";
        cout << "1. Login\n2. Register\n3. Exit\nChoice: ";

        if (!(cin >> choice)) {
             cin.clear();
             cin.ignore(numeric_limits<streamsize>::max(), '\n');
             continue;
        }
        
        switch (choice) {
            case 1:
                activeUser = loginUser();
                if (activeUser != "") {   
                    isLoggedIn = true;
                    return activeUser; 
                }
                break;
            case 2:
                registerUser();
                break;
            case 3:
                return ""; 
            default:
                cout << "Invalid choice.\n";
        }

        cout << "\n";
        system("pause");
    }
    return activeUser;
}