#include <iostream>
#include <climits>
#include <fstream>
#include <map>
#include <string>
#include <cstdlib>
#include "user/user.h"
#include "accountsfile/accountsfile.h"
#include "transaction/transaction.h"

using namespace std;

/**
* Trims whitespace from a string
* @param str String to be trimmed
* @return The trimmed string
*/
int create_account(map<string, User*> users);
int logout(map<string, User*> users);
int delete_account(map<string, User*> users);
int add_Credit(map<string, User*> users);
int refund(map<string, User*> users);
int advertise(map<string, User*> users);
int bid(map<string, User*> users);

    //loginstatus used for check if it is logged in
User* currentUser = NULL;

int processTransaction(string transaction,map<string, User*> users){//it read in the User input and process to different cases
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
            if(currentUser == NULL){
                cout <<"Not Logged in" <<endl;
                return -1;
            }
            logout(users);
            //logout function check mark worked
            break;

        case 3:
            if(currentUser == NULL){
                cout <<"Not Logged in" <<endl;
                return -1;
            }
            //create functions check mark worked
            create_account(users);
            break;

        case 4:
            if(currentUser == NULL){
                cout <<"Not Logged in" <<endl;
                return -1;
            }
            delete_account(users);
            //delete functions check mark worked
            break;

        case 5:
            if(currentUser == NULL){
                cout <<"Not Logged in" <<endl;
                return -1;
            }
            advertise(users);
            //advertise functions
            break;

        case 6:
            if(currentUser == NULL){
                cout <<"Not Logged in" <<endl;
                return -1;
            }
            bid(users);
            //bid function
            break;

        case 7:
            if(currentUser == NULL){
                cout <<"Not Logged in" <<endl;
                return -1;
            }
            refund(users);
            //refund functions
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

int logout(map<string, User*> users){ //daily transaction file on working

    cout <<"You have logged out \n";
    //
    //TODO Logout transaction;
    //
    currentUser = NULL;
    return 0;
}

int delete_account(map<string, User*> users){//screw this one
    if(currentUser->user_type != "AA"){
        cout <<"Error, prohibit to delete account \n";
        return -2;
    }

    string username;

    cout <<"Please enter the username: ";
        getline(cin, username);

    map<string, User*>::iterator it = users.find(username);
    if(it == users.end()){
        cout <<"Error, username could not found \n";
        return 2;
    } else{
        cout <<"Account Delete Successful! \n";
        return 0;
    }
    //
    // TODO delete transaction
    //

    return 1;
}

int create_account(map<string, User*> users){//hell screw the END
    if(currentUser->user_type != "AA"){
        cout <<"Error, prohibit to create account \n";
        return -2;
    }

    string username;
    string user_type;

    cout <<"Please enter the username: ";
    getline(cin, username);
    if(username.size() > 15 || username.size() <= 0){
        cout <<"Error, username too long or too short" <<endl;
        return 1;
    }

    map<string, User*>::iterator it = users.find(username);
    if(it == users.end()){
    } else{
        cout <<"Error, username Already been take \n";
        return 2;
    }

    //end of testing username
    cout <<"Please enter the user_type: ";
    getline(cin, user_type);
    if(user_type != "AA" && user_type != "FS" && user_type != "SS" && user_type != "BS"){
        cout <<"Error, user type is invaild" <<endl;
        return 3;
    }
    //end of testing user_type

    cout <<"Account Create Successful! \n";

    //
    // TODO
    //
    return 0;
}

int refund(map<string, User*> users){
    if(currentUser->user_type != "AA"){
        cout <<"Error, prohibit to process refund \n";
        return -2;
    }

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

int advertise(map<string, User*> users){
    if(currentUser->user_type != "FS" && currentUser->user_type != "BS"){
        cout <<"Error, prohibit to advertise item \n";
    }
    string item;
    double minbid;
    int numofdays;

    cout <<"please enter the item to advertise: ";
    cin >> item;
    cout <<"please enter the minimum bid for the item: ";
    cin >>minbid;
    cout <<"please enter the number of days until the auction end: ";
    cin >>numofdays;

    return 0;
}

int bid(map<string, User*> users){
    if(currentUser->user_type != "BS" && currentUser->user_type != "BS"){
        cout <<"Error, prohibit to Bid item \n";
    }
    string item;
    string seller;
    double bid_amount;


    cout <<"Please enter the item name: ";
    cin >> item;
    cout <<"Please enter the seller's username: ";
    cin >>seller;
    cout <<"Current highest bid for guitar: $300.00 \n";
    cout <<"Please enter a new bid amount: ";
    cin >>bid_amount;

    return 0;
}

int add_Credit(map<string, User*> users){
    if(currentUser->user_type != "AA"){
        cout <<"Error, prohibit to Add Credit \n";
        return -2;
    }

    string username;
    string input_amount = 0;
    cout <<"Please enter the username to add credit to: ";
    cin >>username;
    cout <<"Please enter the amount to add: ";
    getline(cin, input_amount);
    double amount = atof(input_amount.c_str());
    cout <<"Credit Added ";

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

    while(1){
        string transaction;
        cout << "Welcome to CBay Auctioning System!" << endl;
        cout << "Please enter a transaction: ";
        // i changed it to getline is it can reading one line of transaction so Add Credit can be read
        // cout << "transaction entered: " << transaction << endl;
        if (getline(cin, transaction)) {
            processTransaction(transaction,users);
        }
        cout <<endl;
    }
    return 0;
}
