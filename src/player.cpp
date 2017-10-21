#include "player.hpp"

// Driver for player's move, regardless of player
std::pair<int, std::list<int>> othelloPlayer::move(othelloBoard &board,
        std::unordered_map<int, std::list<int>> &legalMoves,
        bool &pass) {

    std::pair<int, std::list<int>> moveChoice;
    if (this->computer) {
        moveChoice = this->computerMove(board, legalMoves, pass);
    }
    else {
        moveChoice = this->humanMove(board, legalMoves, pass);
    }

    return moveChoice;
}

// Prompts user for next move
// `board` is only necessary for polymorphic `move`...
std::pair<int, std::list<int>> othelloPlayer::humanMove(othelloBoard &board,
        std::unordered_map<int, std::list<int>> &legalMoves,
        bool &pass) {

    std::string str;
    std::pair<int, std::list<int>> move;
    int choice = 0;
    bool validInput = false;
    int i = 0;

    if (legalMoves.empty()) {
        std::cout << "No legal moves!" << std::endl;
        std::cout << "\tEnter any string to pass: ";
        std::cin >> str;
        std::cout << std::endl;
        pass = true;
        return move;
    }

    do {
        std::cout << "\tSelect move number: ";
        std::cin >> str;
        std::istringstream iss(str);
        iss >> choice;

        if (!iss.eof() || choice > legalMoves.size() || choice < 1) {
            std::cout << "\tInvalid input. Please try again.\n" << std::endl;
        }
        else {
            validInput = true;
            std::cout << std::endl;
        }
    }
    while (!validInput);

    for (std::pair<int, std::list<int>> keyval : legalMoves) {
        move = keyval;
        i++;
        if (i == choice) {
            break;
        }
    }

    return move;
}

// Driver for the AI algorithm
std::pair<int, std::list<int>> othelloPlayer::computerMove(othelloBoard &board,
        std::unordered_map<int, std::list<int>> &legalMoves,
        bool &pass) {

    std::pair<int, std::list<int>> move;
    auto startTime = this->startTimer();

    if (legalMoves.empty()) {
        std::cout << "No legal moves." << std::endl;
        std::cout << "\tComputer passes.\n" << std::endl;
        pass = true;
        return move;
    }
    else if (legalMoves.size() == 1) {
        std::cout << "Only one legal move." << std::endl;
        std::cout << "\tComputer takes only legal move.\n" << std::endl;
        // FIXME there must be a better way to get the ONLY element...
        for (auto keyval : legalMoves) {
            move = keyval;
        }
        return move;
    }

    // TODO check if board position is in opening book

    std::cout << "Searching game tree...\n" << std::endl;

    int alpha = -infinity;
    int beta = infinity;
    int maxDepth = 60 - board.plies + 1;
    std::pair<std::pair<int, std::list<int>>, int> movescore;

    for (int depth = 1; depth < maxDepth; depth++) {
        std::cout << "\tSearching to depth " << depth << "..." << std::endl;

        std::pair<int, std::list<int>> bestMove;
        int bestScore = -infinity;
        movescore = this->alphabeta(board, depth, alpha, beta, true);

        if (movescore.second > bestScore) {
            bestMove = movescore.first;
            bestScore = movescore.second;
        }
        else if (movescore.second == bestScore) {
            if (rand() % 2 == 0) {
                bestMove = movescore.first;
                bestScore = movescore.second;
            }
        }

        // If time is more than half up, break.
        std::chrono::duration<double> elapsedSeconds =
            this->stopTimer(startTime);
        if (elapsedSeconds.count() > 0.5*board.timeLimit) {
            break;
        }
    }

    // FIXME gives compiler error
    move = bestMove;
    std::chrono::duration<double> elapsedSeconds = this->stopTimer(startTime);
    std::cout << "Time elapsed: " << elapsedSeconds.count() << " sec\n"
        << std::endl;

    return move;
}

std::chrono::time_point<std::chrono::system_clock> othelloPlayer::startTimer() {
    return std::chrono::system_clock::now();
}

std::chrono::duration<double> othelloPlayer::stopTimer(
        std::chrono::time_point<std::chrono::system_clock> startTime) {

    std::chrono::time_point<std::chrono::system_clock> endTime =
        std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = endTime - startTime;
    return elapsedSeconds;

}

// TODO figure out alphabeta...
// Performs depth-limited minimax search with alpha-beta pruning
std::pair<std::pair<int, std::list<int>>, int> othelloPlayer::alphabeta(
        othelloBoard &board, int depth, int alpha, int beta, bool maximizing) {

    std::pair<std::pair<int, std::list<int>>, int> movescore;
    return movescore;
}
