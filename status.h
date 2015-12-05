
#ifndef _STATUS_H_
#define _STATUS_H_

#include "player.h"

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

int nagari; // nagari인지 체크해주는 변수
int before_nagari; // 이전 판이 nagari였는지 체크해주는 변수

typedef struct _game_player_card_status {   // 피박 광박 멍텅구리등을 처리하기 위한 구조체. 
	int oh;
	int sip;
	int pi;
	int gwang;
} P_C_S;

P_C_S PlayerStat[MAX_NUMBER_OF_PLAYER]; // 구조체배열.


void setScore(int playerId);// player 구조체에 점수 세팅
int getScore(int playerId);
void setMoney(int playerId);// player 구조체에 돈 세팅 
int getMoney(int playerId);
player* setWinner();
void drawScreen(); // status 변할 때마다 화면에 값 그려주기
                   // 플레이어 차례, 점수, 갖고 있는 패 등 그려주기
void onlydrawScreen();
void drawInterface(char *command); // 사용자 인터페이스 처리
void save();// dummyCard, blanketCard, player 정보 등을 파일에 저장
void load(); // save.txt 파일내용을 한줄씩 읽기
void getCommand(char *command); // 문자로 입력받은 명령어 정보 리턴
void initializedPCS();

#endif
