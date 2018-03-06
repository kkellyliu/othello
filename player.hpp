#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    Board *playerBoard;
    Side mySide;


    Move *doMove(Move *opponentsMove, int msLeft);
    int heuristic(Board* board);
    Side otherSide(Side side);
    vector<Move*> getPossibleMoves(Board* board, Side side);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
