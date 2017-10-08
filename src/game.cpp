#include "game.hpp"

// Constructor
othelloGame::othelloGame() {
    this->board.positions.resize(64, 0);
}

// Initialize new game
void othelloGame::newGame(bool blackComputer, bool whiteComputer, float timeLimit) {
    // Initialize board
    std::vector<int> setup(64, 0);
    setup[27] = 2;
    setup[28] = 1;
    setup[35] = 1;
    setup[36] = 2;
    this->board.positions.swap(setup);

    // Initialize players
    this->blackPlayer.color = 1;
    this->blackPlayer.computer = (blackComputer ? true : false);
    this->whitePlayer.color = 2;
    this->whitePlayer.computer = (whiteComputer ? true : false);

    // Initialize player to move
    this->toMove = 1;

    // Initialize time limit
    this->timeLimit = timeLimit;
}

// Load game from file
void othelloGame::loadGame(std::string fileName, bool blackComputer, bool whiteComputer) {
    std::ifstream ifs(fileName.c_str());

    if (!ifs.good()) {
        std::cout << "File does not exist" << std::endl;
        return;
    }

    // Load board
    std::vector<int> setup(64, 0);
    std::string str;
    char ch;
    int idx = 0;

    for (int i = 0; i < 8; i++) {
        std::getline(ifs, str);
        for (int j = 0; j < 16; j += 2) {
            ch = str[j];
            if (ch == '1') {
                setup[idx] = 1;
            }
            else if (ch == '2') {
                setup[idx] = 2;
            }
            else if (ch == '0') {
                setup[idx] = 0;
            }
            else {
                std::string msg = "Board must be 0, 1, 2 for empty, black and "
                    "white, separated by spaces";
                std::cout << msg << std::endl;
                return;
            }

            idx++;
        }
    }
    this->board.positions.swap(setup);

    // Initialize players
    this->blackPlayer.color = 1;
    this->blackPlayer.computer = (blackComputer ? true : false);
    this->whitePlayer.color = 2;
    this->whitePlayer.computer = (whiteComputer ? true : false);

    // Load player to move
    if (std::getline(ifs, str)) {
        ch = str[0];
        if (ch == '1') {
            this->toMove = 1;
        }
        else if (ch == '2') {
            this->toMove = 2;
        }
        else {
            std::cout << "Player to move must be 1 (black) or 2 (white)" << std::endl;
            ifs.close();
            return;
        }
    }
    else {
        std::cout << "Save file does not specify player to move" << std::endl;
        ifs.close();
        return;
    }

    // Load time limit
    if (std::getline(ifs, str)) {
        if (stof(str) > 0) {
            this->timeLimit = stof(str);
        }
        else {
            std::cout << "Time limit must be a positive number" << std::endl;
            ifs.close();
            return;
        }
    }
    else {
        std::cout << "Save file does not specify computer time limit" << std::endl;
        ifs.close();
        return;
    }

    ifs.close();
}

// Make a move
void othelloGame::move(int color) {
    std::pair<int, std::list<int>> move;

    if (this->board.moves.empty()) {
        std::cout << "No legal moves. Passing..." << std::endl;
        this->passes[color] = true;

        if (passes[0] && passes[1]) {
            std::cout << "Game over: neither player has any legal moves" << std::endl;
            this->gameOver = true;
            // TODO figure out how game over works...
        }
    }

    if (color == 1) {
        std::cout << "Black to move" << std::endl;
        move = this->blackPlayer.move(this->board.moves);
    } 
    else if (color == 2) {
        std::cout << "White to move" << std::endl;
        move = this->whitePlayer.move(this->board.moves);
    }

    this->board.updateBoard(color, move);

    this->plies++;
}

// Update status of the game
void othelloGame::updateStatus() {

}
