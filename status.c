#include "status.h"

#include <stdio.h>

// player 구조체에 점수 세팅
void setScore(player *playerId) {
	player* tmp = NULL;

	tmp = (player*)malloc(sizeof(player));

	int i = 0;

	int gwang = 0, bigwang = 0, pi = 0, ssangpi = 0, 
		oh = 0, chodan = 0, hongdan = 0, chungdan = 0,
		sip = 0, gukjin = 0, godori = 0;

	player * head = NULL;
	head = (player*)malloc(sizeof(player));

	head = playerId;

	for(i=0 ; head->eating_card->next != NULL ; i++){
		if((((head->eating_card->next->data)%4 == 2)||((head->eating_card->next->data)%4 == 3))
			&& (((head->eating_card->next->data) != 46)||((head->eating_card->next->data) != 47))){
			pi++;}
		if(((head->eating_card->next->data) == 41)||((head->eating_card->next->data) == 47)){
			ssangpi++;}


		if(((head->eating_card->next->data) == 0)||((head->eating_card->next->data)==8)
		     || ((head->eating_card->next->data)==32)||((head->eating_card->next->data)==40)){
			gwang++;}
		if((head->eating_card->next->data) == 44){
			gwang++, bigwang++;}


		if((((head->eating_card->next->data)%4 == 1)
			&& (((head->eating_card->next->data) != 29)||((head->eating_card->next->data)!=41)
			|| ((head->eating_card->next->data) != 45)))
			||(head->eating_card->next->data == 46)){
			oh++;}
		if(((head->eating_card->next->data) == 1)||((head->eating_card->next->data)==5)||
				((head->eating_card->next->data)==9)){
			hongdan++;}
		if(((head->eating_card->next->data) == 13)||((head->eating_card->next->data)==17)||
				((head->eating_card->next->data)==23)){
			chodan++;}
		if(((head->eating_card->next->data) == 21)||((head->eating_card->next->data)==33)||
					((head->eating_card->next->data)==37)){
			chungdan++;}


		if(((head->eating_card->next->data) == 4)||
		((head->eating_card->next->data)==12)||
		((head->eating_card->next->data)==16)||
		 ((head->eating_card->next->data)==20)||
		  ((head->eating_card->next->data)==24)||
			((head->eating_card->next->data)==29)||
			((head->eating_card->next->data)==36)||
			((head->eating_card->next->data)==45)){
			sip++;}
		if(((head->eating_card->next->data) == 4)||
				((head->eating_card->next->data)==12)||
				((head->eating_card->next->data)==33)){
			godori++;}


		if((head->eating_card->next->data) == 32){
			gukjin++;}
		head->eating_card->next = head->eating_card->next->next;
	}
	if(ssangpi == 1){
		pi = pi+2;}
	if(ssangpi == 2){
		pi = pi+4;}
	if(gukjin == 1){
		pi = pi+2;} // 국진을 대비해서.
	if( pi >= 10){
		tmp->score = tmp->score + pi-9;}


	if(gwang == 3){
		tmp->score = tmp->score + 3;
	}
	if((gwang == 3) &&(bigwang ==1 ))
	{
		tmp->score = tmp->score -1;}
	if(gwang == 4){
		tmp->score = tmp->score +1 ;}
	if((gwang == 4) &&(bigwang ==1))
	{
		tmp->score = tmp->score +1;}
	if(gwang ==5){
		tmp->score = tmp->score +11;}

	if(oh >= 5){
		tmp->score = tmp->score + oh-4;}
	if(hongdan ==3){
		tmp->score = tmp->score + 3;}
	if(chodan==3){
		tmp->score = tmp->score + 3;}
	if(chungdan==3){
		tmp->score = tmp->score + 3;}

	if(sip >= 5){
		tmp->score = tmp->score + sip-4;}
	if(godori==3){
		tmp->score = tmp->score + 5;}

	playerId->score = tmp->score;
}


int getScore(player *playerId) {
    int score;

	score = playerId->score; 
    
    return score;
}


void setMoney(player *playerId) {
	int i= 0;

	player* tmp=NULL;

	tmp = (player*)malloc(sizeof(player));

	tmp = setWinner();
	
	int gwang = 0, bigwang = 0, pi = 0, ssangpi = 0, 
		oh = 0, chodan = 0, hongdan = 0, chungdan = 0,
		sip = 0, gukjin = 0, godori = 0;

	player* head = NULL;
	head = (player*)malloc(sizeof(player));
	head = playerId;

	for(i=0 ; head->eating_card->next != NULL ; i++){
		if((((head->eating_card->next->data)%4 == 2)||((head->eating_card->next->data)%4 == 3))
			&& (((head->eating_card->next->data) != 46)||((head->eating_card->next->data) != 47))){
			pi++;}
		if(((head->eating_card->next->data) == 41)||((head->eating_card->next->data) == 47)){
			pi =pi+2;}
		head->eating_card->next = head->eating_card->next->next;}

// 피박(해결)  고박(진사람들 쪽을 조사해야함)- (4,5번할때) 
// 쓰리고, 포고, 흔들기, 멍텅구리(이와같은 것을 하고 이 긴사람 점수를 두배해주는 식으로 해결하면 됨)- (4,5번 할때)
											   
	if(playerId->id == tmp->id)
	{
		playerId->money = INITIAL_MONEY + (tmp->score)*100*2;
	}
	else{
	if(pi<7){
		playerId->money = INITIAL_MONEY - (tmp->score)*100*2;       //피박문제 해결한줄. 
		tmp->money = (tmp->money) + (tmp->score)*100;}				//피박문제 해결한줄.
	else
		playerId->money = INITIAL_MONEY - (tmp->score)*100;
	}
}


// player 구조체에 돈 세팅 
int getMoney(player *playerId) {
    int money;

	money = playerId->money;

    return money;
}


player* setWinner(){
    if((players[0].score > players[1].score) && (players[0].score > players[2].score)) {
        return &players[0]; 
        
    } else if((players[1].score > players[0].score) && (players[1].score > players[2].score)) {
        return &players[1];

    } else {
        return &players[2];
    }
}


void setPlayerInfo() {
    // 게임 시작하기 전에 player 정보 setting
    int i;
    for(i=0; i<3; ++i) {
        players[i].score = 0;
        players[i].played = 0;
        players[i].money = 100000;
        players[i].turn = 0;

		players[i].id = i;
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
        printf("%s ", cardMatrix[head->data]);
        head = head->next;
    }
    printf("\n");
    printf("(점수: %d) 딴 화투\n\n", players[0].score);

    printf("B   : 패) ");
    head = players[1].holding_card;
    while(head != NULL) {
        printf("%s ", cardMatrix[head->data]);
        head = head->next;
    }
    printf("\n");
    printf("(점수: %d) 딴 화투\n\n", players[1].score);

    printf("C   : 패) ");
    head = players[2].holding_card;
    while(head != NULL) {
        printf("%s ", cardMatrix[head->data]);
        head = head->next;
    }
    printf("\n");
    printf("(점수: %d) 딴 화투\n\n", players[2].score);

    printf("깔린 패) ");
    head = &blanketCard;
    while(head != NULL) {
        printf("%s ", cardMatrix[head->data]);
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
