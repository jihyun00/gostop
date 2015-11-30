#include "card.h"
#include "player.h"
#include "status.h"

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

// TODO: FIX
// player 구조체에 점수 세팅
void setScore(int playerId) {
	player* tmp = NULL;

	tmp = (player*)malloc(sizeof(player));
	tmp->score = 0;

	int i = 0;
    int j;

	int gwang = 0, bigwang = 0, pi = 0, ssangpi = 0, 
		oh = 0, chodan = 0, hongdan = 0, chungdan = 0,
		sip = 0, gukjin = 0, godori = 0;

    card *eating = NULL;

    eating = players[playerId].eating_card;

	for(i=0 ; eating->next != NULL ; i++) {
	    if((((eating->next->data)%4 == 2) || ((eating->next->data)%4 == 3)) && (((eating->next->data) != 46) || ((eating->next->data) != 47))) {
			pi++;
        }
        
		if(((eating->next->data) == 41) || ((eating->next->data) == 47)) {
		    ssangpi++;
        }

		if(((eating->next->data) == 0) || ((eating->next->data) == 8) || ((eating->next->data)==28) || ((eating->next->data)==40)) {
			gwang++;
        }

		if((eating->next->data) == 44){
			gwang++, bigwang++;}


		if((((eating->next->data)%4 == 1) && (((eating->next->data) != 29) || ((eating->next->data)!=41) || ((eating->next->data) != 45))) ||(eating->next->data == 46)) {
		    oh++;
        }

		if(((eating->next->data) == 1) || ((eating->next->data) == 5) || ((eating->next->data)==9)) {
			hongdan++;
        }

		if(((eating->next->data) == 13) || ((eating->next->data) == 17) || ((eating->next->data) == 23)) {
			chodan++;
        }

		if(((eating->next->data) == 21) || ((eating->next->data) == 33) || ((eating->next->data)==37)) {
			chungdan++;
        }

        // 구십(32)가 십으로 쓰일 때
		if(((eating->next->data) == 4) || ((eating->next->data) == 12) || ((eating->next->data) == 16) || ((eating->next->data) == 20) || ((eating->next->data) == 24) || ((eating->next->data) == 29) || ((eating->next->data) == 36) || ((eating->next->data) == 45) || (((eating->next->data) == 32) && gusip == 1)) {
			sip++;
        } 

		if(((eating->next->data) == 4) || ((eating->next->data) == 12)|| ((eating->next->data) == 33)) {
			godori++;
        }

        // 구십(32)가 피로 쓰였을 때
		if((eating->next->data) == 32) {
			pi=pi+2;
        } 

	    eating->next = eating->next->next;
    }

	if(ssangpi == 1) {
		pi = pi+2;
    }
    
	if(ssangpi == 2) {
		pi = pi+4;
    }

	if(pi >= 10) {
		tmp->score = tmp->score + pi-9;
    }

	if(gwang == 3) {
		tmp->score = tmp->score + 3;
	}

	if((gwang == 3) && (bigwang ==1)) {
	    tmp->score = tmp->score - 1;
    }

	if(gwang == 4) {
		tmp->score = tmp->score + 1;
    }

	if((gwang == 4) && (bigwang == 1)) {
		tmp->score = tmp->score + 1;
    }

	if(gwang == 5) {
		tmp->score = tmp->score + 11;
    }

	if(oh >= 5) {
		tmp->score = tmp->score + oh-4;
    }

	if(hongdan == 3) {
		tmp->score = tmp->score + 3;
    }

	if(chodan == 3) {
		tmp->score = tmp->score + 3;
    }

	if(chungdan == 3) {
		tmp->score = tmp->score + 3;
    }

	if(sip >= 5) {
		tmp->score = tmp->score + sip-4;
    }

	if(godori == 3) {
		tmp->score = tmp->score + 5;
    }

    players[playerId].score = tmp->score;
}


