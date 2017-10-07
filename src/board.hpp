#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <unordered_map>

class othelloBoard {
    public:
        // positions specifies all pieces on the board. Squares on the
        // board are indexed from 0 to 63, left to right, top to bottom.
        // positions[i] is 1 for a black disc, 2 for a white disc
        std::vector<int> positions;

        // moves is a hash table specifying all possible moves from the
        // current board position. Possible moves are keys, and a list of
        // all pieces to be flipped are values.
        std::unordered_map<int, std::list<int>> moves;

        // Constructor
        othelloBoard();

        // Display board
        void displayBoard(int color);

        // Display legal moves for player
        void displayLegalMoves();

        // Finds all legal moves, returning a hash table with possible
        // moves as keys, and a list of all pieces to be flipped as values.
        void findLegalMoves(int color);

        // Helper function to find a legal move given a disc, its color and a direction.
        // Stores legal move and flipped discs as a pair in the moves hash table.
        void findLegalMoveInDirection(int &disc, int &color, int direction,
                std::unordered_map<int, std::list<int>> &moves);

        // Update board after a move
        void updateBoard();

        // Helper function to convert board square index to coordinate
        // strings
        void index2coord(int index, int &colNum, int &rowNum);
};

#endif // BOARD_HPP
