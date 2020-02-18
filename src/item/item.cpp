#include <string>
#include "../item/item.h"

using namespace std;

/**
* Class to represent an item
*/
Item::Item(string item_name, User* seller, int num_days, Bid* current_bid) {
    this->item_name = item_name;
    this->seller = seller;
    this->num_days = num_days;
    this->current_bid = current_bid;
}
