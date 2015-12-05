#include "card.h"
#include "player.h"
#include "status.h"

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

// player 구조체에 점수 세팅
void setScore(int playerId) {
	int tmp_score = 0;
	
	P_C_S return_tmp; // P_C_S형 임시변수를 선언해서 나중에, 피와 오와 십과 광 값을, 필요에 의해 리턴 받음. 

	int i = 0;
    int j = 0;

	int gwang = 0, bigwang = 0, pi = 0, ssangpi = 0,     
		oh = 0, chodan = 0, hongdan = 0, chungdan = 0,
		sip = 0, gukjin = 0, godori = 0;

    card eating; //임시로 먹은 패의 초기 값을 가리킬 card형 구조체 선언.
    eating.next = players[playerId].eating_card;

	for(i=0 ; eating.next->next != NULL ; i++) {  //내가 먹은 패가 어떤건지 조건들로 알아봄.
	    if((((eating.next->next->data)%4 == 2) || ((eating.next->next->data)%4 == 3)) && (((eating.next->next->data) != 46) && ((eating.next->next->data) != 47))) {
			pi++;
        }
        
		if(((eating.next->next->data) == 41) || ((eating.next->next->data) == 47)) {
		    ssangpi++;
        }

		if(((eating.next->next->data) == 0) || ((eating.next->next->data) == 8) || ((eating.next->next->data)==28) || ((eating.next->next->data)==40)) {
			gwang++;
        }

		if((eating.next->next->data) == 44){
			gwang++, bigwang++;}


		if((((eating.next->next->data)%4 == 1) && (((eating.next->next->data) != 29) && ((eating.next->next->data)!=41) && ((eating.next->next->data) != 45))) ||(eating.next->next->data == 46)) {
		    oh++;
        }

		if(((eating.next->next->data) == 1) || ((eating.next->next->data) == 5) || ((eating.next->next->data)==9)) {
			hongdan++;
        }

		if(((eating.next->next->data) == 13) || ((eating.next->next->data) == 17) || ((eating.next->next->data) == 23)) {
			chodan++;
        }

		if(((eating.next->next->data) == 21) || ((eating.next->next->data) == 33) || ((eating.next->next->data)==37)) {
			chungdan++;
        }

        // 구십(32)가 십으로 쓰일 때
		if(((eating.next->next->data) == 4) || ((eating.next->next->data) == 12) || ((eating.next->next->data) == 16) || ((eating.next->next->data) == 20) || ((eating.next->next->data) == 24) || ((eating.next->next->data) == 29) || ((eating.next->next->data) == 36) || ((eating.next->next->data) == 45) || (((eating.next->next->data) == 32) && gusip == 1)) {
			sip++;
        } 

		if(((eating.next->next->data) == 4) || ((eating.next->next->data) == 12)|| ((eating.next->next->data) == 33)) {
			godori++;
        }

        // 구십(32)가 피로 쓰였을 때
		if((eating.next->next->data) == 32) {
			pi=pi+2;
        } 

	    eating.next = eating.next->next;
    }

	if(ssangpi == 1) { // 쌍피이면 피에 +2
		pi = pi+2;
    }
    
	if(ssangpi == 2) {
		pi = pi+4;
    }

	if(pi >= 10) {  // 피가 10장이상이면 +1
		tmp_score = tmp_score + pi-9;
    }

	if(gwang == 3) {           // 여기서부터 광점수 컨트롤 부분.
		tmp_score = tmp_score + 3;
	}

	if((gwang == 3) && (bigwang ==1)) {
	    tmp_score = tmp_score - 1;
    }

	if(gwang == 4) {
		tmp_score = tmp_score + 1;
    }

	if((gwang == 4) && (bigwang == 1)) {
		tmp_score = tmp_score + 1;
    }

	if(gwang == 5) {
		tmp_score = tmp_score + 11;   // 광이 5개이면 15점.
    }

	if(oh >= 5) {
		tmp_score = tmp_score + oh-4; // 오가 5장이상이면 1점씩 추가
    }

	if(hongdan == 3) {
		tmp_score = tmp_score + 3;  // 홍단의 경우.
    }

	if(chodan == 3) {
		tmp_score = tmp_score + 3;  // 초단의 경우.
    }

	if(chungdan == 3) {
		tmp_score = tmp_score + 3;  //청단의 경우
    }

	if(sip >= 5) {
		tmp_score = tmp_score + sip-4; // 십이 5장 이상이면 1점씩 추가
    }

	if(godori == 3) {
		tmp_score = tmp_score + 5;  //고도리일 경우 5점 추가.
    }

    if((players[playerId].rules->chongtong)==1) { // 총통일 경우 3점 추가.
        tmp_score = tmp_score+3;}

    
    tmp_score = tmp_score + (players[playerId].rules->go); // go 했을 경우 +1점. (이 부분을 안하면 턴 넘어가면서 -1점이 됨.)
    

    if((players[playerId].rules->go)==3) { // 3고할경우 점수 *2
        tmp_score = tmp_score*2;
    }
    
    if((players[playerId].rules->go)==4) { 
        tmp_score = tmp_score*4;
    }

    if((players[playerId].rules->go)==5) {
        tmp_score = tmp_score*8;
    }

    players[playerId].score = tmp_score; // 플레이어 구조체에 점수 셋팅

    return_tmp.pi = pi;
    return_tmp.oh = oh;
    return_tmp.sip = sip;
    return_tmp.gwang = gwang;
    PlayerStat[playerId]=return_tmp;  //전역 변수 playerStat에 pi, oh, sip, gwang의 개수 리턴. 
}


