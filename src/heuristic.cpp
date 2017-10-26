#include "heuristic.hpp"
// Heuristic is from the perspective that black maximizes
// TODO the heuristic should change as the game progresses!

int othelloHeuristic::evaluate(othelloBoard &board, int color) {
    if (board.terminalState()) {
        return 100000*utility(board);
    }

    this->discDifferenceScore = discDifference(board);
    this->mobilityScore = mobility(board, color);
    this->stabilityScore = stability(board);
    this->parityScore = parity(board, color);

    if (board.discsOnBoard <= 10) {
        // Opening game
        return discDifferenceScore + mobilityScore
            + stabilityScore + parityScore;
    }
    else if (board.discsOnBoard >= 50) {
        // Endgame
        return discDifferenceScore + mobilityScore
            + stabilityScore + parityScore;
    }
    else {
        //Midgame
        return discDifferenceScore + mobilityScore
            + stabilityScore + parityScore;
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
        this->discDifferenceScore = 100 * this->foo / (this->foo + this->bar);
    }
    else if (this->foo < this->bar) {
        this->discDifferenceScore = -100 * this->bar / (this->foo + this->bar);
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

// Computes a lower bound on the number of stable discs
int othelloHeuristic::stability(othelloBoard &board) {
    return 0;
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
int othelloHeuristic::squareWeights(othelloBoard &board) {
    return std::inner_product(board.positions.begin(), board.positions.end(),
            this->weights.begin(), 0);
}
