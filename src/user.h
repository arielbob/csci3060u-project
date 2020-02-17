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
        User(){};
        User(std::string username, std::string user_type, double credit);
        User(std::string username, std::string user_type){
            this->username = username;
            this->user_type = user_type;
            this-> credit = 0.0f;
        };
        std::string toString(){
            std::string buffer;
            buffer = this->username;
            buffer.append((15 - username.size()),' ');
            buffer.append(user_type);
            buffer.append(" ");
            buffer.append(std::to_string(credit));
            return buffer;
        };
};

#endif
