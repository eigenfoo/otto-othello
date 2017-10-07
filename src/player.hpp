#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "board.hpp"

class player {
    public:
        int color;
        bool computer;

        player(int color, bool computer);

        std::pair<int, std::list<int>> humanMove(
                std::unordered_map<int, std::list<int>> legalMoves);

        std::pair<int, std::list<int>> computerMove(
                std::unordered_map<int, std::list<int>> legalMoves);

        int minimax();
        int maxValue();
        int minValue();
};

#endif //PLAYER_HPP
