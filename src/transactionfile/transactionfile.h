#ifndef TRANSACTION_FILE_H
#define TRANSACTION_FILE_H

#include <string>
#include <fstream>

/**
* Class to represent a transaction file
*/
class TransactionFile {
    public:
        std::ofstream out;
        TransactionFile();
        ~TransactionFile();
        /**
        * Write line to transaction file
        */
        void write_line(std::string line); 
        /**
        * Write create account transaction
        */
        void write_create_account(std::string username, std::string user_type, double credit);
        /**
        * Write delete account transaction
        */
        void write_delete_account(std::string username);
        /**
        * Write add credit transaction
        */
        void write_add_credit(std::string username, double credit);
        /**
        * Write end of session transaction
        */
        void write_end_session();
        /**
        * Write refund transaction
        */
        void write_refund(std::string buyer_name, std::string seller_name, double credit);
        /**
        * Write advertise transaction
        */
        void write_advertise(std::string item_name, std::string seller_name, int days, double min_bid);
        /**
        * Write bid transaction
        */
        void write_bid(std::string item_name, std::string seller_name, std::string buyer_name, double new_bid);
};

#endif
