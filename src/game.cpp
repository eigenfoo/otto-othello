#include "game.hpp"

// Constructor
othelloGame::othelloGame() {
    this->board.positions.resize(64, 0);
}

// Initialize new game
void othelloGame::newGame(bool blackComputer, bool whiteComputer,
        float timeLimit) {
    // Initialize board
    std::vector<int> setup(64, 0);
    setup[27] = -1;
    setup[28] = 1;
    setup[35] = 1;
    setup[36] = -1;
    this->board.positions.swap(setup);

    // Initialize players
    this->blackPlayer.color = 1;
    this->blackPlayer.computer = blackComputer;
    this->whitePlayer.color = -1;
    this->whitePlayer.computer = whiteComputer;

    // Initialize player to move
    this->toMove = 1;

    // Initialize time limit
    this->board.timeLimit = timeLimit;
}

// Load game from file
void othelloGame::loadGame(std::string fileName, bool blackComputer,
        bool whiteComputer) {
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
                setup[idx] = -1;
            }
            else if (ch == '0') {
                setup[idx] = 0;
            }
            else {
                std::cout << "Invalid file format! Refer to the README." << std::endl;
                return;
            }

            idx++;
        }
    }
    this->board.discsOnBoard = 64 - std::count(setup.begin(), setup.end(), 0);
    this->board.positions.swap(setup);

    // Initialize players
    this->blackPlayer.color = 1;
    this->blackPlayer.computer = blackComputer;
    this->whitePlayer.color = -1;
    this->whitePlayer.computer = whiteComputer;

    // Load player to move
    if (std::getline(ifs, str)) {
        ch = str[0];
        if (ch == '1') {
            this->toMove = 1;
        }
        else if (ch == '2') {
            this->toMove = -1;
        }
        else {
            std::cout << "Player to move must be 1 (black) or 2 (white)!"
                << std::endl;
            ifs.close();
            return;
        }
    }
    else {
        std::cout << "Save file does not specify player to move!"
            << std::endl;
        ifs.close();
        return;
    }

    // Load time limit
    if (std::getline(ifs, str)) {
        if (stof(str) > 0) {
            this->board.timeLimit = stof(str);
        }
        else {
            std::cout << "Time limit must be a positive number!"
                << std::endl;
            ifs.close();
            return;
        }
    }
    else {
        std::cout << "Save file does not specify computer time limit!"
            << std::endl;
        ifs.close();
        return;
    }

    ifs.close();
}

// Make a move
void othelloGame::move(int color) {
    std::pair<int, std::list<int>> move;

    if (color == 1) {
        std::cout << "Black to move" << std::endl;
        move = this->blackPlayer.move(this->board, this->board.moves,
                this->board.passes[0], this->moveHistory);
    } 
    else if (color == -1) {
        std::cout << "White to move" << std::endl;
        move = this->whitePlayer.move(this->board, this->board.moves,
                this->board.passes[0], this->moveHistory);
    }

    if (!this->board.passes[0]) {
        this->board.updateBoard(color, move);
    }
}

// Update status of the game
void othelloGame::checkGameOver() {
    if (this->board.passes[0] && this->board.passes[1]) {
        int blackCount = std::count(this->board.positions.begin(),
                this->board.positions.end(), 1);
        int whiteCount = std::count(this->board.positions.begin(),
                this->board.positions.end(), -1);

        this->board.displayBoard(1);

        if (blackCount > whiteCount) {
            std::cout << "Black wins!" << std::endl;
        }
        else if (blackCount < whiteCount) {
            std::cout << "White wins!" << std::endl;
        }
        else {
            std::cout << "Tie!" << std::endl;
        }
        std::cout << "Black: " << blackCount << "\t"
            << "White: " << whiteCount << std::endl;

        this->gameOver = true;
    }
    else {
        if (!this->board.passes[0]) {
            this->board.discsOnBoard++;
        }

        this->board.passes[1] = this->board.passes[0];
        this->board.passes[0] = false;
    }
}
