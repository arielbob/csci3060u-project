#include <map>
#include <iostream>
#include <string>
#include "../user/user.h"
#include "../util/util.h"
#include "transaction.h"

using namespace std;

bool LoginTransaction::verify(User* user) {
    if (user != NULL) {
        cout << "Error: Already logged in" << endl;
        return false;
    }
    
    return true;
}

int LoginTransaction::execute(TransactionFile tf, User*& current_user, map<string, User*> users) {
    if (!verify(current_user)) return 1;

    string username;
    cout << "Please enter your username:" << endl;
    getline(cin, username);

    if (util::trim_str(username).size() == 0) {
        cout << "Error: Invalid username" << endl;
        return 1;
    }

    map<string, User*>::iterator it = users.find(username);
    if(it == users.end()){
        cout << "Error: Username not found" << endl;
    } else {
        current_user = it->second;
        cout << "Logged in." << endl << endl << "Welcome " << username;
    }

    return 0;
}
