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


typedef struct _game_status {
    int score; // 현재 이기고 있는 사람의 점수
    // TODO: 깔린 패 정보

} game_status;

int gusip;

void setScore(player *playerId);
int getScore(player *playerId);
void setMoney(player *playerId);
int getMoney(player *playerId);
player* setWinner();
void setPlayerInfo();
void setTurn();
int getTurn();
void drawScreen(); // status 변할 때마다 화면에 값 그려주기
                   // 플레이어 차례, 점수, 갖고 있는 패 등 그려주기
void drawInterface(char *command); // 사용자 인터페이스 처리
void save();

#endif
