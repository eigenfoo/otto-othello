#include "player.hpp"

// Driver for player's move, regardless of player
std::pair<int, std::list<int>> othelloPlayer::move(othelloBoard &board,
        std::map<int, std::list<int>> &legalMoves,
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
        std::map<int, std::list<int>> &legalMoves,
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
        std::map<int, std::list<int>> &legalMoves, bool &pass) {
    std::chrono::time_point<std::chrono::system_clock> startTime =
        this->startTimer();
    std::pair<int, std::list<int>> move;

    if (legalMoves.empty()) {
        std::cout << "No legal moves!" << std::endl;
        std::cout << "\tComputer passes.\n" << std::endl;
        pass = true;
        return move;
    }
    else if (legalMoves.size() == 1) {
        std::cout << "Only one legal move!" << std::endl;
        std::cout << "\tComputer takes only legal move.\n" << std::endl;
        move = *(legalMoves.begin());
        return move;
    }

    // TODO check if board position is in opening book

    // Search by iterative deepening
    std::cout << "Searching game tree..." << std::endl;

    int maxDepth = 60 - board.plies + 1;
    std::pair<int, std::list<int>> bestMove;

    for (int depth = 1; depth < maxDepth; depth++) {
        std::cout << "\tSearching to depth " << depth << "..." << std::endl;

        // TODO implement killer move heuristic
        move = this->depthLimitedAlphaBeta(board, depth, startTime, board.timeLimit);
        std::cout << "Done with depth " << depth << "!" << std::endl;

        if (move.first == -1) {
            break;
        }
        else {
            bestMove = move;
        }

        // If time is more than half up, don't bother searching to next depth
        float elapsedSeconds = this->stopTimer(startTime);
        if (elapsedSeconds > 0.5*board.timeLimit) {
            break;
        }
    }

    float elapsedSeconds = this->stopTimer(startTime);
    std::cout << "Time elapsed: " << elapsedSeconds << " sec\n"
        << std::endl;

    return bestMove;
}

// Returns time point
std::chrono::time_point<std::chrono::system_clock> othelloPlayer::startTimer() {
    return std::chrono::system_clock::now();
}

// Returns time elapsed in seconds
float othelloPlayer::stopTimer(
        std::chrono::time_point<std::chrono::system_clock> startTime) {
    std::chrono::time_point<std::chrono::system_clock> endTime =
        std::chrono::system_clock::now();
    std::chrono::duration<float> elapsedSeconds = endTime - startTime;
    return elapsedSeconds.count();
}

// Performs depth-limited minimax search with alpha-beta pruning
// Implemented iteratively to avoid recursion overhead
// Returns move for square -1 if time runs out
std::pair<int, std::list<int>> othelloPlayer::depthLimitedAlphaBeta(
        othelloBoard &board, int depthLimit,
        std::chrono::time_point<std::chrono::system_clock> startTime,
        float timeLimit) {

    // Node stack
    struct {
        bool isMaxNode;
        int alpha;
        int beta;
        int score;
        othelloBoard board;
        std::map<int, std::list<int>>::iterator moveIterator;
        std::map<int, std::list<int>>::iterator lastMove;
    } nodeStack[60];

    // Initialize root node
    nodeStack[0].isMaxNode = true;
    nodeStack[0].alpha = -infinity;
    nodeStack[0].beta = infinity;
    nodeStack[0].score = -infinity;
    nodeStack[0].board = board;
    nodeStack[0].moveIterator = nodeStack[0].board.moves.begin();
    nodeStack[0].lastMove = nodeStack[0].board.moves.end();

    int depth = 0;
    std::map<int, std::list<int>>::iterator bestMove;

    // FIXME program never completes search to depth 2...
    // While we have not evaluated all the root's children
    while (nodeStack[0].moveIterator != nodeStack[0].lastMove) {
        // If we can prune, or have evaluated all children
        if (nodeStack[depth].beta <= nodeStack[depth].alpha
                || nodeStack[depth].moveIterator == nodeStack[depth].lastMove) {
            if (nodeStack[depth].isMaxNode) {
                if (nodeStack[depth+1].score > nodeStack[depth].score) {
                    nodeStack[depth].score = nodeStack[depth+1].score;
                    if (depth == 0) {
                        bestMove = std::prev(nodeStack[0].moveIterator);
                    }
                }

                if (nodeStack[depth].score > nodeStack[depth].alpha) {
                    nodeStack[depth].alpha = nodeStack[depth].score;
                }

                if (depth == 0) {
                    break;
                }
            }
            else {
                if (nodeStack[depth+1].score < nodeStack[depth].score) {
                    nodeStack[depth].score = nodeStack[depth+1].score;
                }

                if (nodeStack[depth].score < nodeStack[depth].beta) {
                    nodeStack[depth].beta = nodeStack[depth].score;
                }
            }
        }
        else {
            // Evaluate next node and search
            // FIXME maybe the problem is here??
            nodeStack[depth+1].board = nodeStack[depth].board;
            nodeStack[depth+1].board.updateBoard(this->color,
                    *nodeStack[depth].moveIterator);
            nodeStack[depth].moveIterator++;

            // If the next depth is not at the depth limit
            if (depth + 1 < depthLimit) {
                depth++;

                // Initialize next node in stack
                nodeStack[depth].isMaxNode = !nodeStack[depth-1].isMaxNode;
                nodeStack[depth].score = (nodeStack[depth].isMaxNode ?
                        -infinity : infinity);
                nodeStack[depth].alpha = nodeStack[depth-1].alpha;
                nodeStack[depth].beta = nodeStack[depth-1].beta;
                nodeStack[depth].board.findLegalMoves(this->color,
                        &nodeStack[depth].board.moves);
                nodeStack[depth].moveIterator =
                    nodeStack[depth].board.moves.begin();
                nodeStack[depth].lastMove = nodeStack[depth].board.moves.end();
            }
            else {
                // The next node is a leaf: evaluate heuristic and update values
                int score = this->heuristic.evaluate(nodeStack[depth+1].board,
                        this->color);
                std::cout << score << std::endl; // REMOVE AFTER DEBUGGING

                if (nodeStack[depth].isMaxNode) {
                    if (score > nodeStack[depth].score) {
                        nodeStack[depth].score = score;
                        if (depth == 0) {
                            bestMove = std::prev(nodeStack[0].moveIterator);
                        }
                    }

                    if (nodeStack[depth].score > nodeStack[depth].alpha) {
                        nodeStack[depth].alpha = nodeStack[depth].score;
                    }
                }
                else {
                    if (score < nodeStack[depth].score) {
                        nodeStack[depth].score = score;
                    }

                    if (nodeStack[depth].score < nodeStack[depth].beta) {
                            nodeStack[depth].beta = nodeStack[depth].score;
                    }
                }
            }
        }

        // If we are almost out of time, failure.
        if (this->stopTimer(startTime) > 0.995*timeLimit) {
            std::pair<int, std::list<int>> move;
            move.first = -1;
            return move;
        }
    }

    return *bestMove;
}
