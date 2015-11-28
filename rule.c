#include "rule.h"


void setrule(rule *rules){
	int i;
	for(i=0;i<MAX_NUMBER_OF_PLAYER;i++){
		rules[i].shake=0;
		rules[i].sulsa=0;
		rules[i].clear_board=0;
		rules[i].go=0;
		rules[i].nagari=0;
	}
}

void setShake(player *players, rule *rules, int i){
	card *head = NULL;
	int j,k;
	int c;
		
	for(j=0;j<12;j++){ // plyaer가 든 패만큼 반복문 반복  
		c=0;
		head = players[i].holding_card;
    	if(head != NULL) {
    		if((players[i].holding_card->data/4)==j){ 
				c++;
			}
	        head = head->next;
	    }
		
		if(c==3){
			rules[i].shake+=1;
			break;
		}
	}
	
}

void setClear_board(card *blanketCard, rule *rules, int i){
	if(blanketCard == NULL) {
		rules[i].clear_board=1;
	}
	else {
		rules[i].clear_board=0;
	}
}

void setGo(player *players, rule *rules, int i){
	if(players[i].score>=3){
		//if()플레이어가 고를 한다고 눌렀을 때 (키);를 조건문으로 두기;
		rules[i].go+=1;
	}
}

void setChongtong(player *players, rule *rules, int i){
	card *head = NULL;
	int j,k;
	int c;
	for(j=0;j<12;j++){ // player가 든 패만큼 반복문 반복 TODO: bug, 항상 player의 패가 12개라는 보장이 없음 
		c=0;
		head = players[i].holding_card;
    	if(head != NULL) {
    		if((players[i].holding_card->data/4)==j){
				c++;
			}
	        head = head->next;
	    }
		if(c==4) break;
	}
	rules[i].congtong=j;
}

void setNagari(card *dummyCard, player *players, rule *rules, int i){
	if(dummyCard==NULL){
		if((players[0].score<3)&&(players[1].score<3)&&(players[2].score<3)){
			rules[i].nagari=1;
		}
	}
}


void setSulsa(player *players, card *blanketCard, rule *rules, int i) {
	card *head = NULL, *head2=NULL;
	int j,k;
	int c;
	for(j=0;j<12;j++){ // plyaer가 든 패+더미 중 큰 애만큼 반복
        // TODO: line 58과 마찬가지 이유로 버그
		c=0;
		head = players[i].holding_card;
    	if(head != NULL) {
    		if((players[i].holding_card->data/4)==j){ 
				c++;
			}
			head = head->next;
		}
		if(head2 !=NULL){
			if(((int)(blanketCard[j].data)/4)==j){ // TODO: blanketCard 이렇게 접근 못함
				c++;
			}
			head2 = head2->next;
	    }	
		if(c==3){
			rules[i].sulsa=(int)rules[i].sulsa+1;
			break;
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


void thadak(player *players, card *dummyCard, int data,  int i){//이번에 플레이어가 낸 카드와, 더미카드가 일치하면 따닥
//card *eating_card;먹은
	card *head = dummyCard;

	if(data==(dummyCard->data)){
		givecard(players,i);
	}
	//일치 if()
}



void doublepae(player *players, int i){//먹은 패 중 쌍피만 존재하면 + 피 뭐줄지
	int data
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
}