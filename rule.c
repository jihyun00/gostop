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

    for(i=0; i < MAX_NUMBER_OF_PLAYER; ++i) {
        if(i == turn) {
            continue;

        } else {
            // 피 가져오기
        }
    }

    // TODO: 다른 사람한테 피 한 개씩 받아와야 됨
}


// TODO: 피 가져오는 거 함수로 만들기


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


void givecard(player *players, int i){// TODO:
	//cardInsert
	switch(i){
		case 0 : {

				break;
		}
		case 1 : {

				break;
		}
		case 2 : {

				break;
		}
	}
	
}


/*
void piInsert(card *players, int data){
	card *head = players[i].eating_card;
	cardInsert(head, data);
}


int piDelete(card *card_list, int data) {  //;a;...
	card *head = players[i].eating_card;
    card *prev = NULL;

    while(head != NULL) {
        if(head->data == data) {
            prev->next = head->next;
            head->next = head;
            return data;
            
        } else {
            prev = head;
            head = head->next;
            return head;
        }
    }
}


// TODO
void thadak(player *players, card *dummyCard, int data,  int i){//이번에 플레이어가 낸 카드와, 더미카드가 일치하면 따닥
//card *eating_card;먹은
	card *head = dummyCard;

	if(data==(dummyCard->data)){
		givecard(players,i);
	}
	//일치 if()
}


// TODO:
void doublepae(player *players, int i){//먹은 패 중 쌍피만 존재하면 + 피 뭐줄지
	int data;
	card *head = players;

	while(head!=NULL){

	}
	for(int j=0;j<=sizeof(card))
	if(card *eating_card->data)
}


void getSulsa(player *players, card *blanketCard, rule *rules, int i){
	if(setSulsa(players, blanketCard, rule, i)){
		givecard(player, i);
	}
}*/
