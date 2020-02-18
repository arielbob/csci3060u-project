#include "user.h"
#include <string>

using namespace std;

User::User() {}

User::User(string username, string user_type, double credit) {
    this->username = username;
    this->user_type = user_type;
    this->credit = credit;
}

User::User(std::string username, std::string user_type){
    this->username = username;
    this->user_type = user_type;
    this->credit = 0.0f;
};

std::string User::toString(){
    string buffer;
    buffer = this->username;
    buffer.append((15 - username.size()),' ');
    buffer.append(user_type);
    buffer.append(" ");
    buffer.append(to_string(credit));
    return buffer;
};