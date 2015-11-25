#include "status.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
// player 구조체에 점수 세팅
int gusip=0;
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
		     || ((head->eating_card->next->data)==28)||((head->eating_card->next->data)==40)){
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
			((head->eating_card->next->data)==45)||(((head->eating_card->next->data)==32)&&gusip==1)){
			sip++;} // 구십(32)가 십으로 쓰일 때
		if(((head->eating_card->next->data) == 4)||
				((head->eating_card->next->data)==12)||
				((head->eating_card->next->data)==33)){
			godori++;}


		if((head->eating_card->next->data) == 32){
<<<<<<< HEAD
			pi=pi+2;}   // 구십(32)가 피로 쓰였을때
=======
			pi = pi+2;}
>>>>>>> a0101b4182472f19142e0d8261a24eff4f8b7ca9
		head->eating_card->next = head->eating_card->next->next;
	}
	if(ssangpi == 1){
		pi = pi+2;}
	if(ssangpi == 2){
		pi = pi+4;}
	//if(gukjin == 1){
	//	pi = pi+2;} // 국진을 대비해서. (통합 과정에서 필요없어짐.)
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
        players[i].turn = GAME_TURN_NOT_NOW;

		players[i].id = i;
    }

    players[0].turn = GAME_TURN_NOW; 

    cardInitialize();
}


void setTurn() {
    int i;
    for(i=0; i < MAX_NUMBER_OF_PLAYER; ++i) {
        if(players[i].turn == GAME_TURN_NOW) {
            players[i].turn = GAME_TURN_NOT_NOW;
            players[(i+1) % MAX_NUMBER_OF_PLAYER].turn = GAME_TURN_NOW;
        }
    }
}


// player turn return
int getTurn() {
    int i;
    for(i=0; i < MAX_NUMBER_OF_PLAYER; ++i) {
        if(players[i].turn == GAME_TURN_NOW) {
            return i;
        }
    }

    return -1;
}


void drawScreen() {
    // status 변할 때마다 화면에 값 그려주기
    // 플레이어 차례, 점수, 갖고 있는 패 등
    char command[256];

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
    head = blanketCard;
    while(head != NULL) {
        printf("%s ", cardMatrix[head->data]);
        head = head->next;
    }
    printf("\n\n");
    printf("명령 : ");
    scanf("%s", command);

    drawInterface(command);
}


void drawInterface(char *command) {
    int num=-1;
   	int index,turn;
	card *eating=NULL;
	card *holding=NULL;
	card target;
	if(isdigit(command[0]))
	{if(command[0] == '9') num = 8;
	 else 
		num = 6;
	}
	else if(command[0] == 'g') num=1;			
	else if(command[0] == 's' && command[1] == 'a') num=9;
	else if(command[0] == 's' && command[1] != 'a') num=2;			
	else if(command[0] == 'e') num=3;			
	else if(command[0] == 'b') num=4;			
	else if(command[0] == 'h') num=5;			
	else if(command[0] == 'l') num=10;			
    // command로 받은 거 문자일 경우 숫자로 변환해주고,
    // switch - case 로 해당 동작 처리
				
    switch(num) {
        case 1:
		    system("clear");				

            printf("go 함수\n");
            // blah blah... 

            break;
		case 2: 
		    system("clear");				

            printf("stop 함수\n");
            
			break;
		case 3: 
            printf("게임을 종료합니다\n");
			exit(0);

			break;
		case 4: 
            printf("-------게이머의 잔고---------\n");
            printf("A의 잔고 : %d 원\n", getMoney(players));
            printf("B의 잔고 : %d 원\n", getMoney(players+1));
            printf("C의 잔고 : %d 원\n", getMoney(players+2));

			break;
		case 5: 
            printf("--------- 도움말 ------------\n");
            printf("1. g(o) : 고 (자기 turn에 점수가 났고 3점이상");
            printf("2. s(top) : 스톱(자기 turn에 점수가 났고 3점 이상일 떄, 이번 판을 끝냄\n");
            printf("3.e(xit) : exit 프로그램 끝내기\n");
            printf("4. b(alance) : 게이머의 잔고 보기\n");
            printf("5. h(elp) : 각 키에 대한 설명 보기\n");
            printf("6. 1~7 : 낼 화투 선택\n");
            printf("7. 1~2 : 화투를 냈는데 깔린 화투 중 무늬는 같지만 다른 것이 있을 때 선택\n");
            printf("8. 9 : 9 십을 피로 또는 십으로 이동(토글), 디폴트로는 피로 함, 각 판에서 한번만 할 수 있음\n");
            printf("9. save : 현재 상태를 파일에 저장(단, 확인 가능하도록 텍스트 형태로 저장해야함\n");
            printf("10. load : 파일에 저장된 상태를 읽어서 계속 게임 진행\n");

			break;
		case 6:
            index = command[0]-'0';
			turn = getTurn();
			printf("%d번쨰 턴이고, %d 번째 카드를 선택하셨습니다\n",turn,index);
            holding = players[turn].holding_card;
            eating = players[turn].eating_card;
            target = holding[index];
            if(getSame(blanketCard,target.data)!=0)
            {
				if(getSame(blanketCard,target.data)>1) // 7번 구현
				{
					printf("1,2번쨰 중 어느것을 선택하시겠습니까?");
					int same=0;
					scanf("%d",&same);
					if(same==1)
					{
						cardInsert(eating,target.data);
						cardDelete(holding,target.data);
                		cardDelete(blanketCard,target.data);
					}
					else if(same==2)
					{
					cardInsert(eating,getSecondCard(blanketCard,target.data)->data);
					cardDelete(holding,target.data);
          			cardDelete(dummyCard,getSecondCard(blanketCard,target.data)->data);
					}
					else
					printf("잘못된 선택입니다");
				 	}
                cardInsert(eating,target.data);
                cardDelete(holding,target.data);
                cardDelete(blanketCard,target.data);
        	    }
				break;
	case 8: printf("9십을 십으로 이동합니다(default : 십->피)\n");
			if(getCard(eating,32)!=NULL && gusip==0)
			gusip=1;
			break;
	case 9: save();
			break;	
		

    }
}

