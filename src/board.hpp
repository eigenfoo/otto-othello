#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <unordered_map>

class othelloBoard {
    public:
        std::vector<int> positions;

        // Constructor
        othelloBoard();

        // Display board
        void displayBoard(std::unordered_map<int, std::list<int>> moves,
                int player);

        // Display valid moves for player
        void displayValidMoves(std::unordered_map<int, std::list<int>> moves);

        // Find valid moves, returning them in a hash table with
        // positions as keys, and a list of possible moves as values
        std::unordered_map<int, std::list<int>> findValidMoves();

        // Update positions after a move
        void updatePositions();

    private:
        const static int width = 8;
        const static int height = 8;
        const static int numSquares = width*height;
};

#endif // BOARD_HPP
