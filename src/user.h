#ifndef USER_H
#define USER_H

#include <string>

/**
* Class to represent a user
*/
class User {
    public:
        std::string username;
        std::string user_type;
        double credit;

        /**
        * Creates a User object
        */
        User(std::string username, std::string user_type, double credit);
};

#endif