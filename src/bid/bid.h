#ifndef BID_H
#define BID_H

#include "../user/user.h"

/**
* Class to represent a bid
*/
class Bid {
    public:
        User* bidder;
        double amount;

        /**
        * Creates a Bid object
        */
        Bid(User* bidder, double amount);
};

#endif