int getScore(int playerId) {  //점수 리턴하는 함수
    int score;

    score = players[playerId].score;
    
    return score;
}


void setMoney(int playerId ) {  // 잔고계산하는 함수.
	int i= 0;
	int j =0;
    int k = 0;
    int g = 0;
    int other = 0;  // 여러 임시변수들.

	player* tmp=NULL;  // 이심변수 구조체.

	tmp = (player*)malloc(sizeof(player)); // 임시변수 동적메모리 할당. 

	tmp = setWinner(); //이긴사람 구조체 임시변수에 받기.
	
	int gwang = 0, bigwang = 0, pi = 0, ssangpi = 0, 
		oh = 0, chodan = 0, hongdan = 0, chungdan = 0,
		sip = 0, gukjin = 0, godori = 0;


    if((tmp->id)!=playerId) { // 플레이어가 승자인지 패자인지 결정.
        j++;
    }

    
    if((PlayerStat[(tmp->id)].pi > 10) && (PlayerStat[playerId].pi < 7)) {  //피박인지 확인
        j=j*2;
    }				


    if((PlayerStat[(tmp->id)].gwang > 3) && (PlayerStat[playerId].gwang < 1)) { // 광박인지 확인
       j=j*2;
    }

    if(PlayerStat[(tmp->id)].sip > 7) { // 멍텅구리인지 확인
        j=j*2;
    }

    k = nagari;

    if(k == 1) { // 나가리 인지 확인.
        j=j*2;
    }

    if((players[(tmp->id)].rules->shake)==1) { // 흔들었는지 확인
        j=j*2;
    }
    if((players[(tmp->id)].rules->shake)==2) {
        j=j*4;
    } // 두번흔들었느지 확인

    if(playerId != (tmp->id)){ // 이긴사람이 고박이면 안되므로, 그 부분 확인.
    if((players[playerId].gobak) == 1){  // 고박인지 확인. 
        other = 3 - ((tmp->id)+playerId);

        g = 1;

        if((PlayerStat[(tmp->id)].pi > 10) && (PlayerStat[other].pi < 7)) {
            g=g*2;
        }				

        if((PlayerStat[(tmp->id)].gwang > 3) && (PlayerStat[other].gwang < 1)) {
           g=g*2;
        }

        if(PlayerStat[(tmp->id)].sip > 7) {
            g=g*2;
        }

        if(k == 1) {
            g=g*2;
        }

        if((players[(tmp->id)].rules->shake)==1) {
            g=g*2;
        }
        if((players[(tmp->id)].rules->shake)==2) {
            g=g*4;
        }
        
        players[playerId].money = players[playerId].money - (tmp->score)*100*g;  // 고박일경우, 돈을 차감.
        players[other].money = players[other].money + (tmp->score)*100*g;  // 차감한 돈을 제 3자에게 줌.
    }
    }

    tmp->money = (tmp->money) + (tmp->score)*100*j;  // 승자에게 돈을 줌.
    players[playerId].money = players[playerId].money - (tmp->score)*100*j; // 나의 돈을 차감. 
}



