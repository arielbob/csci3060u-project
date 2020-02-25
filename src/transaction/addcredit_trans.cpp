#include <map>
#include <iostream>
#include <string>
#include "transaction.h"

using namespace std;

bool AddCreditTransaction::verify(User* user) {
    if (!user) {
        cout << "Not logged in" <<  endl;
        return false;
    }

    if(user->user_type != "AA"){
        cout << "Error, prohibit to add credit" <<  endl;
        return false;
    }

    return true;
}

int AddCreditTransaction::execute(User* current_user, map<string, User*> users) {
    if (!verify(current_user)) return 1;

    string username;
    string input_amount;
    cout <<"Please enter the username to add credit to: ";
    getline(cin, username);
    cout <<"Please enter the amount to add: ";
    getline(cin, input_amount);
    double amount = atof(input_amount.c_str());

    map<string, User*>::iterator it = users.find(username);
    if(it == users.end()){
        cout <<"Error: Username does not exist! \n";
        return 2;
    } else if(amount > 1000.0){
        cout <<"Error: Maximum session credit allowance ($1000.00) reached! \n";
        return 1;
    } else if(amount < 0){
        cout <<"Error: Amount to add must be greater than zero! \n";
        return 3;
    } else if((it -> second -> credit + amount) > 999999.99){
        cout <<"Error: Resulting funds exceed limit in users's account. \n";
        return 4;
    }

    cout << "Credit added!" << endl;
    return 0;
    //
    // TODO addcredit
    //
}