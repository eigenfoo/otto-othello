#ifndef HEURISTIC_HPP
#define HEURISTIC_HPP

#include <numeric>
#include <unordered_set>
#include "board.hpp"

class othelloHeuristic {
    int discDifferenceScore = 0;
    int mobilityScore = 0;
    int stabilityScore = 0;
    std::unordered_set<int> stableDiscs;
    int cornerScore = 0;
    int squareWeightsScore = 0;
    std::map<int, std::list<int>> pMoves;

    public:
    int evaluate(othelloBoard &board, int color);

    private:
    int utility(othelloBoard &board, int &color);
    int discDifference(othelloBoard &board, int &color);
    int mobility(othelloBoard &board, int &color);
    // TODO implement potentialMobility
    // int potentialMobility(othelloBoard &board, int &color);
    int stability(othelloBoard &board, int color);
    void stableDiscsFromCorner(othelloBoard &board, int corner,
            int color);
    // TODO implement parity
    // int parity(othelloBoard &board, int &color);
    int squareWeights(othelloBoard &board, int &color);
    int corners(othelloBoard &board, int &color);
};

#endif // HEURISTIC_HPP
