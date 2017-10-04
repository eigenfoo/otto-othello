#include <iostream>
#include <string>

bool promptAIPlayer(int player);
int promptAITimeLimit(int player);

int main() {
    int choice = 0;
    std::cout << "Load a game or start a new one?" << std::endl;
    std::cout << "\t1 -> Start a new game" << std::endl;
    std::cout << "\t2 -> Load a board from file" << std::endl;

    while (true) {
        std::cout << "\tSelection: ";
        std::cin >> choice;

        if (choice == 1 || choice == 2) {
            break;
        }
        else {
            std::cout << "\tInvalid input, please try again" << std::endl;
        }
    }

    std::cout << std::endl;

    if (choice == 2) {
        std::string fileName;
        std::cout << "Enter file name: ";
        std::cin >> fileName;
        // FIXME Somehow load the board!
    }
    else {
        int timeLimit1 = 0;
        int timeLimit2 = 0;

        bool player1AI = promptAIPlayer(1);
        if (player1AI) {
            timeLimit1 = promptAITimeLimit(1);
        }

        bool player2AI = promptAIPlayer(2);
        if (player2AI) {
            timeLimit2 = promptAITimeLimit(2);
        }
    }

    // FIXME main game logic goes here

    return 0;
}

bool promptAIPlayer(int player) {
    char choice = 'n';
    bool isAI = false;

    std::cout << "Is Player " << player << " the computer?" << std::endl;
    std::cout << "\ty -> Yes" << std::endl;
    std::cout << "\tn -> No" << std::endl;
    std::cout << "\tSelection: ";
    std::cin >> choice;
    std::cout << std::endl;

    if (choice == 'y') {
        isAI = true;
    }
    else if (choice == 'n') {
        isAI = false;
    }

    return isAI;
}

int promptAITimeLimit(int player) {
    int limit = 0;

    while (true) {
        std::cout << "Enter time limit for player " << player
            << " (seconds per move): ";
        std::cin >> limit;
        std::cout << std::endl;

        if (limit <= 0) {
            std::cout << "Non-positive integer input, please try again"
                << std::endl;
        }
        else {
            break;
        }
    }

    return limit;
}
