/**
* CSCI3060 Project Frontend
* By: Ariel Bobadilla, Kelly Pham, Liangyu Zhao
*
* This program simulates an auctioning system.
*/

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

/**
* Process a transaction
* @param transaction The transaction
* @param users The users map generated from AccountsFile::read()
* @param items The items map generated from ItemsFile::read()
* @param tf The TransactionsFile object
* @return A return code, 0 if successful, non-zero if an error occurs
*/
int processTransaction(
    string transaction,
    map<string, User*> users,
    map<pair<string, string>, Item*> items,
    TransactionFile& tf
) {
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

    // Read and parse the accounts file and items file
    map<string, User*> users = AccountsFile::read(argv[1]);
    map<pair<string, string>, Item*> items = ItemsFile::read(argv[2], users);
    // Create a TransactionsFile object and open the transactions file
    TransactionFile tf;
    tf.open(argv[3]);

    cout << "Welcome to CBay Auctioning System!" << endl;
    while(1){
        string transaction;
        cout << "Please enter a transaction:" << endl;
        getline(cin, transaction);
        processTransaction(transaction, users, items, tf);
        cout << endl;
    }

    return 0;
}
