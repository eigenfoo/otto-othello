#include "heuristic.hpp"
// Heuristic is from the perspective that the calling player is the maximizing
// player, regardless of the player's color

int othelloHeuristic::evaluate(othelloBoard &board, int color) {
    if (board.terminalState()) {
        return 100000*utility(board, color);
    }

    if (board.discsOnBoard <= 20) {
        // Opening game
        return 5*mobility(board, color)
            + 5*potentialMobility(board, color)
            + 20*squareWeights(board, color)
            + 10000*corners(board, color)
            + 10000*stability(board, color);
    }
    else if (board.discsOnBoard <= 58) {
        // Midgame
        return 10*discDifference(board, color)
            + 2*mobility(board, color)
            + 2*potentialMobility(board, color)
            + 10*squareWeights(board, color)
            + 100*parity(board)
            + 10000*corners(board, color)
            + 10000*stability(board, color);
    }
    else {
        // Endgame
        return 500*discDifference(board, color)
            + 500*parity(board)
            + 10000*corners(board, color)
            + 10000*stability(board, color);
    }
}

int othelloHeuristic::utility(othelloBoard &board, int &color) {
    int util = std::accumulate(board.positions.begin(),
            board.positions.end(), 0);

    if (color == 1) {
        return util; 
    }
    else {
        return -1*util;
    }
}

// Relative disc difference between the two players
int othelloHeuristic::discDifference(othelloBoard &board, int &color) {
    int blackCount = std::count(board.positions.begin(),
            board.positions.end(), 1);
    int whiteCount = std::count(board.positions.begin(),
            board.positions.end(), -1);

    if (color == 1) {
        return 100 * (blackCount - whiteCount) / (blackCount + whiteCount);
    }
    else {
        return 100 * (whiteCount - blackCount) / (blackCount + whiteCount);
    }
}

// Number of possible moves
int othelloHeuristic::mobility(othelloBoard &board, int &color) {
    board.findLegalMoves(1, &pMoves);
    int blackMoves = pMoves.size();
    pMoves.clear();

    board.findLegalMoves(-1, &pMoves);
    int whiteMoves = pMoves.size();
    pMoves.clear();

    if (color == 1) {
        return 100 * (blackMoves - whiteMoves) / (blackMoves + whiteMoves + 1);
    }
    else {
        return 100 * (whiteMoves - blackMoves) / (blackMoves + whiteMoves + 1);
    }
}

int othelloHeuristic::potentialMobility(othelloBoard &board, int color) {
    int myPotentialMobility = playerPotentialMobility(board, color);
    int opponentPotentialMobility = playerPotentialMobility(board, -color);

    return 100 * (myPotentialMobility - opponentPotentialMobility)
        / (myPotentialMobility + opponentPotentialMobility + 1);
}

int othelloHeuristic::playerPotentialMobility(othelloBoard &board, int color) {
    std::vector<int> boardInterior = {18, 19, 20, 21,
                                      26, 27, 28, 29,
                                      34, 35, 36, 37,
                                      42, 43, 44, 45};

    int here = 0, up = 0, down = 0, left = 0, right = 0,
        upperLeft = 0, upperRight = 0, lowerLeft = 0, lowerRight = 0;
    int potentialMobility = 0;

    for (int square : boardInterior) {
        here = board.positions[square];
        up = board.positions[square-8];
        down = board.positions[square+8];
        left = board.positions[square-1];
        right = board.positions[square+1];
        upperLeft = board.positions[square-9];
        upperRight = board.positions[square-7];
        lowerLeft = board.positions[square+7];
        lowerRight = board.positions[square+9];

        if (here == -color && up == 0)
            potentialMobility++;
        if (here == -color && down == 0)
            potentialMobility++;
        if (here == -color && right == 0)
            potentialMobility++;
        if (here == -color && right == 0)
            potentialMobility++;
        if (here == -color && upperLeft == 0)
            potentialMobility++;
        if (here == -color && upperRight == 0)
            potentialMobility++;
        if (here == -color && lowerLeft == 0)
            potentialMobility++;
        if (here == -color && lowerRight == 0)
            potentialMobility++;
    }

    std::vector<int> topRow = {10, 11, 12, 13};
    for (int square : topRow) {
        here = board.positions[square];
        left = board.positions[square-1];
        right = board.positions[square+1];
        if (here == -color && left == 0)
            potentialMobility++;
        if (here == -color && right == 0)
            potentialMobility++;
    }

    std::vector<int> bottomRow = {50, 51, 52, 53};
    for (int square : bottomRow) {
        here = board.positions[square];
        left = board.positions[square-1];
        right = board.positions[square+1];
        if (here == -color && left == 0)
            potentialMobility++;
        if (here == -color && right == 0)
            potentialMobility++;
    }

    std::vector<int> leftColumn = {17, 25, 33, 41};
    for (int square : leftColumn) {
        here = board.positions[square];
        up = board.positions[square-8];
        down = board.positions[square+8];
        if (here == -color && up == 0)
            potentialMobility++;
        if (here == -color && down == 0)
            potentialMobility++;
    }

    std::vector<int> rightColumn = {22, 30, 38, 46};
    for (int square : leftColumn) {
        here = board.positions[square];
        up = board.positions[square-8];
        down = board.positions[square+8];
        if (here == -color && up == 0)
            potentialMobility++;
        if (here == -color && down == 0)
            potentialMobility++;
    }

    return potentialMobility;
}

