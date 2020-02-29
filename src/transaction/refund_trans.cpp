#include <map>
#include <iostream>
#include <string>
#include "transaction.h"
#include "../util/util.h"

using namespace std;

/**
* Verifies a user can perform a transaction
* @param user The user to verify
* @return A boolean of whether or not the user is permitted to perform the transaction
*/
bool RefundTransaction::verify(User* user) {
    if (!user) {
        cout << "Error: Not logged in" <<  endl;
        return false;
    }

    if(user->user_type != "AA"){
        cout << "Error: Transaction not permitted for your user type" << endl;
        return false;
    }

    return true;
}

/**
* Executes the refund transaction
* @param tf The current transactions file
* @param current_user The current user
* @param users The users map
* @return A return code, 0 if successful, non-zero if an error occurs
*/
int RefundTransaction::execute(TransactionFile tf, User* current_user, map<string, User*> users) {
    if (!verify(current_user)) return 1;

    string buyer;
    cout << "Please enter the buyer's username:" << endl;
    getline(cin, buyer);
    map<string, User*>::iterator buyerit = users.find(buyer);
    if(buyerit == users.end()){
        cout << "Error: Username does not exist" << endl;
        return 2;
    } else if(buyerit ->second -> user_type == "SS"){
        cout <<"Error: User is not of type buy-standard" << endl;
        return 1;
    }

    string seller;
    cout << "Please enter the seller's username:" << endl;
    getline(cin, seller);
    map<string, User*>::iterator sellerit = users.find(seller);
    if(sellerit == users.end()){
        cout << "Error: Username does not exist" << endl;
        return 2;
    }else if(sellerit->second->user_type == "BS"){
        cout << "Error: User is not of type sell-standard" << endl;
        return 1;
    }

    string input_amount;
    cout << "Please enter the amount to refund:" << endl;
    getline(cin, input_amount);

    if(!util::is_number(input_amount)){
        cout << "Error: Invalid input" << endl;
        return 5;
    }

    double amount = atof(input_amount.c_str());

    if (amount <= 0){
        cout << "Error: Amount to refund must be greater than zero" << endl;
        return 3;
    } else if((buyerit->second->credit + amount) > 999999.99){
        cout << "Error: Resulting funds exceed limit in buyer's account" << endl;
        return 4;
    } else if(sellerit -> second ->credit < amount){
        cout << "Error: Seller has insufficient funds for refund" << endl;
        return 5;
    }

    tf.write_refund(buyer, seller, amount);
    cout << "Refund successful!" << endl;

    return 0;
}
