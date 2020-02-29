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
        cout << "Error: Transaction not permitted for your user type" << endl;
        return false;
    }

    return true;
}

int DeleteTransaction::execute(TransactionFile tf, User* current_user, map<string, User*> users) {
    if (!verify(current_user)) return 1;

    string username;
    cout << "Please enter the username to delete:" << endl;
    getline(cin, username);

    map<string, User*>::iterator it = users.find(username);
    if(it == users.end()){
        cout << "Error: Username could not found" << endl;
        return 2;
    }

    tf.write_delete_account(username);
    cout << "Account delete successful!" << endl;

    return 0;
}
