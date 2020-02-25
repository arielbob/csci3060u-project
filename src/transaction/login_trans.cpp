#include <map>
#include <iostream>
#include <string>
#include "../user/user.h"
#include "transaction.h"

using namespace std;

bool LoginTransaction::verify(User* user) {
    return user == NULL;
}

int LoginTransaction::execute(User*& current_user, map<string, User*> users) {
    if (!verify(current_user)) {
        cout << "Already logged in" << endl;
        return 1;
    }

    string username;
    cout << "Please enter your username: ";
    getline(cin, username);

    map<string, User*>::iterator it = users.find(username);
    if(it == users.end()){
        cout << "Error, username not found";
    }else{
        current_user = it->second;
        cout << "You are Logged in \n";
    }

    return 0;
}