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
        std::unordered_map<int, std::list<int>> &legalMoves, bool &pass) {

    std::chrono::time_point<std::chrono::system_clock> startTime
        = this->startTimer();
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
    std::cout << "Searching game tree...\n" << std::endl;

    int maxDepth = 60 - board.plies + 1;
    std::pair<int, std::list<int>> bestMove;

    for (int depth = 1; depth < maxDepth; depth++) {
        std::cout << "\tSearching to depth " << depth << "..." << std::endl;

        // FIXME whats up with maximizing? Can the root node always be a max node?
        // TODO implement killer move heuristic
        move = this->depthLimitedAlphaBeta(board, legalMoves, depth, startTime);

        if (move.first >= 0) {
            move = bestMove;
        }

        // If time is more than half up, don't bother searching to next depth
        double elapsedSeconds = this->stopTimer(startTime);
        if (elapsedSeconds > 0.5*board.timeLimit) {
            break;
        }
    }

    double elapsedSeconds = this->stopTimer(startTime);
    std::cout << "Time elapsed: " << elapsedSeconds << " sec\n"
        << std::endl;

    return move;
}

// Returns time point
std::chrono::time_point<std::chrono::system_clock> othelloPlayer::startTimer() {
    return std::chrono::system_clock::now();
}

// Returns time elapsed in seconds
double othelloPlayer::stopTimer(
        std::chrono::time_point<std::chrono::system_clock> startTime) {
    std::chrono::time_point<std::chrono::system_clock> endTime =
        std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = endTime - startTime;
    return elapsedSeconds.count();
}

// Performs depth-limited minimax search with alpha-beta pruning
// Implemented iteratively to avoid recursion overhead
// TODO Returns -1 if time runs out
std::pair<int, std::list<int>> othelloPlayer::depthLimitedAlphaBeta(
        othelloBoard &board,
        std::unordered_map<int, std::list<int>> legalMoves,
        int depthLimit,
        std::chrono::time_point<std::chrono::system_clock> startTime) {

    // Game tree variables
    struct {
        bool isMaxNode;
        int alpha;
        int beta;
        int score;
        othelloBoard board;
        int numLegalMoves;
        int currentMove;
    } nodeStack[50];

    // Initialize root node
    nodeStack[0].isMaxNode = true;
    nodeStack[0].alpha = -infinity;
    nodeStack[0].beta = infinity;
    nodeStack[0].score = -infinity;
    nodeStack[0].board = board;
    nodeStack[0].currentMove = 0;

    std::pair<int, std::list<int>> move;
    int depth = 0;
    int bestMoveIndex = 0;

    // While we have not evaluated all the root's children
    while (nodeStack[0].currentMove < nodeStack[0].numLegalMoves) {
        if (nodeStack[depth].beta <= nodeStack[depth].alpha
                || nodeStack[depth].currentMove == nodeStack[depth].numLegalMoves) {
            // Prune, update parent, decrease depth
            if (depth == 0) {
                if (nodeStack[1].score > nodeStack[0].score) {
                    nodeStack[0].score = nodeStack[1].score;
                    bestMoveIndex = nodeStack[0].currentMove - 1;
                }

                if (nodeStack[0].score > nodeStack[0].alpha) {
                    nodeStack[0].alpha = nodeStack[0].score;
                }

                break;
            }

            if (nodeStack[depth].isMaxNode) {
                if(nodeStack[depth+1].score > nodeStack[depth].score) {
                    nodeStack[depth].score = nodeStack[depth+1].score;
                    if(depth == 0) {
                        bestMoveIndex = nodeStack[depth].currentMove - 1;
                    }
                }

                if(nodeStack[depth].score > nodeStack[depth].alpha) {
                    nodeStack[depth].alpha = nodeStack[depth].score;
                }
            }

            else {
                if(nodeStack[depth+1].score < nodeStack[depth].score) {
                    nodeStack[depth].score = nodeStack[depth+1].score;
                }

                if(nodeStack[depth].score < nodeStack[depth].beta) {
                    nodeStack[depth].beta = nodeStack[depth].score;
                }
            }
        }
        else {
            // Evaluate next node and search
            // FIXME how to apply move to board??
            // nodeStack[depth+1].board = nodeStack[depth]
            nodeStack[depth].currentMove++;

            // If the next depth is not at the depth limit
            if (depth + 1 < depthLimit) {
                // Go one level deeper
                depth++;

                // Initialize next node in stack
                nodeStack[depth].isMaxNode = !nodeStack[depth-1].isMaxNode;
                nodeStack[depth].score = (nodeStack[depth].isMaxNode ? -infinity : infinity);
                nodeStack[depth].alpha = nodeStack[depth-1].alpha;
                nodeStack[depth].beta = nodeStack[depth-1].beta;
                nodeStack[depth].board.findLegalMoves(this->color, &nodeStack[depth].board.moves);
                nodeStack[depth].numLegalMoves = nodeStack[depth].board.moves.size();
                nodeStack[depth].currentMove = 0;
            }
            else {
                // The next node is a leaf: evaluate heuristic and update values
                int score = this->heuristic.evaluate(nodeStack[depth+1].board, this->color);

                if (nodeStack[depth].isMaxNode) {
                    if (score > nodeStack[depth].score) {
                        nodeStack[depth].score = score;
                        if (depth == 0) {
                            bestMoveIndex = nodeStack[depth].currentMove - 1;
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
    }

    return move;
}
