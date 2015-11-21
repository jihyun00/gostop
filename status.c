#include "status.h"

#include <stdio.h>

void setScore(player playerId) {
    // player 구조체에 점수 세팅
}


int getScore(player playerId) {
    int score;
    
    return score;
}


void setMoney(player playerId) {
    // player 구조체에 돈 세팅 
}


int getMoney(player playerId) {
    int money;

    return money;
}


void setPlayerInfo() {
    // 게임 시작하기 전에 player 정보 setting
    int i;
    for(i=0; i<3; ++i) {
        players[i].score = 0;
        players[i].played = 0;
        players[i].money = 100000;
        players[i].turn = 0;
    }

    cardInitialize();
}


void drawScreen() {
    // status 변할 때마다 화면에 값 그려주기
    // 플레이어 차례, 점수, 갖고 있는 패 등
    char command[256];

    system("clear");
    card *head = NULL;

    printf("A   : 패) ");
    head = players[0].holding_card;
    while(head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
    printf("(점수: %d) 딴 화투\n\n", players[0].score);

    printf("B   : 패) ");
    head = players[1].holding_card;
    while(head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
    printf("(점수: %d) 딴 화투\n\n", players[1].score);

    printf("C   : 패) ");
    head = players[2].holding_card;
    while(head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
    printf("(점수: %d) 딴 화투\n\n", players[2].score);

    printf("깔린 패) ");
    head = &blanketCard;
    while(head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n\n");
    printf("명령 : ");
    scanf("%s", command);
}


void drawInterface(char *command) {
    int num; 

    // command로 받은 거 문자일 경우 숫자로 변환해주고,
    // switch - case 로 해당 동작 처리

    switch(num) {
        case 0:
            // blah blah... 
            break;
    }
}
