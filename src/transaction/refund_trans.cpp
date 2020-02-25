#include <map>
#include <iostream>
#include <string>
#include "transaction.h"

using namespace std;

bool RefundTransaction::verify(User* user) {
    if (!user) {
        cout << "Not logged in" <<  endl;
        return false;
    }

    if(user->user_type != "AA"){
        cout <<"Error, prohibit to process refund" << endl;
        return false;
    }

    return true;
}

int RefundTransaction::execute(User* current_user, map<string, User*> users) {
    if (!verify(current_user)) return 1;

    string buyer;
    string seller;
    string input_amount;

    cout <<"Please enter the buyer's name: ";
    getline(cin, buyer);
    map<string, User*>::iterator buyerit = users.find(buyer);
    if(buyerit == users.end()){
        cout <<"Error: Username does not exist! \n";
        return 2;
    } else if(buyerit ->second -> user_type == "SS"){
        cout <<"Error: User is not of type buy-standard. \n";
        return 1;
    }
    cout <<"Please enter the seller's username: ";
    getline(cin, seller);
    map<string, User*>::iterator sellerit = users.find(seller);
    if(sellerit == users.end()){
        cout <<"Error: Username does not exist! \n";
        return 2;
    }else if(sellerit -> second -> user_type == "SS"){
        cout <<"Error: User is not of type sell-standard.\n";
        return 1;
    }
    cout <<"Please enter the amount to refund: ";
    getline(cin, input_amount);
    double amount = atof(input_amount.c_str());


    if (amount < 0){
        cout <<"Error: Amount to refund must be greater than zero!";
        return 3;
    } else if((sellerit -> second ->credit + amount) >999999.99){
        cout <<"Error: Resulting funds exceed limit in seller's account. \n";
        return 4;
    } else if(sellerit -> second ->credit < amount){
        cout <<"Error: Seller has insufficient funds for refund. \n";
        return 5;
    }
    //
    //TODO refund
    //

    cout <<"Refund Successful! \n";
    return 0;
}