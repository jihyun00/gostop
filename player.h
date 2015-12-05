#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "card.h"
#include "rule.h"

#define MAX_NUMBER_OF_PLAYER    3 // 최대 player수 
#define INITIAL_MONEY   100000
#define NOT_PLAY    0 // play 한 적 없음
#define PLAYED      1 // play 한 적 있음

typedef enum _game_turn {
    // 게임 차례 체크 
    GAME_TURN_NOT_NOW,
    GAME_TURN_NOW

} game_turn;

typedef struct _player {
	int id;// player number
    int score; // player 점수
    int additional_score; // 고했을 경우 추가점수
    int money; // player가 갖고 있는 돈
    int turn; // turn인지 아닌지 check
    int history; // 그 전 함수 history 
    int gobak; // gobak인지 아닌지 check
    int winner; // 누가 위너인지 아닌지
    card *holding_card; // 갖고 있는 패
    card *eating_card; // 먹은 패
    rule *rules;

} player;

player players[MAX_NUMBER_OF_PLAYER]; // player 구조체 배열을 player 수 만큼 선언 

void setPlayerInfo();// 게임 시작하기 전에 player 정보 setting
int getTurn();//턴 리턴해주는 함수 
void setTurn();// 턴 설정해주는 함수
void setWinnerTurn(int turn); // 이전에 이긴 사람이 먼저 시작하게 설정

#endif
