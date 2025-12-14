#include "authSystem.h"
#include "accountManager.h"
#include <iostream>

using namespace std;

int main() {
    AuthSystem auth;
    
    string loggedInUser = auth.runAuthMenu();

    if (loggedInUser != "") {
        
        AccountManager app(loggedInUser);
        
        cout << "Loading data for user: " << loggedInUser << "...\n";
        app.runMenu();
    
    } else {
        cout << "Exiting application.\n";
    }

    return 0;
}