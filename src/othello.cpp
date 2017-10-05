#include <sstream>
#include "game.hpp"

bool promptAIPlayer(int player);
int promptAITimeLimit(int player);

int main() {
    othelloBoard board;
    othelloGame game(board);
    int timeLimit1 = 0;
    int timeLimit2 = 0;
    bool player1AI = false;
    bool player2AI = false;

    // Prompt user for new or loaded game
    int choice = 0;
    std::string str;
    bool validInput = false;
    do {
        std::cout << "Load a game or start a new one?" << std::endl;
        std::cout << "\t1 -> Start a new game" << std::endl;
        std::cout << "\t2 -> Load a board from file" << std::endl;
        std::cout << "\tSelection: ";
        std::cin >> str;
        std::istringstream iss(str);
        iss >> choice;

        if (choice == 1 || choice == 2) {
            validInput = true;
        }
        else {
            std::cout << "\tInvalid input, please try again" << std::endl;
            std::cout << std::endl;
        }
    }
    while (!validInput);
    std::cout << std::endl;

    // Initialize game appropriately
    if (choice == 1) {
        player1AI = promptAIPlayer(1);
        if (player1AI) {
            timeLimit1 = promptAITimeLimit(1);
        }

        player2AI = promptAIPlayer(2);
        if (player2AI) {
            timeLimit2 = promptAITimeLimit(2);
        }

        game.newGame();
    }
    else {
        std::string fileName;
        std::cout << "Enter file name: ";
        std::cin >> fileName;

        game.loadGame(fileName);
    }

    // FIXME main game logic goes here

    return 0;
}

// Prompts user if player n is the computer/AI
bool promptAIPlayer(int player) {
    bool isAI = false;
    std::string str;
    char ch;
    bool validInput = false;

    do {
        std::cout << "Is Player " << player << " the computer?" << std::endl;
        std::cout << "\ty -> Yes" << std::endl;
        std::cout << "\tn -> No" << std::endl;
        std::cout << "\tSelection: ";
        std::cin >> str;
        std::istringstream iss(str);
        iss >> ch;

        if (ch == 'y') {
            isAI = true;
            validInput = true;
        }
        else if (ch == 'n') {
            isAI = false;
            validInput = true;
        }
        else {
            std::cout << "\tInvalid input, please try again" << std::endl;
            std::cout << std::endl;
        }
    }
    while (!validInput);
    std::cout << std::endl;

    return isAI; 
}

// Prompts user for a time limit for a computer/AI player
int promptAITimeLimit(int player) {
    int limit = 0;
    std::string str;
    bool validInput = false;

    do {
        std::cout << "Enter time limit for player " << player
            << " (seconds per move): ";
        std::cin >> str;
        std::istringstream iss(str);
        iss >> limit;

        if (!iss.eof() || limit <= 0) {
            std::cout << "Invalid input, please try again" << std::endl;
            std::cout << std::endl;
        }
        else {
            validInput = true;
        }
    }
    while (!validInput);
    std::cout << std::endl;

    return limit;
}
