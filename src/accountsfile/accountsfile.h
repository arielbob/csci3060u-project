#ifndef ACCOUNTS_FILE_H
#define ACCOUNTS_FILE_H

#include <map>
#include <string>
#include "../user/user.h"

/**
* Class to represent the accounts file 
*/
class AccountsFile {
    public:
        /**
        * Parses the accounts file and returns a generated users map from its contents
        * @return The generated users map
        */
        static std::map<std::string, User*> read();
};

#endif