int getMoney(int playerId) { //돈 리턴하는 함수.
    int money;

	money = players[playerId].money;

    return money;
}


player* setWinner(){  // 이긴사람의 player형 구조체를 리턴하는 함수. 스톱할 때 player[i].winner에 표시해둔 값에 따라 비교를 통해 승자 결정.
    if(players[0].winner== 1)
        return &players[0];
    if(players[1].winner== 1)
        return &players[1];
    if(players[2].winner== 1)
        return &players[2];
    else return NULL;
}


void drawScreen() {
    // status 변할 때마다 화면에 값 그려주기
    // 플레이어 차례, 점수, 갖고 있는 패 등
    char command[256];

    system("clear");

    card *head = NULL;

    if(getTurn() == 0) {
        printf("*");
    }
    if(players[0].rules->shake > 0) {
        printf("(흔듦)");    
    }
    printf("A   : 패) ");
    head = players[0].holding_card;
    while(head != NULL) {
        if(head->data == -1) {
            break;
        }
        printf("%s ", cardMatrix[head->data]);
        head = head->next;
    }
    printf("\n");
    printf("(점수: %d) 딴 화투) ", getScore(0));
    head = players[0].eating_card;
    while(head != NULL) {
        if(head->data == -1) {
            break;
        }
        printf("%s ", cardMatrix[head->data]);
        head = head->next;
    }
    printf("\n");

    if(getTurn() == 1) {
        printf("*");
    }
    if(players[1].rules->shake > 0) {
        printf("(흔듦)");    
    }
    printf("B   : 패) ");
    head = players[1].holding_card;
    while(head != NULL) {
        if(head->data == -1) {
            break;
        }
        printf("%s ", cardMatrix[head->data]);
        head = head->next;
    }
    printf("\n");
    printf("(점수: %d) 딴 화투) ", getScore(1));
    head = players[1].eating_card;
    while(head != NULL) {
        if(head->data == -1) {
            break;
        }
        printf("%s ", cardMatrix[head->data]);
        head = head->next;
    }
    printf("\n");

    if(getTurn() == 2) {
        printf("*");
    }
    if(players[2].rules->shake > 0) {
        printf("(흔듦)");    
    }
    printf("C   : 패) ");
    head = players[2].holding_card;
    while(head != NULL) {
        if(head->data == -1) {
            break;
        }
        printf("%s ", cardMatrix[head->data]);
        head = head->next;
    }
    printf("\n");
    printf("(점수: %d) 딴 화투) ", getScore(2));
    head = players[2].eating_card;
    while(head != NULL) {
        if(head->data == -1) {
            break;
        }
        printf("%s ", cardMatrix[head->data]);
        head = head->next;
    }
    printf("\n");

    printf("깔린 패) ");
    head = blanketCard;
    while(head != NULL) {
        if(head->data == -1) {
            break;
        }
        printf("%s ", cardMatrix[head->data]);
        head = head->next;
    }
    printf("\n\n");
    printf("명령 : ");
    scanf("%s", command);
    drawInterface(command);
}


