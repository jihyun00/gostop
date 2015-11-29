#include "player.h"

void setPlayerInfo() {
    // 게임 시작하기 전에 player 정보 setting
    int i;
    for(i=0; i<3; ++i) {
        players[i].score = 0;
        players[i].played = 0;
        players[i].money = 100000;
        players[i].turn = GAME_TURN_NOT_NOW;

		players[i].id = i;

        initializeRule(i);
    }

    players[0].turn = GAME_TURN_NOW; 

    cardInitialize();
}


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

