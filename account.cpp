#include "account.h"

using namespace std;

const vector<string> Account::QUEST_LIST = {
    "Prologue: The Outlander Who Caught the Wind [Mondstadt]",
    "Chapter I: Farewell, Archaic Lord [Liyue]",
    "Interlude Chapter: Act I - The Crane Returns on the Wind [Liyue]",
    "Interlude Chapter: Act II - Perilous Trails [Liyue]",
    "Chapter II: Omnipresence Over Mortals [Inazuma]",
    "Chapter III: Truth Amongst the Pages of Purana [Sumeru]",
    "Interlude Chapter: Act III - Inversion of Genesis [Sumeru]",
    "Chapter IV: Masquerade of the Guilty [Fontaine]",
    "Chapter V: Incandescent Ode of Resurrection [Natlan]",
    "Interlude Chapter: Act IV - Paralogism [Mondstadt]",
    "Song of the Welkin Moon [Nod Krai]",
};

Account::Account(string u, string id, string s, int ar, int af, int qp) 
    : username(u), uid(id), server(s), adventureRank(ar), abyssFloors(af), questProgress(qp) {}

string Account::getUsername() const { return username; }
string Account::getUid() const { return uid; }
string Account::getServer() const { return server; }
int Account::getAdventureRank() const { return adventureRank; }
int Account::getAbyssFloors() const { return abyssFloors; }
int Account::getQuestProgress() const { return questProgress; }

void Account::setUsername(string newName) {
     username = newName; 
}

void Account::setUid(string newUid) { 
    uid = newUid; 
}

void Account::setServer(string newServer) {
    server = newServer; 
}

void Account::setAdventureRank(int newAr) {
    if (newAr < 1) {
        adventureRank = 1;
    } else if (newAr > 60) {
        adventureRank = 60;
    } else {
        adventureRank = newAr;
    }
}

void Account::setAbyssFloors(int newFloors) {
    if (newFloors < 1) abyssFloors = 1;
    else if (newFloors > 12) abyssFloors = 12;
    else abyssFloors = newFloors;
}

void Account::setQuestProgress(int newQp) {
    questProgress = newQp; 
}