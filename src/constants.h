#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

const std::string CODE_END_SESSION = "00";
const std::string CODE_CREATE  = "01";
const std::string CODE_DELETE = "02";
const std::string CODE_ADVERTISE = "03";
const std::string CODE_BID = "04";
const std::string CODE_REFUND = "05";
const std::string CODE_ADD_CREDIT  = "06";

const int MAX_USERNAME_LENGTH = 15;
const int MAX_ITEM_NAME_LENGTH = 19;
const int MAX_CREDIT_LENGTH = 9;
const int MAX_BID_DAYS_LENGTH = 3;
const int MAX_BID_LENGTH = 6;

#endif