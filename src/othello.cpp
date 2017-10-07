#include "game.hpp"

bool promptAIPlayer(int player);
float promptAITimeLimit();

int main() {
    othelloBoard board;
    othelloGame game;
    bool blackComputer = false, whiteComputer = false;
    float timeLimit = 0.0;

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
            std::cout << "\tInvalid input, please try again" << std::endl
                << std::endl;
        }
    }
    while (!validInput);
    std::cout << std::endl;

    // Initialize game appropriately
    if (choice == 1) {
        blackComputer = promptAIPlayer(1);
        whiteComputer = promptAIPlayer(2);

        if (blackComputer || whiteComputer) {
            timeLimit = promptAITimeLimit();
        }

        game.newGame(blackComputer, whiteComputer, timeLimit);
    }
    else {
        std::string fileName;
        std::cout << "Enter file name: ";
        std::cin >> fileName;
        std::cout << std::endl;

        blackComputer = promptAIPlayer(1);
        whiteComputer = promptAIPlayer(2);

        if (blackComputer || whiteComputer) {
            timeLimit = promptAITimeLimit();
        }

        game.loadGame(fileName, blackComputer, whiteComputer);
    }

    game.board.displayBoard(1);
    // TODO main game logic goes here

    return 0;
}

// Prompts user if black/white is the computer
bool promptAIPlayer(int player) {
    bool isAI = false;
    std::string str;
    char ch;
    bool validInput = false;

    do {
        std::cout << "Is " << ((player == 1) ? "black" : "white") << " the computer?" << std::endl;
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
            std::cout << "\tInvalid input, please try again" << std::endl
                << std::endl;
        }
    }
    while (!validInput);
    std::cout << std::endl;

    return isAI; 
}

// Prompts user for a time limit for a computer/AI player
float promptAITimeLimit() {
    float limit = 0;
    std::string str;
    bool validInput = false;

    do {
        std::cout << "Enter time limit for computer (seconds per move): ";
        std::cin >> str;
        std::istringstream iss(str);
        iss >> limit;

        if (!iss.eof() || limit <= 0) {
            std::cout << "Invalid input, please try again" << std::endl
                << std::endl;
        }
        else {
            validInput = true;
        }
    }
    while (!validInput);
    std::cout << std::endl;

    return limit;
}
