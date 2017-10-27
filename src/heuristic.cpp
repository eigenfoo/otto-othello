#include "heuristic.hpp"
// Heuristic is from the perspective that black maximizes
// TODO the heuristic should change as the game progresses!

int othelloHeuristic::evaluate(othelloBoard &board, int color) {
    if (board.terminalState()) {
        return 100000*utility(board);
    }

    this->discDifferenceScore = discDifference(board);
    this->mobilityScore = mobility(board, color);
    this->potentialMobilityScore = potentialMobility(board, color);
    this->stabilityScore = stability(board, color);
    this->parityScore = parity(board, color);

    if (board.discsOnBoard <= 20) {
        // Opening game
        return mobilityScore
            + potentialMobilityScore
            + stabilityScore
            + parityScore;
    }
    else if (board.discsOnBoard <= 50) {
        //Midgame
        return discDifferenceScore
            + mobilityScore
            + potentialMobilityScore
            + stabilityScore
            + parityScore;
    }
    else {
        // Endgame
        return discDifferenceScore
            + stabilityScore
            + parityScore;
    }
}

int othelloHeuristic::utility(othelloBoard &board) {
    return std::accumulate(board.positions.begin(), board.positions.end(), 0);
}

// Relative disc difference between the two players
int othelloHeuristic::discDifference(othelloBoard &board) {
    // Number of black discs
    this->foo = std::count(board.positions.begin(),
            board.positions.end(), 1);

    // Number of white discs
    this->bar = std::count(board.positions.begin(),
            board.positions.end(), -1);
    
    if (this->foo > this->bar) {
        this->discDifferenceScore = (100 * this->foo) / (this->foo + this->bar);
    }
    else if (this->foo < this->bar) {
        this->discDifferenceScore = (-100 * this->bar) / (this->foo + this->bar);
    }
    else {
        this->discDifferenceScore = 0;
    }

    return this->discDifferenceScore;
}

// Number of possible moves
int othelloHeuristic::mobility(othelloBoard &board, int &color) {
    // Black mobility
    board.findLegalMoves(1, &this->pMoves);
    this->foo = pMoves.size();
    pMoves.clear();

    // White mobility
    board.findLegalMoves(-1, &this->pMoves);
    this->bar = pMoves.size();
    pMoves.clear();

    this->mobilityScore = 0;

    if (this->foo > this->bar) {
        this->mobilityScore = (100*this->foo) / (this->foo + this->bar);
    }
    else if (this->foo < this->bar) {
        this->mobilityScore = (-100*this->bar) / (this->foo + this->bar);
    }

    return this->mobilityScore;
}

int othelloHeuristic::potentialMobility(othelloBoard &board, int &color) {
    return 0;
}

// Computes a lower bound on the number of stable discs
int othelloHeuristic::stability(othelloBoard &board, int &color) {
    this->stableDiscs.clear();

    stableDiscsFromCorner(board, 0, color);
    stableDiscsFromCorner(board, 7, color);
    stableDiscsFromCorner(board, 56, color);
    stableDiscsFromCorner(board, 63, color);

    return this->stableDiscs.size();
}

// Finds the number of stable discs given a corner
void othelloHeuristic::stableDiscsFromCorner(othelloBoard &board, int corner,
        int &color) {

    bool down, right;
    if (corner == 0) {
        down = true;
        right = true;
    }
    else if (corner == 7) {
        down = true;
        right = false;
    }
    else if (corner == 56) {
        down = false;
        right = true;
    }
    else {
        down = false;
        right = false;
    }

    int horizIncr = 1, horizStop = 7;
    int vertIncr = 8, vertStop = 56;
    if (!right) {
        horizIncr *= -1;
        horizStop *= -1;
    }
    if (!down) {
        vertIncr *= -1;
        vertStop *= -1;
    }

    // Iterate horizontally
    for (int i = corner; i != corner + horizIncr + horizStop; i += horizIncr) {
        // If there is a disc of our color on this square
        if (board.positions[i] == color) {
            // Iterate vertically
            for (int j = i; j != i + vertStop; j+= vertIncr) {
                // If there is a disc of our color on this square, and it is not
                // in our stable discs set
                if (board.positions[j] == color && stableDiscs.find(j) == stableDiscs.end()) {
                    // Insert it to our set
                    this->stableDiscs.insert(j);
                }
                // As soon as we come across a disc of the opposite color, break
                else {
                    break;
                }
            }
        }
        // Otherwise, break
        else {
            break;
        }
    }
}

// Who is expected to have the last move in the game
int othelloHeuristic::parity(othelloBoard &board, int &color) {
    if (color == 1) {
        if (board.discsOnBoard % 2 == 0) {
            this->parityScore = -1;
        }
        else {
            this->parityScore = 1;
        }
    }
    else {
        if (board.discsOnBoard % 2 == 0) {
            this->parityScore = -1;
        }
        else {
            this->parityScore = 1;
        }
    }
    return this->parityScore;
}

// Assigns a weight to every square on the board
// FIXME make sure to remove -100 and -200 penalties if corners are occupied!!
// what to replace them with, though?
int othelloHeuristic::squareWeights(othelloBoard &board) {
    return std::inner_product(board.positions.begin(), board.positions.end(),
            this->weights.begin(), 0);
}
