#include "board.hpp"

// Constructor
othelloBoard::othelloBoard() {
    this->positions.resize(64, 0);
}

// Display board
// color is 1 for black, 2 for black
void othelloBoard::displayBoard(int color) {
    std::cout << "  A B C D E F G H" << std::endl;
    int row = 1;
    for (int i = 0; i < 64; i += 8) {
        // Plain green square
        std::cout << row++ << "\033[48;5;34m\033[38;5;232m \033[0m";

        for (int j = i; j < i+8; j++) {
            if (this->positions[j] == 1) {
                // Black disc
                std::cout << "\033[48;5;34m\033[38;5;232m\u25CF\033[0m";
            }
            else if (this->positions[j] == 2) {
                // White disc
                std::cout << "\033[48;5;34m\033[38;5;256m\u25CF\033[0m";
            }
            else if (this->moves.find(j) != this->moves.end() && color == 1) {
                // Black x
                std::cout << "\033[48;5;34m\033[38;5;232m\u2613\033[0m";
            } 
            else if (this->moves.find(j) != this->moves.end() && color == 2) {
                // White x
                std::cout << "\033[48;5;34m\033[38;5;256m\u2613\033[0m";
            }
            else {
                // Plain green square
                std::cout << "\033[48;5;34m\033[38;5;232m\u00B7 \033[0m";
            }
        }

        std::cout << std::endl;
    }
}

// Display valid moves for player
void othelloBoard::displayValidMoves() {
    char colChar = 'A';
    char rowChar = '1';
    int moveNum = 1;

    for (auto keyval : this->moves) {
        index2coord(keyval.first, colChar, rowChar);
        std::cout << "Valid move " << moveNum++ << ") "
            << colChar << rowChar << " ";

        std::list<int> discsFlipped = keyval.second;
        std::cout << "will flip discs: ";

        for (int disc : discsFlipped) {
            index2coord(disc, colChar, rowChar);
            std::cout << colChar << rowChar << " " << std::endl;
        }

        std::cout << std::endl;
    }
}

// Finds all valid moves, returning a hash table with possible moves as keys,
// and a list of all pieces to be flipped as values.
void othelloBoard::findValidMoves() {

}

// Update positions after a move
void othelloBoard::updateBoard() {

}

// Helper function to convert board square index to coordinate strings
void othelloBoard::index2coord(int index, char &colChar, char &rowChar) {
    std::string colCoord = "ABCDEFGH";
    std::string rowCoord = "12345678";

    colChar = colCoord[index % 8];
    rowChar = rowCoord[index / 8];
}