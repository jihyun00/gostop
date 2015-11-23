#include "card.h"
#include "player.h"
#include "status.h"

#include <stdio.h>

int main(void) {
    setPlayerInfo();

    while(1) {
        drawScreen();
    }

    return 0;
}