void onlydrawScreen() {
    char command[256];

    system("clear");

    card *head = NULL;
    if(getTurn() == 0) {
        printf("*");
    }
    if(players[0].rules->shake > 0) {
        printf("(흔듦)");    
    }
    printf("A   : 패) ");
    head = players[0].holding_card;
    while(head != NULL) {
        if(head->data == -1) {
            break;
        }
        printf("%s ", cardMatrix[head->data]);
        head = head->next;
    }
    printf("\n");
    printf("(점수: %d) 딴 화투) ", getScore(0));
    head = players[0].eating_card;
    while(head != NULL) {
        if(head->data == -1) {
            break;
        }
        printf("%s ", cardMatrix[head->data]);
        head = head->next;
    }
    printf("\n");

    if(getTurn() == 1) {
        printf("*");
    }
    if(players[1].rules->shake > 0) {
        printf("(흔듦)");    
    }
    printf("B   : 패) ");
    head = players[1].holding_card;
    while(head != NULL) {
        if(head->data == -1) {
            break;
        }
        printf("%s ", cardMatrix[head->data]);
        head = head->next;
    }
    printf("\n");
    printf("(점수: %d) 딴 화투) ", getScore(1));
    head = players[1].eating_card;
    while(head != NULL) {
        if(head->data == -1) {
            break;
        }
        printf("%s ", cardMatrix[head->data]);
        head = head->next;
    }
    printf("\n");

    if(getTurn() == 2) {
        printf("*");
    }
    if(players[2].rules->shake > 0) {
        printf("(흔듦)");    
    }
    printf("C   : 패) ");
    head = players[2].holding_card;
    while(head != NULL) {
        if(head->data == -1) {
            break;
        }
        printf("%s ", cardMatrix[head->data]);
        head = head->next;
    }
    printf("\n");
    printf("(점수: %d) 딴 화투) ", getScore(2));
    head = players[2].eating_card;
    while(head != NULL) {
        if(head->data == -1) {
            break;
        }
        printf("%s ", cardMatrix[head->data]);
        head = head->next;
    }
    printf("\n");
    printf("깔린 패) ");
    card* tmpblanket = blanketCard;
    int cnt=0;
    while(blanketCard != NULL) {
        if(blanketCard->data == -1) {
            break;
        }
        int n = blanketCard->data;
        printf("%s ", cardMatrix[n]);
        blanketCard = blanketCard->next;
    }
    blanketCard = tmpblanket;
}


void drawInterface(char *command) { // interface를 그려주는 함수
    // 숫자일 경우
    if(isdigit(command[0])) {
        int num;
        int turn = getTurn();
        char id[3] = {'A', 'B', 'C'};

        num = atoi(command);

        while(1) {
            if(num == 9) {
                break;
            }

            if(getCardSize(players[turn].holding_card) < num) {
                printf("갖고 있는 카드 수에서 벗어나는 값입니다.\n"); 
                printf("다시 입력해주세요.\n"); 
                printf("명령 : "); 
                scanf("%d", &num);

            } else {
                break;
            }
        }

        putCard(num);
        printf("%c번째 턴이고, %d 번째 카드를 선택하셨습니다\n", id[turn], num);
        
    } else { // 문자일 경우
        getCommand(command);

        printf("명령 : "); 
        scanf("%s", command);
        drawInterface(command);
    }
}


