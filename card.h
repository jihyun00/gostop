#ifndef _CARD_H_
#define _CARD_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define CardMAX 48

typedef struct _card{
    int data;
    struct _card *next;
} card;

card *dummyCard; // 화투 더미
card *blanketCard; // 깔린 패

// 든 패, 먹은 패, 화투 더미, 깔린 패
const char cardMatrix[CardMAX][10];

void cardInitialize();
void divideCard(card *card_list, card *players_card);
void cardShuffle(card *card_list);
void orderCard(card *card_list);
card *getCard(card *card_list, int data);
int selectCard(card *card_list);
void cardInsert(card *card_list, int data);
void cardDelete(card *card_list, int data);
int getCardSize(card *card_list);
int getSame(card *card_list, int data);
void putCard(int num);

#endif
