#include "card.h"
#include "player.h"
#include "status.h"

#include <stdio.h>

int main(void) {
    int i;
    setPlayerInfo();

    while(1) {
        drawScreen();

        for(i=0; i < MAX_NUMBER_OF_PLAYER; ++i) {
            setScore(i);
        }

        setTurn(); 
        setGo();

        isNagari();
    }

    return 0;
}
