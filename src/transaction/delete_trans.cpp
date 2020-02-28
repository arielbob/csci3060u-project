#include <map>
#include <iostream>
#include <string>
#include "../user/user.h"
#include "transaction.h"

using namespace std;

bool DeleteTransaction::verify(User* user) {
    if (!user) {
        cout << "Error: Not logged in" << endl;
        return false;
    } else if (user->user_type != "AA") {
        cout << "Error: Prohibited to delete accounts" << endl;
        return false;
    }

    return true;
}

int DeleteTransaction::execute(TransactionFile tf, User* current_user, map<string, User*> users) {
    if (!verify(current_user)) return 1;

    string username;
    cout << "Please enter the username:" << endl;
    getline(cin, username);

    map<string, User*>::iterator it = users.find(username);
    if(it == users.end()){
        cout << "Error, username could not found" << endl;
        return 2;
    } else{
        cout << "Account Delete Successful!" << endl;
        return 0;
    }
    //
    // TODO delete transaction
    //

    return 1;
}