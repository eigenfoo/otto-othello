#include "heuristic.hpp"

int othelloHeuristic::utility(othelloBoard &board) {
    int blackCount = std::count(board.positions.begin(),
            board.positions.end(), 1);
    int whiteCount = std::count(board.positions.begin(),
            board.positions.end(), 2);

    return blackCount - whiteCount;
}

int othelloHeuristic::evaluate(othelloBoard &board, int color) {
    if (board.terminalState()) {
        return utility(board);
    }
    else {
        this->heuristicScore = discDifference(board);
        return this->heuristicScore;
    }
}

int othelloHeuristic::discDifference(othelloBoard &board) {
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

int othelloHeuristic::mobility(othelloBoard &board) {
    return 0;
}

int othelloHeuristic::stability(othelloBoard &board) {
    return 0;
}

int othelloHeuristic::parity(othelloBoard &board, int &color) {
    return 0;
}

int othelloHeuristic::boardWeights(othelloBoard &board, int &color) {
    std::vector<int> boardWeights = {
         100, -100, 100,  50,  50, 100, -100,  100,
        -100, -200, -50, -50, -50, -50, -200, -100,
         100,  -50, 100,   0,   0, 100,  -50,  100,
          50,  -50,   0,   0,   0,   0,  -50,   50,
          50,  -50,   0,   0,   0,   0,  -50,   50,
         100,  -50, 100,   0,   0, 100,  -50,  100,
        -100, -200, -50, -50, -50, -50, -200, -100,
         100, -100, 100,  50,  50, 100, -100,  100,
    };

    return 0;
}