void save()
{	
	card *blank = blanketCard;
	FILE *ofp1;
	ofp1 = fopen("blank.txt","w");
	while(blank!=NULL)
{
	fprintf(ofp1,"%d ",blank->data);
	blank = blank -> next;
}

	FILE *ofp20; // 플레이어0 의 정보
	ofp20 = fopen("player0.txt","w");
	fprintf(ofp20,"%d %d %d %d %d %p %p",players[0].id, players[0].score,players[0].played,players[0].money,players[0].turn);	
	
	FILE *ofp21,*ofp22;
	card *aeat,*ahold;
	ofp21 = fopen("player0eat.txt","w");
	aeat = players[0].eating_card;
	while(aeat != NULL)
	{
	fprintf(ofp21,"%d ",aeat->data);
	aeat = aeat -> next;
	}
	
	ofp22 = fopen("player0hold.txt","w");
	ahold = players[0].holding_card;
	while(ahold != NULL)
	{
	fprintf(ofp21,"%d ",ahold->data);
	ahold = ahold -> next;
	}
	
	FILE *ofp30; // 플레이어1 의 정보
	ofp30 = fopen("player1.txt","w");
	fprintf(ofp30,"%d %d %d %d %d %p %p",players[1].id, players[1].score,players[1].played,players[1].money,players[1].turn);	
	
	FILE *ofp31,*ofp32;
	card *beat,*bhold;
	ofp31 = fopen("player1eat.txt","w");
	beat = players[1].eating_card;
	while(beat != NULL)
	{
	fprintf(ofp31,"%d ",beat->data);
	beat = beat -> next;
	}
	
	ofp32 = fopen("player1hold.txt","w");
	bhold = players[1].holding_card;
	while(bhold != NULL)
	{
	fprintf(ofp31,"%d ",bhold->data);
	bhold = bhold -> next;
	}

	FILE *ofp40; // 플레이어2 의 정보
	ofp40 = fopen("player2.txt","w");
	fprintf(ofp40,"%d %d %d %d %d %p %p",players[2].id, players[2].score,players[2].played,players[2].money,players[2].turn);	
	
	FILE *ofp41,*ofp42;
	card *ceat,*chold;
	ofp41 = fopen("player2eat.txt","w");
	ceat = players[2].eating_card;
	while(ceat != NULL)
	{
	fprintf(ofp41,"%d ",ceat->data);
	ceat = ceat -> next;
	}
	
	ofp42 = fopen("player2hold.txt","w");
	chold = players[2].holding_card;
	while(chold != NULL)
	{
	fprintf(ofp41,"%d ",chold->data);
	chold = chold -> next;
	}
}
	



