#ifndef _RULE_H_
#define _RULE_H_

typedef struct _rule{
    int shake;
    int sulsa;
    int clear_board;
    int chongtong;
    int go;
    int nagari;

} rule;

void initializeRule(int index);
int isShake();
void setShake();
int isSulsa();
void setSulsa();
int isClearBoard();
void setClearBoard();
void setGo();
int isChongtong();
void setChongtong();
void setNagari();
//void givecard(player *players, int i);
//void thadak(player *players, card *dummyCard, int i);
//void doublepae(player *players, player *players, int i);
//void getSulsa(player *players, card *blanketCard, rule *rules, int i);

#endif
