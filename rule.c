#include "rule.h"
#include "player.h"
#include "status.h"

#include <string.h>

//rules 구조체 초기화
void initializeRule(int index) {
    players[index].rules = (rule *)malloc(sizeof(rule)); 
    players[index].rules->shake = 0;
    players[index].rules->sulsa = 0;
    players[index].rules->clear_board = 0;
    players[index].rules->chongtong = 0;
    players[index].rules->go = 0;
    players[index].rules->nagari = 0;
    players[index].rules->gobak = 0;
}

//흔들기
void setShake(int index) {
	card *head = NULL;
	int c = 1;
    int prev;

    head = players[index].holding_card;
    prev = head->data/4;
    while(head->next != NULL) {
        if(prev == head->next->data/4) {
            c++;

        } else {
            c = 1;
        }

        if(c==3){
            players[index].rules->shake += 1;

            break;
        }

        prev = head->next->data/4;
        head = head->next;
    }
}


void setSulsa() {
    int turn = getTurn();

    players[turn].rules->sulsa = players[turn].rules->sulsa + 1;
    if(players[turn].rules->sulsa==3){
        players[turn].history=3;
        gameEnd();
    }
}


int getSulsa() {
    int i;
    for(i=0; i < MAX_NUMBER_OF_PLAYER; ++i) {
        if(players[i].rules->sulsa == 1) {
            return i;
        }
    }
    return -1;
}


// 판 쓰리 체크
int isClearBoard() {
    if(getCardSize(blanketCard) == 1 && blanketCard->data == -1) {
        setClearBoard();

        return 1;
    }

    return 0;
}


void setClearBoard(){
    int i;
    int turn = getTurn();

    players[turn].rules->clear_board = 1;

    getPi(turn);
}


void setChongtong(int index) {
	card *head = NULL;
	int c = 1;
    int prev;
    int turn=getTurn();
	head = players[index].holding_card;
    prev = head->data/4;
    while(head->next != NULL) {
        if(prev == head->next->data/4) {
            c++;

        } else {
            c = 1;
        }

        if(c==4){
            players[index].rules->chongtong += 1;
            players[turn].history=3;
            gameEnd();
            break;
        }
        prev = head->next->data/4;
        head = head->next;
    }    
}


void isNagari() {
    int i, j;
    int cnt;
    int turn = getTurn();
    int num_of_go = 0;

	if((dummyCard->data == -1) && (getCardSize(dummyCard) == 1)) {
        // 아무도 3점 이상 내지 못했을 경우
		if((getScore(0) < 3) && (getScore(1) < 3) && (getScore(2) < 3)) {
            nagari = 1;
            printf("이번 판은 나가리~\n");

            gameEnd();
		}
    
        // 고를 했으나 추가 점수가 나지 않고 상대도 3점 이상을 획득하지 못한 경우
        for(i=0; i < MAX_NUMBER_OF_PLAYER; ++i) {
            cnt = 0;
            num_of_go = players[i].rules->go;

            if(players[i].score < players[i].addtional_score + 1) {
                for(j=0; j < MAX_NUMBER_OF_PLAYER; ++j) {
                    if(i == j) {
                        continue;
                    }

                    if(getScore(j) < 3) {
                        cnt++;
                    }
                }

                if(cnt == 2) {
                    nagari = 1;

                    printf("이번 판은 나가리~\n");

                    gameEnd();
                }
            }
        }

        players[turn].history=4;
        gameEnd();
	}
}


void getPi(int turn) {
    int i;

    card *head = NULL;
    
    for(i=0; i < MAX_NUMBER_OF_PLAYER; ++i) {
        if(i == turn) {
            continue;
        }

        while(head != NULL) {
            if((head->data%4 == 2) || (head->data%4 == 3) || (gusip == 0 && head->data == 28)) {
                if(head->data != 46) {
                    cardInsert(players[turn].eating_card, head->data);
                    cardDelete(players[i].eating_card, head->data);
                    
                    break;
                }
            }

            head = head->next;
        }
    }
}


int setGo(){ 
    int turn = getTurn();
    char status[10];

    if(players[turn].rules->go == 0) { // 고를 한 번도 한 적이 없을 때
        if(players[turn].score < 3){ // 3점 이하는 out
            return 0; 
        }
    }
    else { // 고를 한 번 이상했을 때
        if(players[turn].addtional_score < 2) {  // 2점 이상 추가로 못 냈을 때는 out
            return 0;
        }
    }
    printf("%d 플레이어가 %d 점수를 얻었습니다!\n",turn,getScore(turn));
    printf("Go하시겠습니까? Stop하시겠습니까? (g, s)"); 

    scanf("%s", status);

    if((strcmp(status, "go") == 0) || (strcmp(status, "g") == 0)) {
        players[turn].rules->go += 1;
        players[turn].score += 1;
        players[turn].addtional_score = players[turn].score; 
        players[turn].gobak = 1;
        players[(turn+1)%3].gobak= 0;
        players[(turn+2)%3].gobak= 0;
        return players[turn].rules->go;
    } else {
	printf("STOP 했습니다\n");
        /*if(isGobak()) {
            players[turn].history=1;
            gameEnd();
        }
        else setStop();*/
    }
    return 0;
}


void setStop() {
    int turn=getTurn();
    printf("STOP 합니다, 게임을 종료합니다.\n");

    players[turn].winner=1;

    players[turn].history=0;
    gameEnd(); 
}


/*int isGobak(){
    int turn = getTurn();
    int other1, other2;
    if(players[turn].score > 3){
        switch(turn){
            case 1 : {other1=2; other2=3; break;}
            case 2 : {other1=1; other2=3; break;}
            case 3 : {other1=1; other2=2; break;}
        }
        if(!(players[other1].rules->go)&&!(players[other2].rules->go)){
            players[other1].rules->gobak += 1;
            players[other2].rules->gobak += 1;
            return 1;
        }
        else if(!(players[other1].rules->go)||!(players[other2].rules->go)){
            if(!(players[other1].rules->go)){
                players[other1].rules->gobak += 1;
            }
            if(!(players[other2].rules->go)){
                players[other2].rules->gobak += 1;
            }
            return 1; 
        }
        else return 0;
    }
    else return 0;
}*/


void gameEnd() {
    int i;
    char name[5]={'A','B','C'};
    player* tmp= NULL;
    tmp = setWinner();
    
    int winner = tmp->id;
    printf("게임 종료되었습니다. 승자는 %c\n", name[winner]);
    printf("-------게이머의 잔고---------\n");
    for(i=0;i<3;i++){
        setMoney(i);
    }
    for(i=0;i<3;i++){
        printf("%c의 잔고 : %d 원\n", name[i], getMoney(i));
    }

    exit(0);
}
