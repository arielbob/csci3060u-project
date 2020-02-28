#include <map>
#include <iostream>
#include <string>
#include "../user/user.h"
#include "transaction.h"

using namespace std;

bool LogoutTransaction::verify(User* user) {
    if (!user) {
        cout << "Error: Not logged in" << endl;
        return false;
    }

    return true;
}

int LogoutTransaction::execute(TransactionFile tf, User*& current_user, map<string, User*> users) {
    if (!verify(current_user)) return 1;

    //daily transaction file on working
    current_user = NULL;
    cout << "You have logged out \n";
    //
    //TODO Logout transaction;
    //
    return 0;
}