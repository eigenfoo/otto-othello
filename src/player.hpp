#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <chrono>
#include "heuristic.hpp"
#include "board.hpp"

class othelloPlayer {
    public:
        int color;
        bool computer;

        // Driver for moves, regardless of player
        std::pair<int, std::list<int>> move(othelloBoard &board,
                std::unordered_map<int, std::list<int>> &legalMoves,
                bool &pass);

    private:
        const static long infinity = 2147483647;
        othelloHeuristic heuristic;

        // Prompts user for next move
        // `board` is only necessary for polymorphic `move`...
        std::pair<int, std::list<int>> humanMove(othelloBoard &board,
                std::unordered_map<int, std::list<int>> &legalMoves,
                bool &pass);

        // Driver for the AI algorithm
        std::pair<int, std::list<int>> computerMove(othelloBoard &board,
                std::unordered_map<int, std::list<int>> &legalMoves,
                bool &pass);

        std::chrono::time_point<std::chrono::system_clock> startTimer();
        std::chrono::duration<double> stopTimer(
                std::chrono::time_point<std::chrono::system_clock> startTime);

        // Performs depth-limited minimax search with alpha-beta pruning
        std::pair<std::pair<int, std::list<int>>, int> alphabeta(
                othelloBoard &board, int depth, int alpha, int beta,
                bool maximizing);
};

#endif //PLAYER_HPP
