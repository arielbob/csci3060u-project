#include <map>
#include <iostream>
#include <string>
#include "transaction.h"
#include "../util/util.h"

using namespace std;

bool BidTransaction::verify(User* user) {
    if (!user) {
        cout << "Error: Not logged in" <<  endl;
        return false;
    }

    // QUESTION: are admins allowed to bid?
    if(user->user_type != "BS" && user->user_type != "FS" && user->user_type != "AA"){
        cout << "Error: Transaction not permitted for your user type" <<  endl;
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
        cout << "Error: Item not found" <<endl;
        return 2;
    } else {
        cout << "Current highest bid for "<<  item << ": $"<< itemit -> second -> current_bid -> amount << endl;
    }
    cout << "Please enter a new bid amount:" << endl;

    getline(cin, input_amount);
    double amount = atof(input_amount.c_str());

    if(!util::isNumber(input_amount)){
        cout <<"Error: Invalid input\n";
        return 5;
    }

    if (amount <= itemit -> second -> current_bid -> amount){
        cout << "Error: Bid must be higher than current highest bid\n";
        return 3;
    } else if (amount < itemit -> second -> current_bid -> amount * 1.05){
        if (current_user -> user_type != "AA"){
            cout << "Error: Bid must be at least 5% higher than current highest bid\n";
            return 4;
        }
    }

    tf.write_bid(item, seller, current_user->username, amount);
    cout << "Bid entered!" <<endl;

    return 0;
}
