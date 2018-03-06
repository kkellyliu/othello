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
    //cerr << "hello" << endl;
    bool validMoveFound = false;
    int moveX;
    int moveY;
    Move *m = new Move(0, 0);

    playerBoard->doMove(opponentsMove, otherSide(mySide));

    //cerr << "performed other" << endl;
    Move *bestMove = nullptr;
    int minMax = -99999;


    vector<Move*> possibleMoves1 = getPossibleMoves(playerBoard, mySide);
    //cerr << "possible moves fine " << endl;
    for (unsigned int i = 0; i < possibleMoves1.size(); i++) 
        {
        //cerr << "move1 " << possibleMoves1[i]->x << " " << possibleMoves1[i]->y << endl;
        Board *tempBoard1 = playerBoard->copy();
        tempBoard1->doMove(possibleMoves1[i], mySide);
        vector<Move*> possibleMoves2 = getPossibleMoves(tempBoard1, otherSide(mySide));
        vector<int> ScoreTracker;

        for (unsigned int j = 0; j < possibleMoves2.size(); j++)
        {
            //cerr << "move2 " << possibleMoves2[j]->x << " " << possibleMoves2[j]->y << endl;
            Board *tempBoard2 = tempBoard1->copy();
            tempBoard2->doMove(possibleMoves2[j], otherSide(mySide));
            int score = heuristic(tempBoard2);
            ScoreTracker.push_back(score);
        }

        if (ScoreTracker.size() != 0)
        {
            int min = *min_element(ScoreTracker.begin(), ScoreTracker.end()); 
            if (min > minMax) {
                minMax = min;
                bestMove = possibleMoves1[i];
            }
        }
        else
        {
            int min = heuristic(tempBoard1);
            if (min > minMax) {
                minMax = min;
                bestMove = possibleMoves1[i];
            }
        }
    }


    // Beats SimplePlayer
    // vector<Move*> possibleMoves = getPossibleMoves(playerBoard, mySide);
    // Move *bestMove = nullptr;
    // int bestScore = -99999;
    // for (unsigned int i = 0; i < possibleMoves.size(); i++) {
    //     Board *tempBoard = playerBoard->copy();
    //     tempBoard->doMove(possibleMoves[i], mySide);
    //     int score = heuristic(tempBoard);
    //     if (score > bestScore) {
    //         bestScore = score;
    //         bestMove = possibleMoves[i];
    //     }
    // }

    




    // simple random move implementation to be taken out later
    // while (!validMoveFound) {
    //     moveX = rand() % 8;
    //     moveY = rand() % 8;
    //     m->setX(moveX);
    //     m->setY(moveY);
    //     validMoveFound = playerBoard->checkMove(m, mySide);
    // }
    // playerBoard->doMove(m, mySide);

    playerBoard->doMove(bestMove, mySide);

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

// Retrieves all possible moves for specified side 
vector<Move*> Player::getPossibleMoves(Board *board, Side side) {
    vector<Move*> possMoves;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            Move* testMove = new Move(x, y);
            if (board->checkMove(testMove, side)) {
                possMoves.push_back(testMove);
            }
        }
    }
    //cerr << "got possible moves" << endl;
    return possMoves;
}

