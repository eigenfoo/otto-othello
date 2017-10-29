#include "database.hpp"

void database::loadOpenings() {
    std::ifstream csv("../lib/openings.csv");
    std::string line;

    while (csv.good()) {
        getline(csv, line);
        std::size_t found = str.rfind(key);
        if (found!=std::string::npos) {

        }
    }
}
