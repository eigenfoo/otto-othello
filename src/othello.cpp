#include "game.hpp"

int promptNewGame();
void initializeGame(int choice, othelloGame &game,
        bool &blackComputer, bool &whiteComputer, float &timeLimit);
bool promptAIPlayer(int player);
float promptAITimeLimit();

int main() {
    othelloBoard board;
    othelloGame game;
    bool blackComputer = false, whiteComputer = false;
    float timeLimit = 0.0;

    // Initialize game, prompting user appropriately
    int newGame = promptNewGame();
    initializeGame(newGame, game, blackComputer, whiteComputer, timeLimit);

    // Play game
    if (game.toMove == -1) {
        game.board.findLegalMoves(-1, &game.board.moves);
        game.board.displayBoard(-1);
        game.board.displayLegalMoves();
        game.move(-1);

        game.checkGameOver();
    }

    //while (!game.passes[0] && !game.passes[1]) {
    while (!game.gameOver) {
        game.board.findLegalMoves(1, &game.board.moves);
        game.board.displayBoard(1);
        game.board.displayLegalMoves();
        game.move(1);
        game.checkGameOver();

        if (game.gameOver) {
            break;
        }

        game.board.findLegalMoves(-1, &game.board.moves);
        game.board.displayBoard(-1);
        game.board.displayLegalMoves();
        game.move(-1);
        game.checkGameOver();
    }

    return 0;
}

// Prompt user for new or loaded game
int promptNewGame() {
    int choice = 0;

    std::string str;
    bool validInput = false;
    do {
        std::cout << "Start a new game, or load a game from a save file?"
            << std::endl;
        std::cout << "\t1 -> Start" << std::endl;
        std::cout << "\t2 -> Load" << std::endl;
        std::cout << "\tSelection: ";
        std::cin >> str;
        while (std::cin.get() != '\n');          // clear buffer
        std::istringstream iss(str);
        iss >> choice;

        if (choice == 1 || choice == 2) {
            validInput = true;
        }
        else {
            std::cout << "\tInvalid input. Please try again.\n" << std::endl;
        }
    }
    while (!validInput);
    std::cout << std::endl;

    return choice;
}

// Initialize game appropriately
void initializeGame(int choice, othelloGame &game,
        bool &blackComputer, bool &whiteComputer, float &timeLimit) {
    if (choice == 1) {
        blackComputer = promptAIPlayer(1);
        whiteComputer = promptAIPlayer(-1);

        if (blackComputer || whiteComputer) {
            timeLimit = promptAITimeLimit();
        }

        game.newGame(blackComputer, whiteComputer, timeLimit);
    }
    else {
        std::string fileName;
        std::cout << "Enter file name: ";
        std::cin >> fileName;
        while (std::cin.get() != '\n');          // clear buffer
        std::cout << std::endl;

        blackComputer = promptAIPlayer(1);
        whiteComputer = promptAIPlayer(-1);

        game.loadGame(fileName, blackComputer, whiteComputer);
    }
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
        while (std::cin.get() != '\n');          // clear buffer
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
            std::cout << "\tInvalid input. Please try again.\n" << std::endl;
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
        while (std::cin.get() != '\n');          // clear buffer
        std::istringstream iss(str);
        iss >> limit;

        if (!iss.eof() || limit <= 0) {
            std::cout << "Invalid input. Please try again.\n" << std::endl;
        }
        else {
            validInput = true;
        }
    }
    while (!validInput);
    std::cout << std::endl;

    return limit;
}
