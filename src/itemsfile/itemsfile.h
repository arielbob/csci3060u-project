#ifndef ITEMS_FILE_H
#define ITEMS_FILE_H

#include <map>
#include <string>
#include "../item/item.h"

/**
* Class to represent the items file 
*/
class ItemsFile {
    public:
        /**
        * Parses the items file and returns a generated items map from its contents
        * @return The generated items map
        */
        static std::map<std::pair<std::string, std::string>, Item*> read(std::map<std::string, User*> users);
};

#endif

