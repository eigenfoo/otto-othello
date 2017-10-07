#ifndef HUMANPLAYER_HPP
#define HUMANPLAYER_HPP

#include "board.hpp"

class humanPlayer {
    public:
        std::pair<int, std::list<int>> humanMove(
                std::unordered_map<int, std::list<int>> legalMoves);
};

#endif //HUMANPLAYER_HPP
