#ifndef TRANSACTION_H 
#define TRANSACTION_H

#include <string>
#include <map>
#include "../user/user.h"
#include "../item/item.h"

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
        static int execute(User*& user, std::map<std::string, User*> users);
};

/**
* Class to represent a logout transaction
*/
class LogoutTransaction {
    public:
        static bool verify(User* user);
        static int execute(User*& user, std::map<std::string, User*> users);
};

/**
* Class to represent a create transaction
*/
class CreateTransaction {
    public:
        static bool verify(User* user);
        static int execute(User* user, std::map<std::string, User*> users);
};

/**
* Class to represent a delete transaction
*/
class DeleteTransaction {
    public:
        static bool verify(User* user);
        static int execute(User* user, std::map<std::string, User*> users);
};

/**
* Class to represent an advertise transaction
*/
class AdvertiseTransaction {
    public:
        static bool verify(User* user);
        static int execute(User* user, std::map<std::string, User*> users, std::map<std::pair<std::string, std::string>, Item*> items);
};

// -----------

// /**
// * Class to represent a bid transaction
// */
// class Transaction {
//     public:
//         static bool verify(User* user);
//         static int execute(User* user, std::map<std::string, User*> users);
// };

// /**
// * Class to represent a refund transaction
// */
// class Transaction {
//     public:
//         static bool verify(User* user);
//         static int execute(User* user, std::map<std::string, User*> users);
// };

// /**
// * Class to represent an add credit transaction
// */
// class Transaction {
//     public:
//         static bool verify(User* user);
//         static int execute(User* user, std::map<std::string, User*> users);
// };
#endif
