#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "transactionfile.h"
#include "../constants.h"
#include "../util/util.h"

using namespace std;

TransactionFile::TransactionFile() {
    // TODO: add error handling
    out.open("transactions.txt", ofstream::app);
}

TransactionFile::~TransactionFile() {
    out.close();
}

/**
* Writes a line to the transaction file
* @param line The line to write
*/
void TransactionFile::write_line(string line){
    if (!out.is_open()) return;

    out << line << '\n';
    out.flush();
};

/**
* Writes create account transaction to transaction file
* @param username Username of new user
* @param user_type Type of user
* @param credit Initial credit of user
*/
void TransactionFile::write_create_account(std::string username, std::string user_type, double credit) {
    stringstream ss;
    ss << CODE_CREATE << " ";
    ss << util::right_pad(username, MAX_USERNAME_LENGTH, ' ') << " ";
    ss << user_type << " ";
    ss << util::credit_str(credit, MAX_CREDIT_LENGTH);
    write_line(ss.str());
}

/**
* Writes delete account transaction to transaction file
* @param username Username of user to delete
*/
void TransactionFile::write_delete_account(std::string username) {
    stringstream ss;
    ss << CODE_DELETE << " ";
    ss << util::right_pad(username, MAX_USERNAME_LENGTH, ' ') << " ";
    ss << "  " << " ";
    ss << util::right_pad("", MAX_CREDIT_LENGTH, '0');
    write_line(ss.str());
}

/**
* Writes add credit transaction to transaction file
* @param username Username of user to add credit to
* @param credit Credit to add
*/
void TransactionFile::write_add_credit(std::string username, double credit) {
    stringstream ss;
    ss << CODE_ADD_CREDIT << " ";
    ss << util::right_pad(username, MAX_USERNAME_LENGTH, ' ') << " ";
    ss << "  " << " ";
    ss << util::credit_str(credit, MAX_CREDIT_LENGTH);
    write_line(ss.str());
}

/**
* Writes end session transaction to transaction file
*/
void TransactionFile::write_end_session() {
    stringstream ss;
    ss << CODE_END_SESSION << " ";
    ss << util::right_pad("", MAX_USERNAME_LENGTH, ' ') << " ";
    ss << "  " << " ";
    ss << util::right_pad("", MAX_CREDIT_LENGTH, '0');
    write_line(ss.str());
}

/**
* Writes refund transaction to transaction file
* @param buyer_name Username of buyer
* @param seller_name Username of seller
* @param credit Amount to refund
*/
void TransactionFile::write_refund(std::string buyer_name, std::string seller_name, double credit) {
    stringstream ss;
    ss << CODE_REFUND << " ";
    ss << util::right_pad(buyer_name, MAX_USERNAME_LENGTH, ' ') << " ";
    ss << util::right_pad(seller_name, MAX_USERNAME_LENGTH, ' ') << " ";
    ss << util::credit_str(credit, MAX_CREDIT_LENGTH);
    write_line(ss.str());
}

/**
* Writes advertise transaction to transaction file
* @param item_name Name of item
* @param seller_name Username of seller
* @param days Amount of days the item is available to bid on
* @param min_bid The minimum bid amount
*/
void TransactionFile::write_advertise(std::string item_name, std::string seller_name, int days, double min_bid) {
    stringstream ss;
    ss << CODE_ADVERTISE << " ";
    ss << util::right_pad(item_name, MAX_ITEM_NAME_LENGTH, ' ') << " ";
    ss << util::right_pad(seller_name, MAX_USERNAME_LENGTH, ' ') << " ";
    ss << util::left_pad(to_string(days), MAX_BID_DAYS_LENGTH, '0') << " ";
    ss << util::credit_str(min_bid, MAX_BID_LENGTH);
    write_line(ss.str());
}

/**
* Writes bid transaction to transaction file
* @param item_name Name of item
* @param seller_name Username of seller
* @param buyer_name Username of buyer
* @param new_bid The new bid amount
*/
void TransactionFile::write_bid(std::string item_name, std::string seller_name, std::string buyer_name, double new_bid) {
    stringstream ss;
    ss << CODE_BID << " ";
    ss << util::right_pad(item_name, MAX_ITEM_NAME_LENGTH, ' ') << " ";
    ss << util::right_pad(seller_name, MAX_USERNAME_LENGTH, ' ') << " ";
    ss << util::right_pad(buyer_name, MAX_USERNAME_LENGTH, ' ') << " ";
    ss << util::credit_str(new_bid, MAX_BID_LENGTH);
    write_line(ss.str());
}
