#ifndef TRANSACTION_H 
#define TRANSACTION_H

#include <string>
#include <map>
#include "../user/user.h"

/**
* Class to represent a transaction
*/
// class Transaction {
//     public:
//         std::unordered_set perm_user_types;
//         bool is_permitted(User user);
// };

/**
* Class to represent a login transaction
*/
class LoginTransaction {
    public:
        static bool verify(User* user);
        static int execute(User* user, std::map<std::string, User*> users);
};

#endif