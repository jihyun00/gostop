#ifndef _RULE_H_
#define _RULE_H_

typedef struct _rule{
    int shake;
    int sulsa;
    int clear_board;
    int chongtong;
    int go;
    int nagari;
    int gobak;
} rule;

void initializeRule(int index);
void setShake();
void setSulsa();
int getSulsa();
int isClearBoard();
void setClearBoard();
int setGo();
void setStop();
void setChongtong(int index);
void isNagari();
void getPi(int turn);
int isGobak();
void gameEnd();

#endif
