#include "board.hpp"

// Constructor
othelloBoard::othelloBoard() {
    this->positions.resize(64, 0);
}

// Display board: color is 1 for black, -1 for white
void othelloBoard::displayBoard(int color) {
    std::cout << "    A B C D E F G H" << std::endl;
    int row = 1;
    for (int i = 0; i < 64; i += 8) {
        // Green space
        std::cout << " " << row++ << " "
            << "\033[48;5;34m\033[38;5;232m \033[0m";

        for (int j = i; j < i+8; j++) {
            if (this->positions[j] == 1) {
                // Black disc followed by green space
                std::cout << "\033[48;5;34m\033[38;5;232m\u2022 \033[0m";
            }
            else if (this->positions[j] == -1) {
                // White disc followed by green space
                std::cout << "\033[48;5;34m\033[38;5;256m\u2022 \033[0m";
            }
            else if (this->moves.find(j) != this->moves.end() && color == 1) {
                // Black x followed by green space
                std::cout << "\033[48;5;34m\033[38;5;232m\u2613 \033[0m";
            } 
            else if (this->moves.find(j) != this->moves.end() && color == -1) {
                // White x followed by green space
                std::cout << "\033[48;5;34m\033[38;5;256m\u2613 \033[0m";
            }
            else {
                // Dot followed by green space
                std::cout << "\033[48;5;34m\033[38;5;232m\u00B7 \033[0m";
            }
        }

        if (i == 24) {
            std::cout << "\t\tBlack: " << std::count(this->positions.begin(),
                    this->positions.end(), 1);
        }
        else if (i == 32) {
            std::cout << "\t\tWhite: " << std::count(this->positions.begin(),
                    this->positions.end(), -1);
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

// Display legal moves for player
void othelloBoard::displayLegalMoves() {
    std::string colCoord = "ABCDEFGH";
    std::string rowCoord = "12345678";
    int colNum = 0, rowNum = 0;
    int moveNum = 1;
    std::list<int> flippedDiscs;

    std::cout << "Legal moves:" << std::endl;

    for (auto keyval : this->moves) {
        index2coord(keyval.first, colNum, rowNum);
        std::cout << "\t" << moveNum++ << "\t" << colCoord[colNum] << rowCoord[rowNum];

        flippedDiscs = keyval.second;
        std::cout << " will flip: ";

        for (int disc : flippedDiscs) {
            index2coord(disc, colNum, rowNum);
            std::cout << colCoord[colNum] << rowCoord[rowNum] << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

// Finds all legal moves, writing to a reference to a hash table with
// legal moves as keys, and a list of all discs to be flipped as values.
void othelloBoard::findLegalMoves(int color,
        std::unordered_map<int, std::list<int>> *pMoves) {
    // Clear legal moves from previous ply
    this->moves.clear();

    for (int i = 0; i < 64; i++) {
        if (this->positions[i] == color) {
            // Check rows
            findLegalMoveInDirection(i, color, -1, pMoves);
            findLegalMoveInDirection(i, color, 1, pMoves);

            // Check columns
            findLegalMoveInDirection(i, color, -8, pMoves);
            findLegalMoveInDirection(i, color, 8, pMoves);

            // Check diagonals
            findLegalMoveInDirection(i, color, -9, pMoves);
            findLegalMoveInDirection(i, color, 9, pMoves);
            findLegalMoveInDirection(i, color, -7, pMoves);
            findLegalMoveInDirection(i, color, 7, pMoves);
        }
    }
}

// Helper function to find a legal move given a disc, its color and a direction.
// Writes the legal move and a list of all discs to be flipped as a pair to the
// reference to a hash table.
void othelloBoard::findLegalMoveInDirection(int &disc, int &color, int direction,
        std::unordered_map<int, std::list<int>> *pMoves) {
    std::pair<int, std::list<int>> legalMove;
    std::list<int> flippedDiscs;
    int currentSquare = 0;
    int row1 = 0, col1 = 0, row2 = 0, col2 = 0;

    for (int i = disc + direction; i < 64 && i > -1; i += direction) {
        // Guard against wrapping around the board
        index2coord(i-direction, col1, row1);
        index2coord(i, col2, row2);
        if (abs(col1 - col2) > 1 || abs(row1 - row2) > 1) {
            break;
        }

        // Keep moving in given direction, remembering any discs of the
        // opposite color. Break if we see any discs of our color.
        currentSquare = this->positions[i];
        if (currentSquare == color ||
                (currentSquare == 0 && flippedDiscs.empty())) {
            break;
        }
        else if (currentSquare == -color) {
            flippedDiscs.push_front(i);
            continue;
        }
        // If we see an empty square, it is a legal move: insert it into the
        // moves hash table.
        // NB: we must check to see if the move is already in the map.
        // Second condition is to resolve edge case of
        // disc immediately adjacent to original disc.
        else if (currentSquare == 0 && !flippedDiscs.empty()) {
            std::unordered_map<int, std::list<int>>::iterator it = pMoves->find(i);

            if (it != pMoves->end()) {
                it->second.merge(flippedDiscs);
            }
            else {
                legalMove.first = i;
                legalMove.second = flippedDiscs;
                pMoves->insert(legalMove);
            }

            break;
        }
    }
}

// Update positions after a move
void othelloBoard::updateBoard(int color, std::pair<int, std::list<int>> move) {
    int square = move.first;
    std::list<int> flippedDiscs = move.second;

    this->positions[square] = color;
    for (auto disc : flippedDiscs) {
        this->positions[disc] = color;
    }
}

// Checks if game is a terminal state
bool othelloBoard::terminalState() {
    if (this->passes[0] && this->passes[1]) {
        return true;
    }
    return false;
}

// Helper function to convert board square index to coordinates
void othelloBoard::index2coord(int index, int &colNum, int &rowNum) {
    colNum = index % 8;
    rowNum = index / 8;
}
