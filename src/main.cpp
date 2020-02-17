#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cstdlib>
#include "user.h"
#include "transactionfile.h"

using namespace std;

/**
* Trims whitespace from a string
* @param str String to be trimmed
* @return The trimmed string
*/
int create_account(map<string, User*>* users);
int login(map<string, User*>* users);
int logout(map<string, User*>* users);
int delete_account(map<string, User*>* users);
int add_Credit(map<string, User*>* users);

bool LoginStatus = false;    //loginstatus used for check if it is logged in
User* currentUser = new User();


string trim_str(string str) {
    int start = -1;
    int end = -1;
    for (unsigned int i = 0; i < str.size(); i++) {
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

/**
* Class to read users file and generate users map
*/
class AccountsFile {
    public:
        /**
        * Parses the accounts file and returns a generated users map from its contents
        * @return The generated users map
        */
        static map<string, User*>* read() {
            map<string, User*>* users = new map<string, User*>();

            ifstream in("userAccounts.txt");
            string line;

            // loop through accounts file line by line
            while(getline(in, line)) {
                string username = trim_str(line.substr(0, 15));
                if (username == "END") break;
                string user_type = trim_str(line.substr(16, 2));
                string credit_str = line.substr(19, 9);

                double credit = atof(credit_str.c_str());

                // insert new User object into map
                User* user = new User(username, user_type, credit);
                users->insert(pair<string, User*>(username, user));
            }

            in.close();

            return users;
        }
};

int processTransaction(string transaction,map<string, User*>* users){//it read in the User input and process to different cases
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
            cout << "Entered Advertise" <<endl;
            //advertise functions
            break;

        case 6:
            cout << "Entered Bid" <<endl;
            //bid function
            break;

        case 7:
            cout << "Entered Refund" <<endl;
            //refund functions
            break;

        case 8:
            cout << "Entered Add Credit" <<endl;
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

int login(map<string, User*>* users){  //not put a checker yet
    if(LoginStatus == true){
        cout <<"Already Logged in" <<endl;
        return -2;
    }
    string username;
    cout <<"Please enter your username: ";
    cin >> username;
    map<string, User*>::iterator it = users->find(username);
    if(it == users->end()){
        cout <<"Error, username not found";
    }else{
        currentUser = it->second;
        LoginStatus = true;
        cout <<"You are Logged in as Admin Account";
    }

    return 0;
}

int logout(map<string, User*>* users){ //daily transaction file on working
    if(LoginStatus == false){
        cout <<"Not Logged in" <<endl;
        return -1;
    }

    cout <<"You have logged out";
    //
    //To Do
    //
    LoginStatus = false;
    return 0;
}

int delete_account(map<string, User*>* users){//screw this one
    if(LoginStatus == false){
        cout <<"Not Logged in" <<endl;
        return -1;
    }
    if(currentUser->user_type != "AA"){
        cout <<"Error, prohibit to delete account \n";
    }

    string username;

    cout <<"Please enter the username: ";
    cin >> username;

    map<string, User*>::iterator it = users->find(username);
    if(it == users->end()){
        cout <<"Error, username could not found \n";
        return 2;
    } else{
        cout <<"Account Delete Successful! \n";
        return 0;
    }
    //
    // TO DO
    //

    return 1;
}

int create_account(map<string, User*>* users){//hell screw the END
    if(LoginStatus == false){
        cout <<"Not Logged in" <<endl;
        return -1;
    }
    if(currentUser->user_type != "AA"){
        cout <<"Error, prohibit to create account \n";
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

    map<string, User*>::iterator it = users->find(username);
    if(it == users->end()){
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
    // TO DO
    //
    return 0;
}

int add_Credit(map<string, User*>* users){
    if(LoginStatus == false){
        cout <<"Not Logged in" <<endl;
        return -1;
    }
    if(currentUser->user_type != "AA"){
        cout <<"Error, prohibit to create account \n";
    }

    string username;
    float amount = 0;
    cout <<"Please enter the username to add credit to: ";
    cin >>username;
    cout <<"Please enter the amount to add: ";
    cin >>amount;
    cout <<"Credit Added ";

    map<string, User*>::iterator it = users->find(username);
    if(it == users->end()){
        cout <<"Error: Username does not exist! \n";
        return 2;
    } else if(amount > 1000.0){
        cout <<"Error: Maximum session credit allowance ($1000.00) reached!";
        return 1;
    } else if(amount < 0){
        cout <<"Error: Amount to add must be greater than zero!";
        return 3;
    } else if((it -> second -> credit + amount) > 999999.99){
        cout <<"Error: Resulting funds exceed limit in users's account.";
        return 4;
    } else{
        cout <<"Error: unknow error, please contact us at XXX-XXX-XXXX";
        return 5;
    }
    cout <<"Credit added!";
        return 0;
    //
    // TO DO
    //
}

void init(){
    system("clear");
}


int main() {
    //init()
    map<string, User*>* users = AccountsFile::read();
    int count = 0;
    TransactionFile transFile;

    while(1){
        string transaction;
        cout << "Welcome to CBay Auctioning System!" << endl;
        cout << "Please enter a transaction: ";
        getline(cin, transaction);        // i changed it to getline os it can reading one line of transaction so Add Credit can be read
        processTransaction(transaction,users);
        cout <<endl;

    }
    //cout << "Entered " << transaction << endl;
    return 0;
}
