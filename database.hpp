#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <fstream>
#include <unordered_map>
#include "board.hpp"

class database {
    public:
        std::unordered_map<std::string, int> openingBook = {};

        void loadOpenings();
};

#endif // DATABASE_HPP
