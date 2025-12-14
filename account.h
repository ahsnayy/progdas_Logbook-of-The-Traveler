#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>

using namespace std;

class Account {
private:
    string username;
    string uid;
    string server;
    int adventureRank;
    int abyssFloors;
    int questProgress;

public:
    static const vector<string> QUEST_LIST;

    Account(string u, string id, string s, int ar, int af, int qp);
    
    string getUsername() const;
    string getUid() const;
    string getServer() const;
    int getAdventureRank() const;
    int getAbyssFloors() const;
    int getQuestProgress() const;

    void setUsername(string newName);
    void setUid(string newUid);
    void setServer(string newServer);
    void setAdventureRank(int newAr);
    void setAbyssFloors(int newFloors);
    void setQuestProgress(int newQp);
    
};

#endif