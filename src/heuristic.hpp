#ifndef HEURISTIC_HPP
#define HEURISTIC_HPP

#include <numeric>
#include "board.hpp"

class othelloHeuristic {
    int discDifferenceScore = 0;
    int mobilityScore = 0;
    int stabilityScore = 0;
    int parityScore = 0;

    const std::vector<int> weights = {
         100, -100, 100,  50,  50, 100, -100,  100,
        -100, -200, -50, -50, -50, -50, -200, -100,
         100,  -50, 100,   0,   0, 100,  -50,  100,
          50,  -50,   0,   0,   0,   0,  -50,   50,
          50,  -50,   0,   0,   0,   0,  -50,   50,
         100,  -50, 100,   0,   0, 100,  -50,  100,
        -100, -200, -50, -50, -50, -50, -200, -100,
         100, -100, 100,  50,  50, 100, -100,  100,
    };

    // Dummy variables
    int foo = 0, bar = 0;
    std::map<int, std::list<int>> pMoves;

    public:
    int evaluate(othelloBoard &board, int color);

    private:
    int utility(othelloBoard &board);
    int discDifference(othelloBoard &board);
    int mobility(othelloBoard &board, int &color);
    int stability(othelloBoard &board);
    int parity(othelloBoard &board, int &color);
    int squareWeights(othelloBoard &board);
};

#endif // HEURISTIC_HPP
