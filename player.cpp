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

    // do the opponent's move
    playerBoard->doMove(opponentsMove, otherSide(mySide));


    // Minimax Implementation
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

    ////////////////////////////////////////////////////////////////////////////
    
    // Beats SimplePlayer
    // vector<Move*> possibleMoves = getPossibleMoves(playerBoard, mySide);
    // Move *bestMove = nullptr;
    // int bestScore = -99999;
    // for (unsigned int i = 0; i < possibleMoves.size(); i++) {

    //     // declar some variable
    //     Board *tempBoard = playerBoard->copy();
    //     Move *m = possibleMoves[i];
    //     tempBoard->doMove(m, mySide);
    //     int score = heuristic(tempBoard);

    //     // giving extra priority to the edges and corners
    //     bool xSide = m->getX() == 0 or m->getX() == 7;
    //     bool ySide = m->getY() == 0 or m->getY() == 7;
    //     if (xSide) {
    //         score = score + 7;
    //     }

    //     if (ySide) {
    //         score = score + 7;
    //     }

    //     if (ySide and xSide) {
    //         score = score + 20;
    //         cerr << score << endl;
    //     }

    //     // subtracting points for moves that give the opponent access to corners
    //     bool corners = (m->getX() == 1 or m->getX() == 6) and (m->getY() == 1 or m->getY() == 6);
    //     bool side1 = (m->getX() == 0 or m->getX() == 8) and (m->getY() == 1 or m->getY() == 6);
    //     bool side2 = (m->getX() == 1 or m->getX() == 6) and (m->getY() == 0 or m->getY() == 8);
        
    //     if (corners or side1 or side2) {
    //         score = score - 15;
    //     }

    //     // choosing the best move
    //     if (score > bestScore) {
    //         bestScore = score;
    //         bestMove = possibleMoves[i];
    //     }
    // }


    /////////////////////////////////////////////////////////////////////////////////
   
    // simple random move implementation 
    // declarations
    // int moveX;
    // int moveY;
    // Move *bestMove = new Move(0, 0);
    // bool validMoveFound = false;
    // // randomly find a valid move
    // while (!validMoveFound) {
    //     // get random moves and check if they're valid
    //     moveX = rand() % 8;
    //     moveY = rand() % 8;
    //     bestMove->setX(moveX);
    //     bestMove->setY(moveY);
    //     validMoveFound = playerBoard->checkMove(bestMove, mySide);
    // }

    // once best move has been determined, we do the move and return it 
    playerBoard->doMove(bestMove, mySide);

    return bestMove;
}


/* This function counds the difference between the scores given a certain board
 * Input:
 *      board: the board to calculate the score for 
 * Output:
 *      score: the score with positive being winning and negative being losing
 */
int Player::heuristic(Board* board) {
    int score = board->count(mySide) - board->count(otherSide(mySide));


    return score;
}


/* This function returns the color of the opposing side
 * Input: 
 *      side: the side the player currently is
 * Output: 
 *      the color of the opposing team
 */
Side Player::otherSide(Side side) {
    if (side == WHITE) {
        return BLACK;
    } else {
        return WHITE;
    }
}

/* This function retrieves all possible moves for a side given a board
 * Inputs:
 *      side: the side you want the moves for
 *      board: the game board
 * Outputs:
 *      possMoves: a vector containing all the possible moves
 */
vector<Move*> Player::getPossibleMoves(Board *board, Side side) {
    vector<Move*> possMoves;
    // iterate through the entire board and check for valid moves
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            Move* testMove = new Move(x, y);
            if (board->checkMove(testMove, side)) {
                // if valid add to vector
                possMoves.push_back(testMove);
            }
        }
    }
    return possMoves;
}

