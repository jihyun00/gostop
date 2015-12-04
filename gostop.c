#include "card.h"
#include "player.h"
#include "status.h"

#include <stdio.h>

int main(void) {
    int i;
    setPlayerInfo();// 게임 시작하기 전에 player 정보 setting

    while(1) {
        drawScreen();// status 변할 때마다 화면에 값 그려주기

        for(i=0; i < MAX_NUMBER_OF_PLAYER; ++i) {
            setScore(i);
        }

        setGo();
        setTurn(); 

        isNagari();
    }

    return 0;
}
