#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <fstream>
#include "player.hpp"
#include "board.hpp"

class othelloGame {
    public:
        othelloBoard board;
        othelloPlayer blackPlayer;
        othelloPlayer whitePlayer;

        int toMove = 1;
        bool gameOver = false;

        // passes[0] and passes[1] are true if the most recent/second most
        // recent ply was a pass, resp.
        bool passes[2] = {false, false};

        // Constructor
        othelloGame();

        // Initialize board
        void newGame(bool blackComputer, bool whiteComputer, float timeLimit);

        // Load game from file
        // 0, 1, 2 for an empty square, a white disc, and a black disc, resp.
        // Last two lines give the player to move (1 for black, 2 for white)
        // and clock time limit for the AI, respectively.
        void loadGame(std::string fileName, bool blackComputer, bool whiteComputer);

        // Make a move
        void move(int color);

        // Update status of the game
        void checkGameOver();

        // Checks if game is a terminal state
        bool terminalState();
};

#endif // GAME_HPP
