#ifndef HEURISTIC_HPP
#define HEURISTIC_HPP

/* References:
 * http://mkorman.org/othello.pdf
 * https://www.tjhsst.edu/~rlatimer/techlab10/Per5/FourthQuarter/ChenPaperQ4-10.pdf
 */

#include "board.hpp"

class othelloHeuristic {
    int heuristicScore = 0;

    public:
        int utility(othelloBoard &board);
        int evaluate(othelloBoard &board, int color);

    private:
        int discDifference(othelloBoard &board);
        int mobility(othelloBoard &board);
        int stability(othelloBoard &board);
        int parity(othelloBoard &board, int &color);
        int boardWeights(othelloBoard &board, int &color);
};

#endif // HEURISTIC_HPP
