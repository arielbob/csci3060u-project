#include <map>
#include <string>
#include <fstream>
#include "itemsfile.h"
#include "../user/user.h"
#include "../util/util.h"
#include "../constants.h"

using namespace std;

/**
* Parses the items file and returns a generated items map from its contents
* @param users The users map
* @return The generated items map
*/
map<pair<string, string>, Item*> ItemsFile::read(map<string, User*> users) {
    // map from <item_name, username> to Item*
    map<pair<string, string>, Item*> items;

    ifstream in("items.txt");
    string line;

    // loop through items file line by line
    while(getline(in, line)) {
        string item_name = util::trim_str(line.substr(0, MAX_ITEM_NAME_LENGTH));
        if (item_name == "END") break;

        int seller_name_offset = MAX_ITEM_NAME_LENGTH + 1;
        string seller_name = util::trim_str(line.substr(seller_name_offset, MAX_USERNAME_LENGTH));

        int bidder_name_offset = seller_name_offset + MAX_USERNAME_LENGTH + 1;
        string bidder_name = util::trim_str(line.substr(bidder_name_offset, MAX_USERNAME_LENGTH));

        int days_offset = bidder_name_offset + MAX_USERNAME_LENGTH + 1;
        int days = atoi(line.substr(days_offset, MAX_BID_DAYS_LENGTH).c_str());

        int current_bid_offset = days_offset + MAX_BID_DAYS_LENGTH + 1;
        double current_bid = atof(line.substr(current_bid_offset, MAX_BID_LENGTH).c_str());

        map<string, User*>::iterator it = users.find(seller_name);
        if (it == users.end()) continue;
        User* seller = it->second;

        it = users.find(bidder_name);
        if (it == users.end()) continue;
        User* bidder = it->second;

        Bid* bid = new Bid(bidder, current_bid);
        Item* item = new Item(item_name, seller, days, bid);

        pair<string, string> key(item_name, seller_name);
        pair<pair<string, string>, Item*> pair(key, item);
        items.insert(pair);
    }

    in.close();

    return items;
}