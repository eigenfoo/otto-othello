#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <fstream>
#include "board.hpp"

class othelloGame {
    public:
        othelloBoard board;
        int movesFirst = 1;
        bool player1AI = false, player2AI = false;
        float timeLimit = 0.0;
        bool gameOver = false;
        bool pass[2] = {false, false};

        // Constructor
        othelloGame();

        // Initialize board
        void newGame(bool player1AI, bool player2AI, float timeLimit);

        // Load game from file
        // 0, 1, 2 for an empty square, a white disc, and a black disc, resp.
        // Last two lines give the player to move (1 for black, 2 for white)
        // and clock time limit for the AI, respectively.
        void loadGame(std::string fileName, bool player1AI, bool player2AI);

        // Moke a move
        void move();

        // Update status of the game
        void updateStatus();
};

#endif // GAME_HPP
