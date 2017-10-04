#include "game.hpp"

othelloGame::othelloGame() {

}

// Initialize board
void othelloGame::newGame() {

}

// Load game from file
void othelloGame::loadGame(std::string fileName) {
    std::ifstream ifs;
    ifs.open(fileName.c_str());
    ifs.close();
}

void othelloGame::move() {

}

void othelloGame::updateStatus() {

}
