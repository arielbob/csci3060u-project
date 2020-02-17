#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cstdlib>
#include "user.h"

using namespace std;

/**
* Trims whitespace from a string
* @param str String to be trimmed
* @return The trimmed string
*/
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

            return users;
        }
};

int main() {
    string transaction;
    map<string, User*>* users = AccountsFile::read();

    cout << "Welcome to CBay Auctioning System!" << endl;
    cout << "Please enter a transaction: ";
    cin >> transaction;

    cout << "Entered " << transaction << endl;
    return 0;
}