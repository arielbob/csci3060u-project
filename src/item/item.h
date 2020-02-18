#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "../user/user.h"
#include "../bid/bid.h"

/**
* Class to represent an item
*/
class Item {
    public:
        std::string item_name;
        User* seller;
        Bid* current_bid;
        int num_days;

        /**
        * Creates an Item object
        */
        Item(std::string item_name, User* seller, int num_days, Bid* current_bid);
};

#endif
