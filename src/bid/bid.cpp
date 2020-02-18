#include "../bid/bid.h"

using namespace std;

/**
* Class to represent a bid
*/
Bid::Bid(User* bidder, double amount) {
    this->bidder = bidder;
    this->amount = amount;
}
