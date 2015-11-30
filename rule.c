#include "rule.h"
#include "player.h"

void initializeRule(int index) {
    players[index].rules = (rule *)malloc(sizeof(rule)); 

    players[index].rules->shake = 0;
    players[index].rules->sulsa = 0;
    players[index].rules->clear_board = 0;
    players[index].rules->chongtong = 0;
    players[index].rules->go = 0;
    players[index].rules->nagari = 0;
}


void setShake() {
	card *head = NULL;
	int j,k;
	int c;
    int turn = getTurn();
		
	for(j=0; j<12; j++){ // player가 든 패만큼 반복문 반복  
		c = 0;
		head = players[turn].holding_card;
    	if(head != NULL) {
    		if((head->data/4)==j){ 
				c++;
			}

	        head = head->next;
	    }
		
		if(c==3){
            players[turn].rules->shake += 1;
			break;
		}
	}
}


void setSulsa() {
    int turn = getTurn();

    players[turn].rules->sulsa = players[turn].rules->sulsa + 1;
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


// TODO:
void setGo(){ 
    int turn = getTurn();

	if(players[turn].score>=3){
		//if()플레이어가 고를 한다고 눌렀을 때 (키);를 조건문으로 두기;
        players[turn].rules->go += 1;
	}
}


void setChongtong() {
	card *head = NULL;
	int j,k;
	int c;
    int turn = getTurn();
	for(j=0;j<12;j++){ // player가 든 패만큼 반복문 반복 
		c=0;
		head = players[turn].holding_card;
    	if(head != NULL) {
    		if((head->data/4)==j){
				c++;
			}

	        head = head->next;
	    }
		if(c==4) break;
	}

    players[turn].rules->chongtong = j;
}


void setNagari() {
    int turn = getTurn();

	if(dummyCard == NULL){
		if((players[0].score < 3) && (players[1].score < 3) && (players[2].score < 3)) {
            players[turn].rules->nagari = 1;
		}
	}
}


// TODO: 점수 변동있을 수 있으므로, 재계산 필요
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
