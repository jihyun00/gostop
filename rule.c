#include "rule.h"
#include "player.h"
#include "status.h"

#include <string.h>


//rules 구조체 초기화
void initializeRule(int index) {
    players[index].rules = (rule *)malloc(sizeof(rule)); 
    players[index].rules->shake = 0;
    players[index].rules->sulsa = 0;
    players[index].rules->clear_board = 0;
    players[index].rules->chongtong = 0;
    players[index].rules->go = 0;
    players[index].rules->nagari = 0;
    players[index].rules->gobak = 0;
}

//흔들기
void setShake(int index) {
	card *head = NULL;
	int c = 1;
    int prev;

    head = players[index].holding_card;
    prev = head->data/4;
    while(head->next != NULL) {
        if(prev == head->next->data/4) {
            c++;
        } else {
            c = 1;
        }
        if(c==3){
            players[index].rules->shake += 1;

            break;
        }
        prev = head->next->data/4;
        head = head->next;
    }
}

// 설사 기능 설정
void setSulsa() {
    int turn = getTurn();

    players[turn].rules->sulsa = players[turn].rules->sulsa + 1;
    if(players[turn].rules->sulsa==3){
        players[turn].history=3;
        gameEnd();
    }
}


// 설사한 적이 있는지 체크
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
    if(getCardSize(blanketCard) == 1 && blanketCard->data == -1) {
        setClearBoard();
        return 1;
    }
    return 0;
}


// 판쓰리 설정
void setClearBoard(){
    int i;
    int turn = getTurn();
    players[turn].rules->clear_board = 1;
    getPi(turn);
}


// 총통 여부 체크
void setChongtong(int index) {
	card *head = NULL;
	int c = 1;
    int prev;
    int turn=getTurn();
	head = players[index].holding_card;
    prev = head->data/4;
    while(head->next != NULL) {
        if(prev == head->next->data/4) {  // 4로 나누었을때의 몫이 같으면 같은 달이므로 총통이 된다.
            c++;

        } else {
            c = 1;
        }

        if(c==4){
            players[index].rules->chongtong += 1;
            players[turn].history=3;
            gameEnd();
            break;
        }
        prev = head->next->data/4;
        head = head->next;
    }    
}


// 나가리 여부 체크
void isNagari() {
    int i, j;
    int cnt;
    int turn = getTurn();
    int num_of_go = 0;

	if((dummyCard->data == -1) && (getCardSize(dummyCard) == 1)) {
        // 아무도 3점 이상 내지 못했을 경우
		if((getScore(0) < 3) && (getScore(1) < 3) && (getScore(2) < 3)) {
            printf("아무도 3점 이상 못냈을 경우\n");
            nagari = 1;
            printf("이번 판은 나가리~\n");

		} else { // 고를 했으나 추가 점수가 나지 않은 경우
            for(i=0; i < MAX_NUMBER_OF_PLAYER; ++i) {
                cnt = 0;
                num_of_go = players[i].rules->go;

                if(players[i].score < players[i].additional_score + 1) {
                    nagari = 1;
                    printf("이번 판은 나가리~\n");

                    break;
                }
            }
            players[turn].history=4;
        }

        gameEnd();
    }
}


// 다른 사람에게 피를 한 장씩 가져오는 함수
void getPi(int turn) {
    int i;
    card *head = NULL;
    
    for(i=0; i < MAX_NUMBER_OF_PLAYER; ++i) {
        if(i == turn) {
            continue;
        }

        head = players[i].eating_card;
        if(head == NULL) {
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

// 점수가 났는지 체크 후 점수 났을 경우 go를 할지 말지 체크
int setGo(){ 
    int turn = getTurn();
    char status[10];
    char id[3] = {'A', 'B', 'C'}; // 숫자에 따른 플레이어 이름 출력을 위한 배열

    if(players[turn].rules->go == 0) { // 고를 한 번도 한 적이 없을 때
        if(players[turn].score < 3){ // 3점 이하는 out
            return 0; 
        }
    }
    else { // 고를 한 번 이상했을 때
        if(players[turn].additional_score < 2) {  // 2점 이상 추가로 못 냈을 때는 out
            return 0;
        }
    }
    printf("%c 플레이어가 점수 %d 획득!\n",id[turn],getScore(turn));
    printf("Go하시겠습니까? Stop하시겠습니까? (g, s)"); 
    scanf("%s", status);

    if((strcmp(status, "go") == 0) || (strcmp(status, "g") == 0)) {
        players[turn].rules->go += 1;
        players[turn].score += 1;
        players[turn].additional_score = players[turn].score; 
        players[turn].gobak = 1;   // 고박 체크하는 부분.
        players[(turn+1)%3].gobak= 0;  // 나머지 사람들은 고박에 대한 값을 없앰.
        players[(turn+2)%3].gobak= 0;

        return players[turn].rules->go;
    } else if((strcmp(status, "stop") == 0) || (strcmp(status, "s") == 0)) {
        setStop();

    } else {
        printf("명령어를 잘못 입력하셨습니다.\n");

        setGo(); 
    }

    return 0;
}


// 고를 할 수 있는 상황에서 stop을 했을 때 처리하는 함수
void setStop() {
    int turn=getTurn();
    printf("STOP 합니다, 게임을 종료합니다.\n");
    players[turn].winner=1;  //승자 표시해두는 부분.
    players[turn].history=0;
             
    gameEnd(); 
}

// 게임이 마무리되고 승자를 가리고, 잔고 등을 출력해주는 함수
void gameEnd() {
    int i;
    int winner;
    char name[5]={'A','B','C'};
    player* tmp= NULL;
    char command[10];
    int playersMoney[3];

    tmp = setWinner();
    if(tmp ==NULL) {
        printf("게임 종료되었습니다.\n");

    } else{
        winner = tmp->id;
        printf("게임 종료되었습니다. 승자는 %c\n", name[winner]);
        for(i=0;i<3;i++){
            setMoney(i);
        }
    }
    printf("-------게이머의 잔고---------\n");
    for(i=0;i<3;i++){
        printf("%c의 잔고 : %d 원\n", name[i], getMoney(i));
        playersMoney[i] = getMoney(i);
    }

    printf("게임을 계속하시겠습니까?(y, n)\n");
    
    while(1) {
        scanf("%s", command);

        if(strcmp(command, "y") == 0 || (strcmp(command, "yes") == 0)) {
            setPlayerInfo(); 
            if(nagari != 1) {
                setWinnerTurn((winner+MAX_NUMBER_OF_PLAYER-1)%MAX_NUMBER_OF_PLAYER); 

            } else {
                before_nagari = 1;
            }

            initializedPCS();
            gusip = 0;
            
            for(i=0; i < MAX_NUMBER_OF_PLAYER; ++i) {
                players[i].money = playersMoney[i];
            }

            break;

        } else if(strcmp(command, "n") == 0 || (strcmp(command, "no") == 0)) {
            exit(0);

        } else {
            getCommand(command);
        }
    }
}
