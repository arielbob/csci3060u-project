#include <map>
#include <iostream>
#include <string>
#include "../user/user.h"
#include "transaction.h"

using namespace std;

bool CreateTransaction::verify(User* user) {
    if (!user) {
        cout << "Error: Not logged in" <<  endl;
        return false;
    }

    if (user->user_type == "AA") return true;

    return false;
}

int CreateTransaction::execute(TransactionFile tf, User* current_user, map<string, User*> users) {
    if (!verify(current_user)) {
        cout <<"Error: prohibit to create account" << endl;
        return 1;
    }

    string username;
    string user_type;

    cout << "Please enter the username:" << endl;
    getline(cin, username);
    if(username.size() > 15 || username.size() <= 0){
        cout <<"Error: username too long or too short" <<endl;
        return 1;
    }

    map<string, User*>::iterator it = users.find(username);
    if(it == users.end()){
    } else{
        cout <<"Error: username Already been take \n";
        return 2;
    }

    //end of testing username
    cout << "Please enter the user_type:" << endl;
    getline(cin, user_type);
    if(user_type != "AA" && user_type != "FS" && user_type != "SS" && user_type != "BS"){
        cout <<"Error: user type is invaild" <<endl;
        return 3;
    }
    //end of testing user_type

    cout <<"Account Create Successful! \n";

    //
    // TODO
    //
    return 0;
}
