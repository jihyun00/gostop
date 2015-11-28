#include "player.h"

void setTurn() {
    int i;
    for(i=0; i < MAX_NUMBER_OF_PLAYER; ++i) {
        if(players[i].turn == GAME_TURN_NOW) {
            players[i].turn = GAME_TURN_NOT_NOW;
            players[(i+1) % MAX_NUMBER_OF_PLAYER].turn = GAME_TURN_NOW;
        }
    }
}


// player turn return
int getTurn() {
    int i;
    for(i=0; i < MAX_NUMBER_OF_PLAYER; ++i) {
        if(players[i].turn == GAME_TURN_NOW) {
            return i;
        }
    }

    return -1;
}

