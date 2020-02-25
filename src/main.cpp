#include <iostream>
#include <climits>
#include <fstream>
#include <map>
#include <string>
#include <cstdlib>
#include <utility>
#include "user/user.h"
#include "accountsfile/accountsfile.h"
#include "transaction/transaction.h"
#include "item/item.h"
#include "accountsfile/accountsfile.h"
#include "itemsfile/itemsfile.h"
#include "transactionfile/transactionfile.h"

using namespace std;

int add_Credit(map<string, User*> users);

User* currentUser = NULL;

int processTransaction(string transaction,map<string, User*> users, map<pair<string, string>, Item*> items){//it read in the User input and process to different cases
    string transactions[10] = {"login","logout","create","delete","advertise","bid","refund","add credit","exit"};
    int index = 0;

    for(int i = 0; i < 10; i++){
        index += 1;
        if(transaction == transactions[i]){
            break;
        }
    }

    switch(index){
        case 1:
            LoginTransaction::execute(currentUser, users);
            break;

        case 2:
            LogoutTransaction::execute(currentUser, users);
            break;

        case 3:
            CreateTransaction::execute(currentUser, users);
            break;

        case 4:
            DeleteTransaction::execute(currentUser, users);
            break;

        case 5:
            AdvertiseTransaction::execute(currentUser, users, items);
            break;

        case 6:
            BidTransaction::execute(currentUser, users, items);
            break;

        case 7:
            RefundTransaction::execute(currentUser, users);
            break;

        case 8:
            if(currentUser == NULL){
                cout <<"Not Logged in" <<endl;
                return -1;
            }
            add_Credit(users);
            //add creidt functions
            break;

        case 9:
            exit(0);

        default:
            cout <<"Transaction Error" <<endl;
            break;
    }
    return 0;
}
//use int so i can have a check if the return value is correct it is a basic version of delete.
//need to pass one more argument user, so we can check the user typecheck if the current user is the Admin account.

int add_Credit(map<string, User*> users){
    if(currentUser->user_type != "AA"){
        cout <<"Error, prohibit to Add Credit \n";
        return -2;
    }

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
    cout <<"Credit added! \n";
        return 0;
    //
    // TODO addcredit
    //
}


void init(){
    system("clear");
}

int main() {
    init();
    map<string, User*> users = AccountsFile::read();
    map<pair<string, string>, Item*> items = ItemsFile::read(users);

    while(1){
        string transaction;
        cout << "Welcome to CBay Auctioning System!" << endl;
        cout << "Please enter a transaction: ";
        // i changed it to getline is it can reading one line of transaction so Add Credit can be read
        // cout << "transaction entered: " << transaction << endl;
        if (getline(cin, transaction)) {
            processTransaction(transaction, users, items);
        }
        cout <<endl;
    }
    return 0;
}