int getScore(int playerId) {
    int score;

    score = players[playerId].score;
    
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

	for(i=0 ; head->eating_card->next != NULL ; i++) {
		if((((head->eating_card->next->data)%4 == 2) || ((head->eating_card->next->data)%4 == 3)) && (((head->eating_card->next->data) != 46)||((head->eating_card->next->data) != 47))) {
			pi++;
        }

		if(((head->eating_card->next->data) == 41) || ((head->eating_card->next->data) == 47)) {
			pi =pi+2;
        }

		head->eating_card->next = head->eating_card->next->next;}

    //  TODO: 피박(해결)  고박(진사람들 쪽을 조사해야함)- (4,5번할때) 
    // 쓰리고, 포고, 흔들기, 멍텅구리(이와같은 것을 하고 이 긴사람 점수를 두배해주는 식으로 해결하면 됨)- (4,5번 할때)
											   
	if(playerId->id == tmp->id) {
		playerId->money = INITIAL_MONEY + (tmp->score)*100*2;
	} else {
        if(pi < 7) {
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
        printf("%s ", cardMatrix[head->data]);
        head = head->next;
    }
    printf("\n");
    printf("(점수: %d) 딴 화투) ", getScore(0));
    head = players[0].eating_card;
    while(head != NULL) {
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
        printf("%s ", cardMatrix[head->data]);
        head = head->next;
    }
    printf("\n");
    printf("(점수: %d) 딴 화투) ", getScore(1));
    head = players[1].eating_card;
    while(head != NULL) {
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
        printf("%s ", cardMatrix[head->data]);
        head = head->next;
    }
    printf("\n");
    printf("(점수: %d) 딴 화투) ", getScore(2));
    head = players[2].eating_card;
    while(head != NULL) {
        printf("%s ", cardMatrix[head->data]);
        head = head->next;
    }
    printf("\n");

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
    // 숫자일 경우
    if(isdigit(command[0])) {
        int num;
        int turn = getTurn();

        num = atoi(command);

        if(num < 10 && num > 0) {
            if(num == 9) {
                printf("9십을 십으로 이동합니다(default : 십->피)\n");

            } else {
                printf("%d번째 턴이고, %d 번째 카드를 선택하셨습니다\n", turn, num);
            }
                
            turn = getTurn();
            putCard(num);

        } else {
            // TODO: Error Hanlding
            printf("Invalid command\n");
        }
        
        
    } else { // 문자일 경우
        if((strcmp(command, "e") == 0) || (strcmp(command, "exit") == 0)) {
                printf("게임을 종료합니다\n");
                exit(0);

        } else if((strcmp(command, "b") == 0) || (strcmp(command, "balance") == 0)) {
                printf("-------게이머의 잔고---------\n");
                printf("A의 잔고 : %d 원\n", getMoney(players));
                printf("B의 잔고 : %d 원\n", getMoney(players+1));
                printf("C의 잔고 : %d 원\n", getMoney(players+2));

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

        } else {
            // TODO : Error Handling
            printf("Invalid command\n");
        }

    }
}


void save() {
    // player 구조체 모든 정보
    // dummyCard, blanketCard
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
    fprintf(fp, "dummyCard : ");
    while(head != NULL) {
        fprintf(fp, "%d ", head->data); 

        head = head->next;
    }
    fprintf(fp, "\n");
    
    head = blanketCard;

    // blanketCard 정보 저장
    fprintf(fp, "blanketCard : ");
    while(head != NULL) {
        fprintf(fp, "%d ", head->data); 

        head = head->next;
    }
    fprintf(fp, "\n");

    // gusip 정보 저장
    fprintf(fp, "gusip : %d", gusip);

    // player들 정보 저장
    fprintf(fp, "player1 id : %d\n", players[0].id);    
    fprintf(fp, "player1 score : %d\n", players[0].score); 
    fprintf(fp, "player1 played : %d\n", players[0].played);    
    fprintf(fp, "player1 money : %d\n", players[0].money);    
    fprintf(fp, "player1 turn : %d\n", players[0].turn);    
    
    head = players[0].holding_card;

    fprintf(fp, "player1 holding card : ");
    while(head != NULL) {
        fprintf(fp, "%d ", head->data);

        head = head->next;
    }
    fprintf(fp, "\n");

    head = players[0].eating_card;

    fprintf(fp, "player1 eating card : ");
    while(head != NULL) {
        fprintf(fp, "%d ", head->data);

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
    fprintf(fp, "player2 played : %d\n", players[1].played);    
    fprintf(fp, "player2 money : %d\n", players[1].money);    
    fprintf(fp, "player2 turn : %d\n", players[1].turn);    
    
    head = players[1].holding_card;

    fprintf(fp, "player2 holding card : ");
    while(head != NULL) {
        fprintf(fp, "%d ", head->data);

        head = head->next;
    }
    fprintf(fp, "\n");

    head = players[1].eating_card;

    fprintf(fp, "player2 eating card : ");
    while(head != NULL) {
        fprintf(fp, "%d ", head->data);

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
    fprintf(fp, "player3 played : %d\n", players[2].played);    
    fprintf(fp, "player3 money : %d\n", players[2].money);    
    fprintf(fp, "player3 turn : %d\n", players[2].turn);    
    
    head = players[2].holding_card;

    fprintf(fp, "player3 holding card : ");
    while(head != NULL) {
        fprintf(fp, "%d ", head->data);

        head = head->next;
    }
    fprintf(fp, "\n");

    head = players[2].eating_card;

    fprintf(fp, "player3 eating card : ");
    while(head != NULL) {
        fprintf(fp, "%d ", head->data);

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


void load() {
    FILE *fp;
    fp = fopen("save.txt", "r");
    char line[512];
    card *head = (card *)malloc(sizeof(card)*CardMAX); // TODO: malloc으로 할당한 거 다 0으로 초기화되나?
    int i = 0;
    int j;

    if(fp == NULL) {
        fprintf(stderr, "파일 open을 실패하였습니다.\n");

        return;
    }

    while(fgets(line, 512, fp) != NULL) {
        if(strstr(line, "dummyCard :")) {
            sscanf(line, "dummyCard: %d", &head[i++].data);

            while(line[0] == '\n') {
                sscanf(line, " %d", &head[i++].data);
            }

            for(j=0; j < i; ++j) {
                head[j].next = &head[j+1];
            }

            dummyCard = &head[0];
            i = 0;
        }

        // TODO: head 초기화
        if(strstr(line, "blanketCard :")) {
            sscanf(line, "blanketCard: %d", &head[i++].data);

            while(line[0] == '\n') {
                sscanf(line, " %d", &head[i++].data);
            }

            for(j=0; j < i; ++j) {
                head[j].next = &head[j+1];
            }

            blanketCard = &head[0];
            i = 0;
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
        }

        // TODO: head 초기화
        if(strstr(line, "players1 holding card :")) {
            sscanf(line, "players1 holding card : %d", &head[i++].data);

            while(line[0] == '\n') {
                sscanf(line, " %d", &head[i++].data);
            }

            for(j=0; j < i; ++j) {
                head[j].next = &head[j+1];
            }

            players[0].holding_card = &head[0];
            i = 0;
        }
        
        // TODO: head 초기화
        if(strstr(line, "players1 eating card :")) {
            sscanf(line, "players1 eating card : %d", &head[i++].data);

            while(line[0] == '\n') {
                sscanf(line, " %d", &head[i++].data);
            }

            for(j=0; j < i; ++j) {
                head[j].next = &head[j+1];
            }

            players[0].eating_card = &head[0];
            i = 0;
        }
        if(strstr(line, "player1 rule :")) {
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
        }
        // TODO: head 초기화
        if(strstr(line, "players2 holding card :")) {
            sscanf(line, "players2 holding card : %d", &head[i++].data);

            while(line[0] == '\n') {
                sscanf(line, " %d", &head[i++].data);
            }

            for(j=0; j < i; ++j) {
                head[j].next = &head[j+1];
            }

            players[1].holding_card = &head[0];
            i = 0;
        }
        // TODO: head 초기화
        if(strstr(line, "players2 eating card :")) {
            sscanf(line, "players2 eating card : %d", &head[i++].data);

            while(line[0] == '\n') {
                sscanf(line, " %d", &head[i++].data);
            }

            for(j=0; j < i; ++j) {
                head[j].next = &head[j+1];
            }

            players[1].eating_card = &head[0];
            i = 0;
        }
        if(strstr(line, "player2 rule :")) {
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
        }
        // TODO: head 초기화
        if(strstr(line, "players3 holding card :")) {
            sscanf(line, "players3 holding card : %d", &head[i++].data);

            while(line[0] == '\n') {
                sscanf(line, " %d", &head[i++].data);
            }

            for(j=0; j < i; ++j) {
                head[j].next = &head[j+1];
            }

            players[2].holding_card = &head[0];
            i = 0;
        }
        // TODO: head 초기화
        if(strstr(line, "players3 eating card :")) {
            sscanf(line, "players3 eating card : %d", &head[i++].data);

            while(line[0] == '\n') {
                sscanf(line, " %d", &head[i++].data);
            }

            for(j=0; j < i; ++j) {
                head[j].next = &head[j+1];
            }

            players[2].eating_card = &head[0];
        }
        if(strstr(line, "player3 rule :")) {
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
