#include <map>
#include <iostream>
#include <string>
#include "transaction.h"
#include "../util/util.h"

using namespace std;

map<string, double> AddCreditTransaction::daily_max;

bool AddCreditTransaction::verify(User* user) {
    if (!user) {
        cout << "Error: Not logged in" <<  endl;
        return false;
    }

    return true;
}


int AddCreditTransaction::execute(TransactionFile tf, User* current_user, map<string, User*> users) {
    if (!verify(current_user)) return 1;

    string username;
    string input_amount;

    if (current_user->user_type == "AA") {
        cout << "Please enter the username to add credit to:" << endl;
        getline(cin, username);
    } else {
        username = current_user->username;
    }

    map<string, User*>::iterator it = users.find(username);
    if(it == users.end()){
        cout <<"Error: Username does not exist!" <<endl;
        return 2;
    }

    cout << "Please enter the amount to add:" << endl;
    getline(cin, input_amount);
    if (!util::isNumber(input_amount)){
        cout <<"Error: Invalid input\n";
        return 5;
    }

    double amount = atof(input_amount.c_str());

    map<string, double>::iterator dailyit = daily_max.find(username);
    if(dailyit == daily_max.end()){
        daily_max.insert(pair<string,double>(username, amount));
    }
    //dailyit -> second = dailyit -> second + amount;
    if (dailyit->second + amount > 1000){
        cout <<"Error: Maximum session credit allowance ($1000.00) reached!\n";
        return 1;
    }

    if(amount <= 0){
        cout <<"Error: Amount to add must be greater than zero!\n";
        return 3;
    } else if((it -> second -> credit + amount) > 999999.99){
        cout <<"Error: Resulting funds exceed limit in users's account.\n";
        return 4;
    }

    tf.write_add_credit(username, amount);

    cout << "Credit added!" << endl;
    return 0;
    //
    // TODO addcredit
    //
}
