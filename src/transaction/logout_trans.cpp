#include <map>
#include <iostream>
#include <string>
#include "../user/user.h"
#include "transaction.h"

using namespace std;

/**
* Verifies a user can perform a transaction
* @param user The user to verify
* @return A boolean of whether or not the user is permitted to perform the transaction
*/
bool LogoutTransaction::verify(User* user) {
    if (!user) {
        cout << "Error: Not logged in" << endl;
        return false;
    }

    return true;
}

/**
* Executes the logout transaction
* @param tf The current transactions file
* @param current_user The current user
* @param users The users map
* @return A return code, 0 if successful, non-zero if an error occurs
*/
int LogoutTransaction::execute(TransactionFile tf, User*& current_user, map<string, User*> users) {
    if (!verify(current_user)) return 1;

    //daily transaction file on working
    current_user = NULL;
    cout << "You have logged out" << endl;

    tf.write_end_session();

    return 0;
}