void save() { // dummyCard, blanketCard, player 정보 등을 파일에 저장
    FILE *fp;
    card *head = NULL;
    int exist = -1;

    // 파일이 존재하는지 체크, 존재할 경우 파일 삭제 후 다시 생성
    exist = access("save.txt", F_OK);
    if(exist == 0) {
        unlink("save.txt");
    }

    fp = fopen("save.txt", "w");

    if(fp == NULL) {
        fprintf(stderr, "파일 open을 실패하였습니다.\n");

        return;
    }


    head = dummyCard;

    // dummyCard 정보 저장
    fprintf(fp, "dummyCard :");
    while(head != NULL) {
        fprintf(fp, " %2d", head->data); 

        head = head->next;
    }
    fprintf(fp, "\n");
    
    head = blanketCard;

    // blanketCard 정보 저장
    fprintf(fp, "blanketCard :");
    while(head != NULL) {
        fprintf(fp, " %2d", head->data); 

        head = head->next;
    }
    fprintf(fp, "\n");

    // gusip 정보 저장
    fprintf(fp, "gusip : %d\n", gusip);
    // nagari 정보 저장
    fprintf(fp, "nagari : %d\n", nagari);

    // player들 정보 저장
    fprintf(fp, "player1 id : %d\n", players[0].id);    
    fprintf(fp, "player1 score : %d\n", players[0].score); 
    fprintf(fp, "player1 money : %d\n", players[0].money);    
    fprintf(fp, "player1 turn : %d\n", players[0].turn);    
    
    head = players[0].holding_card;

    fprintf(fp, "player1 holding card : ");
    while(head != NULL) {
        fprintf(fp, "%2d ", head->data);
        head = head->next;
    }
    fprintf(fp, "\n");

    head = players[0].eating_card;

    fprintf(fp, "player1 eating card : ");
    while(head != NULL) {
        fprintf(fp, "%2d ", head->data);
        head = head->next;
    }
    fprintf(fp, "\n");
    fprintf(fp, "player1 rule : ");
    fprintf(fp, "%d %d %d %d %d %d", players[0].rules->shake,
                                     players[0].rules->sulsa,
                                     players[0].rules->clear_board,
                                     players[0].rules->chongtong,
                                     players[0].rules->go,
                                     players[0].rules->nagari);
    fprintf(fp, "\n");
    fprintf(fp, "player2 id : %d\n", players[1].id);    
    fprintf(fp, "player2 score : %d\n", players[1].score); 
    fprintf(fp, "player2 money : %d\n", players[1].money);    
    fprintf(fp, "player2 turn : %d\n", players[1].turn);    
    head = players[1].holding_card;

    fprintf(fp, "player2 holding card : ");
    while(head != NULL) {
        fprintf(fp, "%2d ", head->data);
        head = head->next;
    }
    fprintf(fp, "\n");
    head = players[1].eating_card;
    fprintf(fp, "player2 eating card : ");
    while(head != NULL) {
        fprintf(fp, "%2d ", head->data);
        head = head->next;
    }
    fprintf(fp, "\n");
    fprintf(fp, "player2 rule : ");
    fprintf(fp, "%d %d %d %d %d %d", players[1].rules->shake,
                                     players[1].rules->sulsa,
                                     players[1].rules->clear_board,
                                     players[1].rules->chongtong,
                                     players[1].rules->go,
                                     players[1].rules->nagari);
    fprintf(fp, "\n");
    fprintf(fp, "player3 id : %d\n", players[2].id);    
    fprintf(fp, "player3 score : %d\n", players[2].score); 
    fprintf(fp, "player3 money : %d\n", players[2].money);    
    fprintf(fp, "player3 turn : %d\n", players[2].turn);    
    
    head = players[2].holding_card;

    fprintf(fp, "player3 holding card : ");
    while(head != NULL) {
        fprintf(fp, "%2d ", head->data);

        head = head->next;
    }
    fprintf(fp, "\n");

    head = players[2].eating_card;

    fprintf(fp, "player3 eating card : ");
    while(head != NULL) {
        fprintf(fp, "%2d ", head->data);

        head = head->next;
    }
    fprintf(fp, "\n");
    fprintf(fp, "player3 rule : ");
    fprintf(fp, "%d %d %d %d %d %d", players[2].rules->shake,
                                     players[2].rules->sulsa,
                                     players[2].rules->clear_board,
                                     players[2].rules->chongtong,
                                     players[2].rules->go,
                                     players[2].rules->nagari);
    fprintf(fp, "\n");
    fclose(fp);
}

