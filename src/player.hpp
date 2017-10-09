#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "board.hpp"

class othelloPlayer {
    public:
        int color;
        bool computer;

        // Driver for moves, regardless of player
        std::pair<int, std::list<int>> move(
                const std::unordered_map<int, std::list<int>> &legalMoves,
                bool &pass);

        // Prompts user for next move
        std::pair<int, std::list<int>> humanMove(
                const std::unordered_map<int, std::list<int>> &legalMoves,
                bool &pass);

        // Driver for the AI algorithm
        std::pair<int, std::list<int>> computerMove(
                const std::unordered_map<int, std::list<int>> &legalMoves,
                bool &pass);

        // Performs minimax search with alpha-beta pruning
        int minimax();
        int maxValue();
        int minValue();
};

#endif //PLAYER_HPP
