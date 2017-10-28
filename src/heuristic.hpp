#ifndef HEURISTIC_HPP
#define HEURISTIC_HPP

#include <numeric>
#include <unordered_set>
#include "board.hpp"


class othelloHeuristic {
    int discDifferenceScore = 0;
    int mobilityScore = 0;
    int potentialMobilityScore = 0;
    int stabilityScore = 0;
    std::unordered_set<int> stableDiscs;
    int parityScore = 0;

    // Dummy variables
    int foo = 0, bar = 0;
    std::map<int, std::list<int>> pMoves;

    public:
    int evaluate(othelloBoard &board, int color);

    private:
    int utility(othelloBoard &board);
    int discDifference(othelloBoard &board);
    int mobility(othelloBoard &board, int &color);
    int potentialMobility(othelloBoard &board, int &color);
    int stability(othelloBoard &board, int &color);
    void stableDiscsFromCorner(othelloBoard &board, int corner,
            int &color);
    int parity(othelloBoard &board, int &color);
    int squareWeights(othelloBoard &board);
};

#endif // HEURISTIC_HPP
