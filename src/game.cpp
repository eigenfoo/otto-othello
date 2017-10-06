#include "game.hpp"

othelloGame::othelloGame() {
    this->board.positions.resize(64, 0);
}

// Initialize board
void othelloGame::newGame() {
    std::vector<int> setup(64, 0);

    setup[27] = 2;
    setup[28] = 1;
    setup[35] = 1;
    setup[36] = 2;

    this->board.positions.swap(setup);
}

// Load game from file
void othelloGame::loadGame(std::string fileName) {
    std::ifstream ifs(fileName.c_str());
    
    if (!ifs.good()) {
        std::cout << "File does not exist!" << std::endl;
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
                    "white, separated by spaces!";
                std::cout << msg << std::endl;
                return;
            }

            idx++;
        }
    }
    this->board.positions.swap(setup);

    // Load player to move
    std::getline(ifs, str);
    ch = str[0];
    if (ch == '1') {
        this->movesFirst = 1;
    }
    else if (ch == '2') {
        this->movesFirst = 2;
    }
    else {
        std::cout << "Player to move must be 1 (black) or 2 (white)!" << std::endl;
        return;
    }
    
    // Load time limit
    std::getline(ifs, str);
    this->timeLimit = stof(str);

    ifs.close();
}

// Make a move
void othelloGame::move() {

}

// Update status of the game
void othelloGame::updateStatus() {

}