void load() {        // save.txt 파일내용을 한줄씩 읽기
    setPlayerInfo();
    setTurn();
    FILE *fp;
    fp = fopen("save.txt", "r");
	rewind(fp);
    char line[512];
    card *dummy = (card *)malloc(sizeof(card)*CardMAX); 
    card *blanket = (card *)malloc(sizeof(card)*CardMAX); 
    card *head = (card *)malloc(sizeof(card)*CardMAX); 	
    card *headah = (card *)malloc(sizeof(card)*CardMAX);
    card *headae = (card *)malloc(sizeof(card)*CardMAX);
    card *headbh = (card *)malloc(sizeof(card)*CardMAX); 
    card *headbe = (card *)malloc(sizeof(card)*CardMAX);
    card *headch = (card *)malloc(sizeof(card)*CardMAX); 
    card *headce = (card *)malloc(sizeof(card)*CardMAX);

    int i = 0;
    int j;

    if(fp == NULL) {
        fprintf(stderr, "파일 open을 실패하였습니다.\n");
        return;
    }
    while(fgets(line, 512, fp) != NULL) {          // 화투패 더미 읽기
        if(strstr(line, "dummyCard :")) {
            while(line[11+3*i] != '\n') { 
                sscanf(line+11+i*3," %2d", &dummy[i].data);
				i++;
            }
            dummy[i-1].next=NULL;
            for(j=0; j < i-1; ++j) {
                dummy[j].next = &dummy[j+1];
            }
            dummyCard = &dummy[0];
            i = 0;
        }

        if(strstr(line, "blanketCard :")) {	  // 깔린 패 읽기
            while(line[13+3*i] != '\n') {
                sscanf(line+13+3*i, " %2d", &blanket[i].data);
                i++;
            }
	    
	        blanket[i-1].next=NULL;
            for(j=0; j < i-1; ++j) {
                blanket[j].next = &blanket[j+1];
            }

            blanketCard = &blanket[0];
            i = 0;
        }
        if(strstr(line, "gusip :")) {
            sscanf(line, "gusip : %d", &gusip);
        }
	    if(strstr(line, "nagari :")) {
            sscanf(line, "nagari : %d", &nagari);
        }
        if(strstr(line, "player1 id :")) {
            sscanf(line, "player1 id : %d", &players[0].id);
        }
        if(strstr(line, "player1 score :")) {
            sscanf(line, "player1 score : %d", &players[0].score);
        }
        if(strstr(line, "player1 money :")) {
            sscanf(line, "player1 money : %d", &players[0].money);
        }
        if(strstr(line, "player1 turn :")) {
            sscanf(line, "player1 turn : %d", &players[0].turn);

        }								// A의 info 읽기

        if(strstr(line, "player1 holding card :")) {			// A의 가지고 있는 패읽기

        }
        if(strstr(line, "player1 holding card :")) {

            while(line[23+3*i] != '\n') {
                sscanf(line+23+3*i, " %2d", &headah[i].data);
                i++;
            }
	        headah[i-1].next=NULL;
            for(j=0; j < i-1; ++j) {
                headah[j].next = &headah[j+1];
            }

            players[0].holding_card = &headah[0];
            i = 0;
        }
        
        if(strstr(line, "player1 eating card :")) {			// A가 먹은 패읽기
            while(line[22+3*i] != '\n'){
                sscanf(line+22+3*i, " %2d", &headae[i].data);
                i++;
            }
	        headae[i-1].next=NULL;
            for(j=0; j < i-1; ++j) {
                headae[j].next = &headae[j+1];
            }

            players[0].eating_card = &headae[0];
            i = 0;
        }
        if(strstr(line, "player1 rule :")) {				// A의 룰 읽기
            sscanf(line, "player1 rule : %d %d %d %d %d %d", &players[0].rules->shake, 
                                                             &players[0].rules->sulsa, 
                                                             &players[0].rules->clear_board,
                                                             &players[0].rules->chongtong,
                                                             &players[0].rules->go,
                                                             &players[0].rules->nagari);
        }
        if(strstr(line, "player2 id :")) {
            sscanf(line, "player2 id : %d", &players[1].id);
        }
        if(strstr(line, "player2 score :")) {
            sscanf(line, "player2 score : %d", &players[1].score);
        }
        if(strstr(line, "player2 money :")) {
            sscanf(line, "player2 money : %d", &players[1].money);
        }
        if(strstr(line, "player2 turn :")) {
            sscanf(line, "player2 turn : %d", &players[1].turn);
        }						 		//B 정보 읽기
	
        if(strstr(line, "player2 holding card :")) {			//B 지니고 있는 패읽기
            while(line[23+3*i] != '\n') {
                sscanf(line+23+3*i, " %2d", &headbh[i].data);
                i++;
            }
	        headbh[i-1].next=NULL;
            for(j=0; j < i-1; ++j) {
                headbh[j].next = &headbh[j+1];
            }
            players[1].holding_card = &headbh[0];
            i = 0;
        }

        if(strstr(line, "player2 eating card :")) {			//B 먹은패 읽기
            while(line[22+3*i] != '\n'){
                sscanf(line+22+3*i, " %2d", &headbe[i].data);
				i++;
            }
	        headbe[i-1].next=NULL;
            for(j=0; j < i-1; ++j) {
                headbe[j].next = &headbe[j+1];
            }

            players[1].eating_card = &headbe[0];
            i = 0;
        }
        if(strstr(line, "player2 rule :")) {				//B의 룰 읽기
            sscanf(line, "player2 rule : %d %d %d %d %d %d", &players[1].rules->shake, 
                                                             &players[1].rules->sulsa, 
                                                             &players[1].rules->clear_board,
                                                             &players[1].rules->chongtong,
                                                             &players[1].rules->go,
                                                             &players[1].rules->nagari);
        }
        if(strstr(line, "player3 id :")) {
            sscanf(line, "player3 id : %d", &players[2].id);
        }
        if(strstr(line, "player3 score :")) {
            sscanf(line, "player3 score : %d", &players[2].score);
        }
        if(strstr(line, "player3 money :")) {
            sscanf(line, "player3 money : %d", &players[2].money);
        }
        if(strstr(line, "player3 turn :")) {
            sscanf(line, "player3 turn : %d", &players[2].turn);
        }								//C 정보 읽기

        if(strstr(line, "player3 holding card :")) {			//C 지니고 있는 패 읽기
            while(line[23+3*i] != '\n'){
                sscanf(line+23+3*i, " %2d", &headch[i].data);
				i++;
            }
	        headch[i-1].next=NULL;
            for(j=0; j < i-1; ++j) {
                headch[j].next = &headch[j+1];
            }

            players[2].holding_card = &headch[0];
            i = 0;
        }

        if(strstr(line, "player3 eating card :")) {			//C 먹은 패 읽기
            while(line[22+3*i] != '\n'){
                sscanf(line+22+3*i, " %2d", &headce[i].data);
				i++;
            }
	        headce[i-1].next=NULL;
            for(j=0; j < i-1; ++j) {
                headce[j].next = &headce[j+1];
            }
            players[2].eating_card = &headce[0];
        }
        if(strstr(line, "player3 rule :")) {				// C의 룰 읽기
            sscanf(line, "player3 rule : %d %d %d %d %d %d", &players[2].rules->shake, 
                                                             &players[2].rules->sulsa, 
                                                             &players[2].rules->clear_board,
                                                             &players[2].rules->chongtong,
                                                             &players[2].rules->go,
                                                             &players[2].rules->nagari);
        }
    }
    fclose(fp);
}


