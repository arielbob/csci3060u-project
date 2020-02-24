#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cstdlib>
#include "user/user.h"
#include "accountsfile/accountsfile.h"

using namespace std;

/**
* Trims whitespace from a string
* @param str String to be trimmed
* @return The trimmed string
*/
int create_account(map<string, User*> users);
int login(map<string, User*> users);
int logout(map<string, User*> users);
int delete_account(map<string, User*> users);
int add_Credit(map<string, User*> users);
int refund(map<string, User*> users);
int LoginCheck();
int Advertise(map<string, User*> users);
int Bid(map<string, User*> users);

bool LoginStatus = false;    //loginstatus used for check if it is logged in
User* currentUser = new User();


string trim_str(string str) {
    int start = -1;
    int end = -1;
    for (int i = 0; i < str.size(); i++) {
        if (start < 0 && str[i] != ' ') start = i;
        if (str[i] != ' ') end = i + 1;
    }
    int len = end - start;

    if (start > -1) {
        return str.substr(start, len);
    } else {
        return str;
    }
}

int processTransaction(string transaction,map<string, User*> users){//it read in the User input and process to different cases
    string transactions[9] = {"Login","Logout","Create","Delete","Advertise","Bid","Refund","Add Credit"};
    int index = 0;

    for(int i = 0; i < 9; i++){
        index += 1;
        if(transaction == transactions[i]){
            break;
        }
    }

    switch(index){
        case 1:
            login(users);
            //login function check mark worked
            break;

        case 2:
            logout(users);
            //logout function check mark worked
            break;

        case 3:
            //create functions check mark worked
            create_account(users);
            break;

        case 4:
            delete_account(users);
            //delete functions check mark worked
            break;

        case 5:
            Advertise(users);
            //advertise functions
            break;

        case 6:
            Bid(users);
            //bid function
            break;

        case 7:
            refund(users);
            //refund functions
            break;

        case 8:
            add_Credit(users);
            //add creidt functions
            break;

        default:
            cout <<"Transaction Error" <<endl;
            break;
    }
    return 0;
}
//use int so i can have a check if the return value is correct it is a basic version of delete.
//need to pass one more argument user, so we can check the user typecheck if the current user is the Admin account.

int login(map<string, User*> users){  //not put a checker yet
    if(LoginStatus == true){
        cout <<"Already Logged in" <<endl;
        return -3;
    }
    string username;
    cout <<"Please enter your username: ";
    cin >> username;
    map<string, User*>::iterator it = users.find(username);
    if(it == users.end()){
        cout <<"Error, username not found";
    }else{
        currentUser = it->second;
        LoginStatus = true;
        cout <<"You are Logged in";
    }

    return 0;
}

int logout(map<string, User*> users){ //daily transaction file on working
    LoginCheck();

    cout <<"You have logged out";
    //
    //TODO Logout transaction;
    //
    LoginStatus = false;
    return 0;
}

int delete_account(map<string, User*> users){//screw this one
    LoginCheck();
    if(currentUser->user_type != "AA"){
        cout <<"Error, prohibit to delete account \n";
        return -2;
    }

    string username;

    cout <<"Please enter the username: ";
    cin >> username;

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
    LoginCheck();
    if(currentUser->user_type != "AA"){
        cout <<"Error, prohibit to create account \n";
        return -2;
    }

    string username;
    string usertype;
    int i = 0;

    cout <<"Please enter the username: ";
    cin >>username;
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
    cout <<"Please enter the usertype: ";
    cin >>usertype;
    if(usertype != "AA" && usertype != "FS" && usertype != "SS" && usertype != "BS"){
        cout <<"Error, user type is invaild" <<endl;
        return 3;
    }
    //end of testing usertpye

    cout <<"Account Create Successful! \n";

    //
    // TODO
    //
    return 0;
}

int refund(map<string, User*> users){
    LoginCheck();
    if(currentUser->user_type != "AA"){
        cout <<"Error, prohibit to process refund \n";
        return -2;
    }

    string buyer;
    string seller;
    double amount;

    cout <<"Please enter the buyer's name: ";
    cin >>buyer;
    map<string, User*>::iterator buyerit = users.find(buyer);
    if(buyerit == users.end()){
        cout <<"Error: Username does not exist! \n";
        return 2;
    } else if(buyerit ->second -> user_type == "SS"){
        cout <<"Error: User is not of type buy-standard. \n";
        return 1;
    }
    cout <<"Please enter the seller's username: ";
    cin >>seller;
    map<string, User*>::iterator sellerit = users.find(seller);
    if(sellerit == users.end()){
        cout <<"Error: Username does not exist! \n";
        return 2;
    }else if(sellerit -> second -> user_type == "SS"){
        cout <<"Error: User is not of type sell-standard.\n";
        return 1;
    }
    cout <<"Please enter the amount to refund: ";
    cin >>amount;
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

int Advertise(map<string, User*> users){
    LoginCheck();
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

int Bid(map<string, User*> users){
    LoginCheck();
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
}

int add_Credit(map<string, User*> users){
    LoginCheck();
    if(currentUser->user_type != "AA"){
        cout <<"Error, prohibit to Add Credit \n";
        return -2;
    }

    string username;
    float amount = 0;
    cout <<"Please enter the username to add credit to: ";
    cin >>username;
    cout <<"Please enter the amount to add: ";
    cin >>amount;
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
    } else{
        cout <<"Error: unknow error, please contact us at XXX-XXX-XXXX \n";
        return 5;
    }
    cout <<"Credit added! \n";
        return 0;
    //
    // TODO addcredit
    //
}

int LoginCheck(){
    if(LoginStatus == false){
        cout <<"Not Logged in" <<endl;
        return -1;
    }
}

void init(){
    system("clear");
}

int main() {
    init();
    map<string, User*> users = AccountsFile::read();
    int count = 0;

    while(1){
        string transaction;
        cout << "Welcome to CBay Auctioning System!" << endl;
        cout << "Please enter a transaction: ";
        getline(cin, transaction);        // i changed it to getline os it can reading one line of transaction so Add Credit can be read
        processTransaction(transaction,users);
        cout <<endl;

    }
    return 0;
}
