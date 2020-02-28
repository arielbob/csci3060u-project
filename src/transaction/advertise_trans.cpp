#include <map>
#include <iostream>
#include <string>
#include "../user/user.h"
#include "transaction.h"

using namespace std;

bool AdvertiseTransaction::verify(User* user) {
    if (!user) {
        cout << "Error: Not logged in" << endl;
        return false;
    }

    if(user->user_type != "FS" && user->user_type != "BS"){
        cout << "Error, prohibit to advertise item" << endl;
        return false;
    }

    return true;
}

int AdvertiseTransaction::execute(TransactionFile tf, User* current_user, map<string, User*> users, map<pair<string, string>, Item*> items) {
    if (!verify(current_user)) return 1;

    string item;
    string input_amount;
    string input_days;

    cout << "Please enter the item to advertise:" << endl;
    getline(cin,item);
    if(item.size() > 15){
        cout << "Error! item name is too long.\n";
        return 1;
    }

    pair <string, string> item_seller = make_pair(item, current_user->username);
    map<pair<string, string>, Item*>::iterator itemit = items.find(item_seller);
    if(itemit == items.end()){
    } else {
        cout <<"Error, item duplicated with other items.\n";
        return 2;
    }

    cout << "Please enter the minimum bid for the item:" << endl;
    getline(cin, input_amount);
    double minbid = atof(input_amount.c_str());
    if (minbid > 999.99){
        cout <<"Error, Item price is too high\n";
        return 3;
    }

    cout << "Please enter the number of days until the auction end:" << endl;
    getline(cin, input_days);
    int numofdays = atoi(input_amount.c_str());
    if (numofdays > 100){
        cout <<"days of auction is too long\n";
        return 4;
    }

    return 0;
}