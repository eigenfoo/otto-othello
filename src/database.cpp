#include "database.hpp"

void database::loadOpenings() {
    std::ifstream csv("../lib/openings.csv");
    std::string line;

    while (csv.good()) {
        getline(csv, line);
    }

}
