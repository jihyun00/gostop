#include "card.h"

#ifndef _PLAYER_H_
#define _PLAYER_H_

#define MAX_NUMBER_OF_PLAYER    3
#define INITIAL_MONEY   100000
#define NOT_PLAY    0 // play 한 적 없음
#define PLAYED      1 // play 한 적 있음

typedef enum _game_turn {
    // 게임 차례 체크
    GAME_TURN_NOT_NOW,
    GAME_TURN_NOW

} game_turn;

typedef struct _player {
    int score; // player 점수
    int played;// 이전에 play했는지 체크
    int money; // player가 갖고 있는 돈
    int turn;
    struct _card holding_card; // 갖고 있는 패
    struct _card eating_card; // 먹은 패

} player;

player players[MAX_NUMBER_OF_PLAYER];

#endif
