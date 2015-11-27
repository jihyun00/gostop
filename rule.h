#ifndef _RULE_H_
#define _RULE_H_
#include "player.h"
#include "status.h"

typedef struct _rule{
    unsigned short shake;
    unsigned short sulsa;
    unsigned short clear_board;
    unsigned short congtong;
    unsigned short go;
    unsigned short nagari;
} rule;

rule rules[MAX_NUMBER_OF_PLAYER];

void setrule(rule *rules);
void setShake(player *players, rule *rules, int i);
void setSulsa(player *players, card *blanketCard, rule *rules, int i);
void setClear_board(card *blanketCard, rule *rules, int i);
void setGo(player *players, rule *rules, int i);
void setChongtong(player *players, rule *rules, int i);
void setNagari(card *dummyCard, player *players, rule *rules, int i);


#endif
