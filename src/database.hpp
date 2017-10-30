#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <fstream>
#include "board.hpp"

class othelloDatabase {
    public:
        std::unordered_map<std::string, int> openingBook = {};

        othelloDatabase();
        void loadOpenings();
};

#endif // DATABASE_HPP