// Computes a lower bound on the number of stable discs
int othelloHeuristic::stability(othelloBoard &board, int color) {
    stableDiscs.clear();

    stableDiscsFromCorner(board, 0, color);
    stableDiscsFromCorner(board, 7, color);
    stableDiscsFromCorner(board, 56, color);
    stableDiscsFromCorner(board, 63, color);

    int myStables = stableDiscs.size();

    stableDiscsFromCorner(board, 0, -color);
    stableDiscsFromCorner(board, 7, -color);
    stableDiscsFromCorner(board, 56, -color);
    stableDiscsFromCorner(board, 63, -color);

    int opponentStables = stableDiscs.size();

    return myStables - opponentStables;
}

// Finds the number of stable discs given a corner
void othelloHeuristic::stableDiscsFromCorner(othelloBoard &board, int corner,
        int color) {
    bool down, right;
    if (corner == 0) {
        down = true;
        right = true;
    }
    else if (corner == 7) {
        down = true;
        right = false;
    }
    else if (corner == 56) {
        down = false;
        right = true;
    }
    else {
        down = false;
        right = false;
    }

    int horizIncr = 1, horizStop = 7, vertIncr = 8, vertStop = 56;
    if (!right) {
        horizIncr *= -1;
        horizStop *= -1;
    }
    if (!down) {
        vertIncr *= -1;
        vertStop *= -1;
    }

    // Iterate horizontally
    for (int i = corner; i != corner + horizIncr + horizStop; i += horizIncr) {
        // If there is a disc of our color on this square
        if (board.positions[i] == color) {
            // Iterate vertically
            for (int j = i; j != i + vertStop; j+= vertIncr) {
                // If there is a disc of our color on this square,
                // and it is not in the set of stable discs
                if (board.positions[j] == color
                        && stableDiscs.find(j) == stableDiscs.end()) {
                    // Insert it to the set
                    stableDiscs.insert(j);
                }
                // If we come across a disc of the opposite color, break
                else {
                    break;
                }
            }
        }
        // Otherwise, break
        else {
            break;
        }
    }
}

int othelloHeuristic::parity(othelloBoard &board) {
    int squaresRemaining = 64 - board.discsOnBoard;

    if (squaresRemaining % 2 == 0) {
        return -1;
    }
    else {
        return 1;
    }
}

// Assigns a weight to every square on the board
int othelloHeuristic::squareWeights(othelloBoard &board, int &color) {
    std::vector<int> weights = {
         200, -100, 100,  50,  50, 100, -100,  200,
        -100, -200, -50, -50, -50, -50, -200, -100,
         100,  -50, 100,   0,   0, 100,  -50,  100,
          50,  -50,   0,   0,   0,   0,  -50,   50,
          50,  -50,   0,   0,   0,   0,  -50,   50,
         100,  -50, 100,   0,   0, 100,  -50,  100,
        -100, -200, -50, -50, -50, -50, -200, -100,
         200, -100, 100,  50,  50, 100, -100,  200,
    };

    if (board.positions[0] != 0) {
        weights[1]  = 0;
        weights[2]  = 0;
        weights[3]  = 0;
        weights[8]  = 0;
        weights[9]  = 0;
        weights[10] = 0;
        weights[11] = 0;
        weights[16] = 0;
        weights[17] = 0;
        weights[18] = 0;
        weights[24] = 0;
        weights[25] = 0;
    }

    if (board.positions[7] != 0) {
        weights[4]  = 0;
        weights[5]  = 0;
        weights[6]  = 0;
        weights[12] = 0;
        weights[13] = 0;
        weights[14] = 0;
        weights[15] = 0;
        weights[21] = 0;
        weights[22] = 0;
        weights[23] = 0;
        weights[30] = 0;
        weights[31] = 0;
    }

    if (board.positions[56] != 0) {
        weights[32] = 0;
        weights[33] = 0;
        weights[40] = 0;
        weights[41] = 0;
        weights[42] = 0;
        weights[48] = 0;
        weights[49] = 0;
        weights[50] = 0;
        weights[51] = 0;
        weights[57] = 0;
        weights[58] = 0;
        weights[59] = 0;
    }

    if (board.positions[63] != 0) {
        weights[38] = 0;
        weights[39] = 0;
        weights[45] = 0;
        weights[46] = 0;
        weights[47] = 0;
        weights[52] = 0;
        weights[53] = 0;
        weights[54] = 0;
        weights[55] = 0;
        weights[60] = 0;
        weights[61] = 0;
        weights[62] = 0;
    }

    if (color == 1) {
        return std::inner_product(board.positions.begin(),
                board.positions.end(), weights.begin(), 0);
    }
    else {
        return -1*std::inner_product(board.positions.begin(),
                board.positions.end(), weights.begin(), 0);
    }
}

int othelloHeuristic::corners(othelloBoard &board, int &color) {
    std::vector<int> corners = {0, 7, 56, 63};
    int blackCorners = 0;
    int whiteCorners = 0;

    for (int corner : corners) {
        if (board.positions[corner] == 1) {
            blackCorners++;
        }
        else if (board.positions[corner] == -1) {
            whiteCorners++;
        }
    }

    if (color == 1) {
        return 100 * (blackCorners - whiteCorners)
            / (blackCorners + whiteCorners + 1);
    }
    else {
        return 100 * (whiteCorners - blackCorners)
            / (blackCorners + whiteCorners + 1);
    }
}
