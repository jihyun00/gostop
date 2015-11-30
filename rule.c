#include "rule.h"
#include "player.h"

#include <string.h>

void initializeRule(int index) {
    players[index].rules = (rule *)malloc(sizeof(rule)); 

    players[index].rules->shake = 0;
    players[index].rules->sulsa = 0;
    players[index].rules->clear_board = 0;
    players[index].rules->chongtong = 0;
    players[index].rules->go = 0;
    players[index].rules->nagari = 0;
}


void setShake(int index) {
	card *head = NULL;
	int j;
	int c;
    int turn = getTurn();
		
	for(j=0; j<12; j++){ // player가 든 패만큼 반복문 반복  
		c = 0;
		head = players[index].holding_card;
    	if(head != NULL) {
    		if((head->data/4)==j){ 
				c++;
			}

	        head = head->next;
	    }
		
		if(c==3){
            players[index].rules->shake += 1;

            break;
		}
	}
}


void setSulsa() {
    int turn = getTurn();

    players[turn].rules->sulsa = players[turn].rules->sulsa + 1;
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
    if(getCardSize(blanketCard) == 0) {
        return 1;
    }

    return 0;
}


void setClearBoard(){
    int i;
    int turn = getTurn();

	if(blanketCard == NULL) {
        players[turn].rules->clear_board = 1;
	}
	else {
        players[turn].rules->clear_board = 0;
	}

    getPi(turn);
}


void setGo(){ 
    int turn = getTurn();
    char status[10];

    if(players[turn].rules->go == 0) { // 고를 한 번도 한 적이 없을 때
        if(players[turn].score < 3){ // 3점 이하는 out
            return; 
        }

    } else { // 고를 한 번 이상했을 때
        if(players[turn].score < players[turn].addtional_score + 2) {  // 2점 이상 추가로 못 냈을 때는 out
            return;
        }
    }

    printf("Go하시겠습니까? Stop하시겠습니까?"); 

    scanf("%s", status);

    if((strcmp(status, "go") == 0) || (strcmp(status, "g") == 0)) {
        players[turn].rules->go += 1;
        players[turn].score += 1;
        players[turn].addtional_score = players[turn].score;
        
    } else if((strcmp(status, "stop") == 0) || (strcmp(status, "s") == 0)) {
        setStop();

    } else {
        // TODO: Error Handling
        printf("Invalid command\n");
    }
}


// TODO: setStop 구현, 이전 정보 필요한 것들 존재
void setStop() {
    printf("STOP 합니다, 게임을 종료합니다.\n");

    exit(0);
}


void setChongtong(int index) {
	card *head = NULL;
	int j,k;
	int c;
	for(j=0;j<12;j++){ // player가 든 패만큼 반복문 반복 
		c=0;
		head = players[index].holding_card;
    	if(head != NULL) {
    		if((head->data/4)==j){
				c++;
			}

	        head = head->next;
	    }
		if(c==4) break;
	}

    players[index].rules->chongtong = j;
}


// TODO: 나가리 구현
int isNagari() {
    // 아무도 3점 이상을 내지 못한 경우 나가리라고 한다. 누가 고를 했으나 추가 점수가 나지 않고 상대도 3점 이상을 획득 하지 못한 경우도 나가리에 속한다. 나가리가 되면 그 다음 판은 2배(*2)가 된다.( 돈계산.)
    int i, j;
    int turn = getTurn();
    int num_of_go = 0;
	if(dummyCard == NULL) {
        // 아무도 3점 이상 내지 못했을 경우
		if((players[0].score < 3) && (players[1].score < 3) && (players[2].score < 3)) {
            return 1;
		}
    
        // 고를 했으나 추가 점수가 나지 않고 상대도 3점 이상을 획득하지 못한 경우
        for(i=0; i < MAX_NUMBER_OF_PLAYER; ++i) {
            int cnt = 0;

            num_of_go = players[i].rules->go;
        }
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


int isGobak(int turn) {


}
