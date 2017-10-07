#include "player.hpp"

// Driver for player's move, regardless of player
std::pair<int, std::list<int>> othelloPlayer::move(
        std::unordered_map<int, std::list<int>> legalMoves) {

    std::pair<int, std::list<int>> moveChoice;
    if (this->computer) {
        moveChoice = this->computerMove(legalMoves);
    }
    else {
        moveChoice = this->humanMove(legalMoves);
    }

    return moveChoice;
}

// Prompts user for next move
std::pair<int, std::list<int>> othelloPlayer::humanMove(
        std::unordered_map<int, std::list<int>> legalMoves) {
    std::string str;
    int choice = 0;
    bool validInput = false;

    do {
        std::cout << "\tSelect move number: ";
        std::cin >> str;
        std::istringstream iss(str);
        iss >> choice;

        if (!iss.eof() || choice > legalMoves.size() || choice < 0) {
            std::cout << "\tInvalid input, please try again" << std::endl
                << std::endl;
        }
        else {
            validInput = true;
        }
        std::cout << std::endl;
    }
    while (!validInput);

    int i = 0;
    std::pair<int, std::list<int>> move;
    for (std::pair<int, std::list<int>> kv : legalMoves) {
        move = kv;
        i++;
        if (i == choice) {
            break;
        }
    }

    return move;
}

// Performs minimax search with alpha-beta pruning
std::pair<int, std::list<int>> othelloPlayer::computerMove(
        std::unordered_map<int, std::list<int>> legalMoves) {

    // Just takes first move... for now.
    std::cout << "Computer makes random move..." << std::endl;

    std::pair<int, std::list<int>> randMove;
    for (auto kv : legalMoves) {
        randMove = kv;
        break;
    }
    return randMove;
}

int othelloPlayer::minimax() {
    return 0;
}

int othelloPlayer::maxValue() {
    return 0;
}

int othelloPlayer::minValue() {
    return 0;
}
