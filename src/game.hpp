#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <fstream>
#include "board.hpp"

class othelloGame {
    public:
        othelloBoard board;

        // 1 for black, 2 for white
        int movesFirst = 1;

        // Time limit for AI
        float timeLimit = 0.0;

        // true if game is over
        bool gameOver = false;

        // Constructor
        othelloGame();

        // Initialize board
        void newGame();

        // Load game from file
        // 0, 1, 2 for an empty square, a white disc, and a black disc, resp.
        // Last two lines give the player to move (1 for black, 2 for white)
        // and clock time limit for the AI, resp.
        void loadGame(std::string fileName);

        // Moke a move
        void move();

        // Update status of the game
        void updateStatus();
};

#endif // GAME_HPP
