#ifndef TRANSACTION_FILE_H
#define TRANSACTION_FILE_H

#include <string>
#include <fstream>

/**
* Class to represent a transaction file
*/
class TransactionFile {
    public:
        static std::ofstream out;
        /**
        * Open stream to write to transaction file
        */
        static void open(std::string filename);
        /**
        * Write line to transaction file
        */
        static void write_line(std::string line); 
        /**
        * Write create account transaction
        */
        static void write_create_account(std::string username, std::string user_type, double credit);
        /**
        * Write delete account transaction
        */
        static void write_delete_account(std::string username);
        /**
        * Write add credit transaction
        */
        static void write_add_credit(std::string username, double credit);
        /**
        * Write end of session transaction
        */
        static void write_end_session();
        /**
        * Write refund transaction
        */
        static void write_refund(std::string buyer_name, std::string seller_name, double credit);
        /**
        * Write advertise transaction
        */
        static void write_advertise(std::string item_name, std::string seller_name, int days, double min_bid);
        /**
        * Write bid transaction
        */
        static void write_bid(std::string item_name, std::string seller_name, std::string buyer_name, double new_bid);
};

#endif
