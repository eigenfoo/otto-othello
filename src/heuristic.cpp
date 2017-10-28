#include "heuristic.hpp"
// Heuristic is from the perspective that black maximizes
// TODO the heuristic should change as the game progresses!

int othelloHeuristic::evaluate(othelloBoard &board, int color) {
    if (board.terminalState()) {
        return 100000*utility(board);
    }

    discDifferenceScore = discDifference(board);
    mobilityScore = mobility(board, color);
    potentialMobilityScore = potentialMobility(board, color);
    stabilityScore = stability(board, color);
    parityScore = parity(board, color);

    if (board.discsOnBoard <= 20) {
        // Opening game
        return 5*mobilityScore
            + 2*potentialMobilityScore
            + 1000*stabilityScore;
    }
    else if (board.discsOnBoard <= 58) {
        //Midgame
        return discDifferenceScore
            + 5*mobilityScore
            + 2*potentialMobilityScore
            + 1000*stabilityScore
            + 500*parityScore;
    }
    else {
        // Endgame
        return 500*discDifferenceScore
            + 1000*stabilityScore
            + 2000*parityScore;
    }
}

int othelloHeuristic::utility(othelloBoard &board) {
    return std::accumulate(board.positions.begin(), board.positions.end(), 0);
}

// Relative disc difference between the two players
int othelloHeuristic::discDifference(othelloBoard &board) {
    // Number of black discs
    foo = std::count(board.positions.begin(),
            board.positions.end(), 1);

    // Number of white discs
    bar = std::count(board.positions.begin(),
            board.positions.end(), -1);
    
    if (foo > bar) {
        discDifferenceScore = (100 * foo) / (foo + bar);
    }
    else if (foo < bar) {
        discDifferenceScore = (-100 * bar) / (foo + bar);
    }
    else {
        discDifferenceScore = 0;
    }

    return discDifferenceScore;
}

// Number of possible moves
int othelloHeuristic::mobility(othelloBoard &board, int &color) {
    // Black mobility
    board.findLegalMoves(1, &pMoves);
    foo = pMoves.size();
    pMoves.clear();

    // White mobility
    board.findLegalMoves(-1, &pMoves);
    bar = pMoves.size();
    pMoves.clear();

    mobilityScore = 0;

    if (foo > bar) {
        mobilityScore = (100*foo) / (foo + bar);
    }
    else if (foo < bar) {
        mobilityScore = (-100*bar) / (foo + bar);
    }

    return mobilityScore;
}

int othelloHeuristic::potentialMobility(othelloBoard &board, int &color) {
    return 0;
}

// Computes a lower bound on the number of stable discs
int othelloHeuristic::stability(othelloBoard &board, int &color) {
    stableDiscs.clear();

    stableDiscsFromCorner(board, 0, color);
    stableDiscsFromCorner(board, 7, color);
    stableDiscsFromCorner(board, 56, color);
    stableDiscsFromCorner(board, 63, color);

    return stableDiscs.size();
}

// Finds the number of stable discs given a corner
void othelloHeuristic::stableDiscsFromCorner(othelloBoard &board, int corner,
        int &color) {

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

    int horizIncr = 1, horizStop = 7;
    int vertIncr = 8, vertStop = 56;
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
                if (board.positions[j] == color && stableDiscs.find(j) == stableDiscs.end()) {
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

// Who is expected to have the last move in the game
int othelloHeuristic::parity(othelloBoard &board, int &color) {
    if (color == 1) {
        if (board.discsOnBoard % 2 == 0) {
            parityScore = -1;
        }
        else {
            parityScore = 1;
        }
    }
    else {
        if (board.discsOnBoard % 2 == 0) {
            parityScore = -1;
        }
        else {
            parityScore = 1;
        }
    }
    return parityScore;
}

// Assigns a weight to every square on the board
int othelloHeuristic::squareWeights(othelloBoard &board) {
    std::vector<int> weights = {
         100, -100, 100,  50,  50, 100, -100,  100,
        -100, -200, -50, -50, -50, -50, -200, -100,
         100,  -50, 100,   0,   0, 100,  -50,  100,
          50,  -50,   0,   0,   0,   0,  -50,   50,
          50,  -50,   0,   0,   0,   0,  -50,   50,
         100,  -50, 100,   0,   0, 100,  -50,  100,
        -100, -200, -50, -50, -50, -50, -200, -100,
         100, -100, 100,  50,  50, 100, -100,  100,
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

    return std::inner_product(board.positions.begin(), board.positions.end(),
            weights.begin(), 0);
}
