#ifndef _RULE_H_
#define _RULE_H_

typedef struct _rule{
    unsigned short shake;
    unsigned short sulsa;
    unsigned short clear_board;
    unsigned short chongtong;
    unsigned short go;
    unsigned short nagari;
} rule;

void setrule();
void setShake();
void setClear_board();
void setGo();
void setChongtong();
void setNagari();
void setSulsa();
//void givecard(player *players, int i);
//void thadak(player *players, card *dummyCard, int i);
//void doublepae(player *players, player *players, int i);
//void getSulsa(player *players, card *blanketCard, rule *rules, int i);

#endif
