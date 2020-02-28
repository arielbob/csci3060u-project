#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include "accountsfile.h"
#include "../user/user.h"
#include "../util/util.h"

using namespace std;

/**
* Parses the accounts file and returns a generated users map from its contents
* @return The generated users map
*/
map<string, User*> AccountsFile::read(string filename) {
    map<string, User*> users;

    ifstream in(filename);

    if (!in.is_open()) {
        cout << "Error: Could not open user accounts file" << endl;
        exit(1);
    }

    string line;

    // loop through accounts file line by line
    while(getline(in, line)) {
        string username = util::trim_str(line.substr(0, 15));
        if (username == "END") break;
        string user_type = util::trim_str(line.substr(16, 2));
        string credit_str = line.substr(19, 9);

        double credit = atof(credit_str.c_str());

        // insert new User object into map
        User* user = new User(username, user_type, credit);
        users.insert(pair<string, User*>(username, user));
    }

    in.close();

    return users;
}
