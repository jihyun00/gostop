#ifndef _CARD_H_
#define _CARD_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define CardMAX 48 // 화투패 개수

typedef struct _card{ // 카드 자기참조구조체 
    int data;
    struct _card *next;
} card;

card *dummyCard; // 화투 더미
card *blanketCard; // 깔린 패

int gusip; // 9십을 십으로 쓸 것인지 피로 쓸 것인지 설정하는 변수 


const char cardMatrix[CardMAX][10]; // 카드 데이터를 이름으로 출력하기 위해 선언한 배열

void cardInitialize(); // 카드 동적 할당 및 player들에게 카드 할당
void divideCard(card *card_list, card *players_card);// shuffle한 카드 player들에게 나눠주기
void cardShuffle(card *card_list);// 카드 random 하게 섞기
void orderCard(card *card_list);// 카드를 번호순으로 정렬하기
card *getCard(card *card_list, int data);// 카드 정보 가져오기
int selectCard(card *card_list); // 카드리스트에서 맨 위에 있는 카드 뽑기
void cardInsert(card *card_list, int data);// 카드리스트에 카드 추가
void cardDelete(card *card_list, int data);// 카드 리스트로부터 카드 삭제
int getCardSize(card *card_list);// 가지고 있는 카드 갯수 리턴
int* getSame(card *card_list, int data, int *size);// 카드가 같은 달에 속하는지 체크
void putCard(int num);// 사용자가 카드를 내고, 카드를 뽑고, 카드를 먹는 과정
void toggle(); // 토글 기능 수행하는 함수

#endif
