#include "status.h"

#include <stdio.h>

void setScore(player playerId) {



	player* tmp;

	int i = 0;

	int gwang = 0, bigwang = 0, pi = 0, ssangpi = 0, 
		oh = 0, chodan = 0, hongdan = 0, chungdan = 0,
		sip = 0, gukjin = 0, godori = 0;

	for(i=0 ; playerId->eating_card[i]->next != NULL ; i++){
		if(((playerId->eating_card[i]->data)%4 == (2||3))
			&& ((playerId->eating_card[i]->data) != (46||47))){
			pi++;}
		if((playerId->eating_card[i]->data) == (41||47)){
			ssangpi++;}


		if((playerId->eating_card[i]->data) == (0||8||32||40)){
			gwang++;}
		if((playerId->eating_card[i]->data) == 44){
			gwang++, bigwang++;}


		if(((playerId->eating_card[i]->data)%4 == 1)
			&& ((playerId->eating_card[i]->data) != (29||41||45))
			&&(playerId->eating_card[i]->data == 46)){
			oh++;}
		if((playerId->eating_card[i]->data) == (1||5||9)){
			hongdan++;}
		if((playerId->eating_card[i]->data) == (13||17||23)){
			chodan++;}
		if((playerId->eating_card[i]->data) == (21||33||37)){
			chungdan++;}


		if((playerId->eating_card[i]->data) == (4||12||16||20||24
			||29||36||45)){
			sip++;}
		if((playerId->eating_card[i]->data) == (4||12||33)){
			godori++;}


		if((playerId->eating_card[i]->data) == 32){
			gukjin++;}
	}
	if(ssangpi == 1){
		pi = pi+2}
	if(ssangpi == 2){
		pi = pi+4}
	if(gukjin == 1){
		pi = pi+2} // 국진을 대비해서.
	if( pi >= 10){
		tmp->score = tmp->score + pi-9}


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
	if(hongdan=3){
		tmp->score = tmp->score + 3;}
	if(chodan=3){
		tmp->score = tmp->score + 3;}
	if(chungdan=3){
		tmp->score = tmp->score + 3;}


	if(sip >= ){
		tmp->score = tmp->score + sip-4;}
	if(godori=3){
		tmp->score = tmp->score + 5;}

	playerId->score = tmp->score;


	





}

		


    // player 구조체에 점수 세팅



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
