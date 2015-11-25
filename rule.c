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
    		if(((int)players[i].holding_card/4)==j){
				c++;
			}
	        head = head->next;
	    }
		
		if(c==3) break;
	}
	rules[i].shake+=1;
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
	for(j=0;j<12;j++){ // plyaer가 든 패만큼 반복문 반복  
		c=0;
		head = players[i].holding_card;
    	if(head != NULL) {
    		if(((int)players[i].holding_card/4)==j){
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


void setSulsa(player *players, card *blanketCard, rule *rules, int i){
	card *head = NULL, *head2=NULL;
	int j,k;
	int c;
	for(j=0;j<12;j++){ // plyaer가 든 패+더미 중 큰 애만큼 반복
		c=0;
		head = players[i].holding_card;
    	if(head != NULL) {
    		if(((int)players[i].holding_card/4)==j){
				c++;
			}
			head = head->next;
		}
		if(head2 !=NULL){
			if(((int)(blanketCard[j].data)/4)==j){
				c++;
			}
			head2 = head2->next;
	    }	
		if(c==3){
			break;
		} 
	}
	rules[i].sulsa=(int)rules[i].sulsa+1;
}
