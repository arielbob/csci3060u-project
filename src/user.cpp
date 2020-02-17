#include "user.h"
#include <string>

using namespace std;

User::User(string username, string user_type, double credit) {
    this->username = username;
    this->user_type = user_type;
    this-> credit = credit;
}