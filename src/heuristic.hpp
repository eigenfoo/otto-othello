#ifndef HEURISTIC_HPP
#define HEURISTIC_HPP

/* References:
 * http://mkorman.org/othello.pdf
 * https://www.tjhsst.edu/~rlatimer/techlab10/Per5/FourthQuarter/ChenPaperQ4-10.pdf
 */

#include "board.hpp"

class othelloHeuristic {
    public:
        int evaluate(const othelloBoard &board, int &color);

    private:
        int discDifference(const othelloBoard &board);
        int mobility(const othelloBoard &board);
        int stability(const othelloBoard &board);
        int parity(const othelloBoard &board, int &color);
};

#endif // HEURISTIC_HPP
