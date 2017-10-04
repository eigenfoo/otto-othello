#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>

class othelloBoard {
    public:
        std::vector<int> positions;

        // Constructor
        othelloBoard();

        // Print board
        void printBoard();

        // Valid moves
        void validMoves();

    private:
        const static int width = 8;
        const static int height = 8;

};

#endif // BOARD_HPP
