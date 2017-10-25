#include "heuristic.hpp"
// TODO finish heuristic

int othelloHeuristic::evaluate(othelloBoard &board, int color) {
    if (board.terminalState()) {
        return utility(board);
    }
    else {
        this->discDifferenceScore = discDifference(board);
        this->mobilityScore = mobility(board, color);
        this->stabilityScore = stability(board);
        this->parityScore = parity(board, color);

        return discDifferenceScore + mobilityScore + stabilityScore + parityScore;
    }
}

int othelloHeuristic::utility(othelloBoard &board) {
    // Number of black discs
    this->foo = std::count(board.positions.begin(),
            board.positions.end(), 1);
    // Number of white discs
    this->bar = std::count(board.positions.begin(),
            board.positions.end(), -1);

    return this->foo - this->bar;
}

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

int othelloHeuristic::mobility(othelloBoard &board, int &color) {
    std::map<int, std::list<int>> *pMoves = nullptr;

    // Black mobility
    board.findLegalMoves(1, pMoves);
    this->foo = pMoves->size();

    pMoves->clear(); // FIXME is this necessary?

    // White mobility
    board.findLegalMoves(-1, pMoves);
    this->bar = pMoves->size();

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

// Computes who is expected to have the last move in the game
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
