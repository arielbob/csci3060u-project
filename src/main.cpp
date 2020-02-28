#include <iostream>
#include <climits>
#include <fstream>
#include <map>
#include <string>
#include <cstdlib>
#include <utility>
#include "user/user.h"
#include "item/item.h"
#include "transaction/transaction.h"
#include "accountsfile/accountsfile.h"
#include "itemsfile/itemsfile.h"
#include "transactionfile/transactionfile.h"

using namespace std;

User* current_user = NULL;

int processTransaction(
    string transaction,
    map<string, User*> users,
    map<pair<string, string>, Item*> items,
    TransactionFile& tf
) {//it read in the User input and process to different cases
    string transactions[10] = {
        "login",
        "logout",
        "create",
        "delete",
        "advertise",
        "bid",
        "refund",
        "addcredit",
        "exit"
    };
    int index = 0;

    for(int i = 0; i < 10; i++){
        index += 1;
        if(transaction == transactions[i]){
            break;
        }
    }

    switch(index){
        case 1:
            LoginTransaction::execute(tf, current_user, users);
            break;

        case 2:
            LogoutTransaction::execute(tf, current_user, users);
            break;

        case 3:
            CreateTransaction::execute(tf, current_user, users);
            break;

        case 4:
            DeleteTransaction::execute(tf, current_user, users);
            break;

        case 5:
            AdvertiseTransaction::execute(tf, current_user, users, items);
            break;

        case 6:
            BidTransaction::execute(tf, current_user, users, items);
            break;

        case 7:
            RefundTransaction::execute(tf, current_user, users);
            break;

        case 8:
            AddCreditTransaction::execute(tf, current_user, users);
            break;

        case 9:
            exit(0);

        default:
            cout << "Transaction Error" << endl;
            break;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage: ./main <accounts file> <items file> <transactions file>" << endl;
        return 1;
    }

    map<string, User*> users = AccountsFile::read(argv[1]);
    map<pair<string, string>, Item*> items = ItemsFile::read(argv[2], users);
    TransactionFile tf;
    tf.open(argv[3]);

    cout << "Welcome to CBay Auctioning System!" << endl;
    while(1){
        string transaction;
        cout << "Please enter a transaction:" << endl;
        // i changed it to getline is it can reading one line of transaction so Add Credit can be read
        getline(cin, transaction);
        processTransaction(transaction, users, items, tf);
        cout << endl;
    }

    return 0;
}
