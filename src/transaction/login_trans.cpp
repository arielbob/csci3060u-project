#include <map>
#include <iostream>
#include <string>
#include "../user/user.h"
#include "transaction.h"

using namespace std;

bool LoginTransaction::verify(User* user) {
    return user == NULL;
}

int LoginTransaction::execute(TransactionFile tf, User*& current_user, map<string, User*> users) {
    if (!verify(current_user)) {
        cout << "Error: Already logged in" << endl;
        return 1;
    }

    string username;
    cout << "Please enter your username:" << endl;
    getline(cin, username);

    map<string, User*>::iterator it = users.find(username);
    if(it == users.end()){
        cout << "Error: Username not found" << endl;
    } else {
        current_user = it->second;
        cout << "Logged in." << endl << endl << "Welcome " << username;
    }

    return 0;
}
