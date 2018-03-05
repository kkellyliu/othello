#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */

    playerBoard = new Board;
    mySide = side;
    // cout << "helllo" << endl;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    bool validMoveFound = false;
    int moveX;
    int moveY;
    Move *m = new Move(0, 0);

    playerBoard->doMove(opponentsMove, otherSide(mySide));

    Move *bestMove = nullptr;
    int bestScore = -99999;

    vector<Move*> possibleMoves = getPossibleMoves(playerBoard);
    for (unsigned int i = 0; i < possibleMoves.size(); i++) {
        Board *tempBoard = playerBoard->copy();
        tempBoard->doMove(possibleMoves[i], mySide);
        int score = heuristic(tempBoard);
        if (score > bestScore) {
            bestScore = score;
            bestMove = possibleMoves[i];
        }
    }

    playerBoard->doMove(bestMove, mySide);

    // simple random move implementation to be taken out later
    // while (!validMoveFound) {
    //     moveX = rand() % 8;
    //     moveY = rand() % 8;
    //     m->setX(moveX);
    //     m->setY(moveY);
    //     validMoveFound = playerBoard->checkMove(m, mySide);
    // }
    // playerBoard->doMove(m, mySide);

    return bestMove;
}

int Player::heuristic(Board* board) {
    int score = board->count(mySide) - board->count(otherSide(mySide));

    return score;
}

Side Player::otherSide(Side side) {
    if (side == WHITE) {
        return BLACK;
    } else {
        return WHITE;
    }
}

vector<Move*> Player::getPossibleMoves(Board *board) {
    vector<Move*> possMoves;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            Move* testMove = new Move(x, y);
            if (board->checkMove(testMove, mySide)) {
                possMoves.push_back(testMove);
            }
        }
    }
    return possMoves;
}

