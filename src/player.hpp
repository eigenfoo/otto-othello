#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <chrono>
#include <iterator>
#include "heuristic.hpp"
#include "board.hpp"

class othelloPlayer {
    public:
        int color;
        bool computer;

        // Driver for moves, regardless of player
        std::pair<int, std::list<int>> move(othelloBoard &board,
                std::map<int, std::list<int>> &legalMoves,
                bool &pass);

    private:
        const static long infinity = 2147483647;
        othelloHeuristic heuristic;

        // Prompts user for next move
        // `board` is only necessary for polymorphic `move`...
        std::pair<int, std::list<int>> humanMove(othelloBoard &board,
                std::map<int, std::list<int>> &legalMoves, bool &pass);

        // Driver for the AI algorithm
        std::pair<int, std::list<int>> computerMove(othelloBoard &board,
                std::map<int, std::list<int>> &legalMoves, bool &pass);

        // Returns time point
        std::chrono::time_point<std::chrono::system_clock> startTimer();

        // Returns time elapsed in seconds
        float stopTimer(
                std::chrono::time_point<std::chrono::system_clock> startTime);

        // Performs depth-limited minimax search with alpha-beta pruning
        // Implemented using a stack to avoid recursion overhead
        // Returns move for square -1 if time runs out
        std::pair<int, std::list<int>> depthLimitedAlphaBeta(
                othelloBoard &board, int depthLimit,
                std::chrono::time_point<std::chrono::system_clock> startTime,
                float timeLimit);
};

#endif //PLAYER_HPP
