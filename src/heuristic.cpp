#include "heuristic.hpp"

int othelloHeuristic::utility(const othelloBoard &board) {
    int blackCount = std::count(board.positions.begin(),
            board.positions.end(), 1);
    int whiteCount = std::count(board.positions.begin(),
            board.positions.end(), 2);

    return blackCount - whiteCount;
}

int othelloHeuristic::evaluate(const othelloBoard &board, int color) {
    return discDifference(board);
}

int othelloHeuristic::discDifference(const othelloBoard &board) {
    int score = 0;
    int blackCount = std::count(board.positions.begin(),
            board.positions.end(), 1); 
    int whiteCount = std::count(board.positions.begin(),
            board.positions.end(), 2); 
    
    if (blackCount > whiteCount) {
        score = 100 * blackCount / (blackCount + whiteCount);
    }
    else if (blackCount < whiteCount) {
        score = -100 * whiteCount / (blackCount + whiteCount);
    }

    return score;
}

int othelloHeuristic::mobility(const othelloBoard &board) {
    return 0;
}

int othelloHeuristic::stability(const othelloBoard &board) {
    return 0;
}

int othelloHeuristic::parity(const othelloBoard &board, int &color) {
    return 0;
}
