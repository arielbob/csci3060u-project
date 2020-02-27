#include <map>
#include <iostream>
#include <string>
#include "transaction.h"

using namespace std;

bool BidTransaction::verify(User* user) {
    if (!user) {
        cout << "Not logged in" <<  endl;
        return false;
    }

    // QUESTION: are admins allowed to bid?
    if(user->user_type != "BS" && user->user_type != "FS"){
        cout << "Error, prohibit to Bid item" <<  endl;
        return false;
    }

    return true;
}

int BidTransaction::execute(TransactionFile tf, User* current_user, map<string, User*> users, map<pair<string, string>, Item*> items) {
    if (!verify(current_user)) return 1;

    string item;
    string seller;
    string input_amount;

    cout << "Please enter the item name:" << endl;
    getline(cin, item);
    cout << "Please enter the seller's username:" << endl;
    getline(cin, seller);


    pair <string, string> item_seller = make_pair(item,seller);
    map<pair<string, string>, Item*>::iterator itemit = items.find(item_seller);
    if(itemit == items.end()){
        cout << "Error, cannot find the items \n";
        return 2;
    } else {
        cout << "Current highest bid for "<<  item << ": $"<< itemit -> second -> current_bid -> amount << endl;
    }
    cout << "Please enter a new bid amount:" << endl;
    getline(cin, input_amount);
    double amount = atof(input_amount.c_str());
    if (amount <= itemit -> second -> current_bid -> amount){
        cout << "Error: Bid must be higher than current highest bid. \n";
    } else if (amount < itemit -> second -> current_bid -> amount * 1.05){
        cout << "Error: Bid must be at least 5% higher than current highest bid. \n";
    }
    cout << "bid entered";

    return 0;
}