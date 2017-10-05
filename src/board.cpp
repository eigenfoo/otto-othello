#include "board.hpp"

// Constructor
othelloBoard::othelloBoard() {
    this->positions.resize(64, 0);
}

// Display board
// player is 1 for white, -1 for black
void othelloBoard::displayBoard(std::unordered_map<int, std::list<int>> moves,
        int player) {
    std::cout << "  A B C D E F G H" << std::endl;
    int row = 1;
    for (int i = 0; i < numSquares; i += height ) {
        // plain green square
        std::cout << row++ << "\033[48;5;34m\033[38;5;232m \033[0m";
        for (int j = i; j < i+width; j++) {
            if (this->positions[j] == 1) {
                // white disc
                std::cout << "\033[48;5;34m\033[38;5;256m\u25CF\033[0m";
            }
            else if (this->positions[j] == -1) {
                // black disc
                std::cout << "\033[48;5;34m\033[38;5;232m\u25CF\033[0m";
            }
            else if (moves.find(j) != moves.end() && player == 1) {
                // white x
                std::cout << "\033[48;5;34m\033[38;5;256m\u2613\033[0m";
            } 
            else if (moves.find(j) != moves.end() && player == -1) {
                // black x
                std::cout << "\033[48;5;34m\033[38;5;232m\u2613\033[0m";
            }
            else {
                // plain green square
                std::cout << "\033[48;5;34m\033[38;5;232m\u00B7 \033[0m";
            }
        }
        std::cout << std::endl;
    }
}

// Display valid moves for player
void othelloBoard::displayValidMoves(std::unordered_map<int, std::list<int>> moves) {

}

// Valid moves
std::unordered_map<int, std::list<int>> othelloBoard::findValidMoves() {

}

// Update positions after a move
void othelloBoard::updatePositions() {

}
