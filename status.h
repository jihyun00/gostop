#include "player.h"

#ifndef _STATUS_H_
#define _STATUS_H_

typedef enum _game_player_status {
    // 기본, 흔들기, 설사, 판쓰리, 총통 등 status 구조체

    GAME_PLAYER_STATUS_DEFAULT,
    GAME_PLAYER_STATUS_SHAKE,
    GAME_PLAYER_STATUS_SULSA,
    GAME_PLAYER_STATUS_CLEAR_BOARD,
    GAME_PLAYER_STATUS_GO,
    GAME_PLAYER_STATUS_CHONGTONG,
    GAME_PLAYER_STATUS_NAGARI

} game_player_status;

int nagari;

typedef struct _game_player_card_status {
	int oh;
	int sip;
	int pi;
	int gwang;
} P_C_S;

//P_C_S[MAX_NUMBER_OF_PLAYER];


void setScore(int playerId);
int getScore(int playerId);
void setMoney(int playerId, P_C_S );
int getMoney(int playerId);
player* setWinner();
void drawScreen(); // status 변할 때마다 화면에 값 그려주기
                   // 플레이어 차례, 점수, 갖고 있는 패 등 그려주기
void drawInterface(char *command); // 사용자 인터페이스 처리
void save();
void load();

#endif
