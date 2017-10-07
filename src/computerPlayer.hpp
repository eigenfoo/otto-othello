#ifndef COMPUTER_HPP
#define COMPUTER_HPP

#include "board.hpp"

class computerPlayer {
    public:
        void computerMove();
        int minimax();
        int maxValue();
        int minValue();
};

#endif // COMPUTER_HPP
