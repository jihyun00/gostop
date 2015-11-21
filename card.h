#ifndef _CARD_H_
#define _CARD_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define CardMAX 48

typedef struct _card{
        int data;
        struct _card * next;
} card;

card dummyCard; // 화투 더미
card blanketCard; // 깔린 패

// 든 패, 먹은 패, 화투 더미, 깔린 패
/*const char cardMatrix[CardMAX][10] = {
    "1광","1오","1피","1피",
    "2십","2오","2피","2피",
    "3광","3오","3피","3피",
    "4십","4오","4피","4피",
    "5십","5오","5피", "5피",
    "6십","6오","6피","6피",
    "7십","7오","7피","7피",
    "8광","8십","8피","8피",
    "9십","9오","9피","9피",
    "10십","10오","10피","10피",
    "11광","11쌍피","11피","11피",
    "12광","12십","12띠","12쌍피" 
};*/


void cardInitialize();
void divideCard(card *card_list, card *players_card);
void cardShuffle(card *card_list);
void orderCard(card *card_list);
card *getCard(card *card_list, int data);
void cardInsert(card *card_list, int data);
void cardDelete(card *card_list, int data);

#endif
