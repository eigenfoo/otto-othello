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
    int maxDepth = 64 - board.discsOnBoard;
    std::pair<int, std::list<int>> bestMove;

    for (int depthLimit = 1; depthLimit <= maxDepth; depthLimit++) {
        std::cout << "\tSearching to depth " << depthLimit;

        // TODO implement killer move heuristic
        move = this->depthLimitedAlphaBeta(board, depthLimit, startTime,
                board.timeLimit);

        if (move.first == -1) {
            std::cout << "\t\tSearch aborted" << std::endl;
            break;
        }
        else {
            std::cout << "\t\tSearch complete" << std::endl;
            bestMove = move;
        }

        // If time is more than half up, don't bother searching to next depth
        if (this->stopTimer(startTime) > 0.5*board.timeLimit) {
            break;
        }
    }

    std::cout << "Time elapsed: " << this->stopTimer(startTime) << " sec\n"
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

    // Initialize root node
    this->nodeStack[0].isMaxNode = true;
    this->nodeStack[0].alpha = INT_MIN;
    this->nodeStack[0].beta = INT_MAX;
    this->nodeStack[0].score = INT_MIN;
    this->nodeStack[0].board = board;
    this->nodeStack[0].moveIterator = this->nodeStack[0].board.moves.begin();
    this->nodeStack[0].lastMove = this->nodeStack[0].board.moves.end();

    int depth = 0;
    int leafScore = 0;
    int oppColor = (this->color == 1 ? 2 : 1);
    std::map<int, std::list<int>>::iterator bestMove =
        this->nodeStack[0].board.moves.begin();

    // While we have not evaluated all the root's children
    // FIXME make sure to implement Sable's +/-1 fix
    while (true) {
        // If we can prune, or have evaluated all children
        if (this->nodeStack[depth].beta <= this->nodeStack[depth].alpha
                || this->nodeStack[depth].moveIterator == this->nodeStack[depth].lastMove) {

            if (depth-- == 0) {
                if (this->nodeStack[1].score > this->nodeStack[0].score) {
                    this->nodeStack[0].score = this->nodeStack[1].score;
                    bestMove = std::prev(this->nodeStack[0].moveIterator);
                }

                if (this->nodeStack[0].score > this->nodeStack[0].alpha) {
                    this->nodeStack[0].alpha = this->nodeStack[0].score;
                }

                break;
            }

            if (this->nodeStack[depth].isMaxNode) {
                if (this->nodeStack[depth+1].score > this->nodeStack[depth].score) {
                    this->nodeStack[depth].score = this->nodeStack[depth+1].score;
                    if (depth == 0) {
                        bestMove = std::prev(this->nodeStack[0].moveIterator);
                    }
                }

                if (this->nodeStack[depth].score > this->nodeStack[depth].alpha) {
                    this->nodeStack[depth].alpha = this->nodeStack[depth].score;
                }
            }
            else {
                if (this->nodeStack[depth+1].score < this->nodeStack[depth].score) {
                    this->nodeStack[depth].score = this->nodeStack[depth+1].score;
                }

                if (this->nodeStack[depth].score < this->nodeStack[depth].beta) {
                    this->nodeStack[depth].beta = this->nodeStack[depth].score;
                }
            }
        }
        else {
            // Generate next node, increment moveIterator
            this->nodeStack[depth+1].board = this->nodeStack[depth].board;
            this->nodeStack[depth+1].board.updateBoard(
                    (this->nodeStack[depth].isMaxNode ? this->color : oppColor),
                    *this->nodeStack[depth].moveIterator);
            this->nodeStack[depth].moveIterator++;

            // If the next depth is not at the depth limit
            if (depth + 1 < depthLimit) {
                depth++;

                // Initialize next node in stack
                this->nodeStack[depth].isMaxNode = !this->nodeStack[depth-1].isMaxNode;
                this->nodeStack[depth].score =
                    (this->nodeStack[depth].isMaxNode ? INT_MIN : INT_MAX);
                this->nodeStack[depth].alpha = this->nodeStack[depth-1].alpha;
                this->nodeStack[depth].beta = this->nodeStack[depth-1].beta;
                this->nodeStack[depth].board.findLegalMoves(
                        (this->nodeStack[depth].isMaxNode ? this->color : oppColor),
                        &this->nodeStack[depth].board.moves);
                this->nodeStack[depth].moveIterator =
                    this->nodeStack[depth].board.moves.begin();
                this->nodeStack[depth].lastMove = this->nodeStack[depth].board.moves.end();
            }
            else {
                // The node is a leaf: evaluate heuristic and update values
                // TODO change this to heuristic.evaluate once alphabeta is done
                leafScore = this->heuristic.utility(this->nodeStack[depth+1].board);

                if (this->nodeStack[depth].isMaxNode) {
                    if (leafScore > this->nodeStack[depth].score) {
                        this->nodeStack[depth].score = leafScore;
                        if (depth == 0) {
                            bestMove = std::prev(this->nodeStack[0].moveIterator);
                        }
                    }

                    if (this->nodeStack[depth].score > this->nodeStack[depth].alpha) {
                        this->nodeStack[depth].alpha = this->nodeStack[depth].score;
                    }
                }
                else {
                    if (leafScore < this->nodeStack[depth].score) {
                        this->nodeStack[depth].score = leafScore;
                    }

                    if (this->nodeStack[depth].score < this->nodeStack[depth].beta) {
                        this->nodeStack[depth].beta = this->nodeStack[depth].score;
                    }
                }
            }
        }

        // If we are almost out of time, failure
        if (this->stopTimer(startTime) > 0.99*timeLimit) {
            std::pair<int, std::list<int>> move;
            move.first = -1;
            return move;
        }
    }

    return *bestMove;
}