void getCommand(char *command) { // 문자로 입력받은 명령어 정보 리턴
    if((strcmp(command, "e") == 0) || (strcmp(command, "exit") == 0)) {
            printf("게임을 종료합니다\n");
            exit(0);

    } else if((strcmp(command, "b") == 0) || (strcmp(command, "balance") == 0)) {
            printf("-------게이머의 잔고---------\n");
            printf("A의 잔고 : %d 원\n", getMoney(0));
            printf("B의 잔고 : %d 원\n", getMoney(1));
            printf("C의 잔고 : %d 원\n", getMoney(2));

    } else if((strcmp(command, "h") == 0) || (strcmp(command, "help") == 0)) { 
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

    } else if(strcmp(command, "save") == 0) {
            printf("게임을 저장합니다.\n");
            save();
    } else if(strcmp(command, "load") == 0) {
        printf("게임을 로드합니다.\n");
        load();
        onlydrawScreen();
        printf("\n\n");
    } else {
        printf("유효하지 않은 명령어입니다.\n");
    }
}


void initializedPCS() {
    int i;

    for(i=0; i < MAX_NUMBER_OF_PLAYER; ++i) {
        PlayerStat[i].oh = 0;
        PlayerStat[i].sip = 0;
        PlayerStat[i].pi = 0;
        PlayerStat[i].gwang = 0;
    }
}
