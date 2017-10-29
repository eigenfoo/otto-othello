#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <fstream>
#include <list>
#include <unordered_map>

class database {
    public:
        std::unordered_map<std::list<int>, int> openingBook = {};

        void loadOpenings();
};

#endif // DATABASE_HPP
