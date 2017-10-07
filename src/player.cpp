#include "player.hpp"

player::player(int color, bool computer) {
    this->color = color;
    this->computer = computer;
}

std::pair<int, std::list<int>> player::humanMove(
        std::unordered_map<int, std::list<int>> legalMoves) {
    std::string str;
    int choice = 0;
    bool validInput = false;

    do {
        std::cout << "Select move: ";
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

std::pair<int, std::list<int>> player::computerMove(
        std::unordered_map<int, std::list<int>> legalMoves) {

}

int player::minimax() {
    return 0;
}

int player::maxValue() {
    return 0;
}

int player::minValue() {
    return 0;
}
