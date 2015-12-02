#include "card.h"
#include "player.h"
#include "rule.h"
#include <string.h>
#include <unistd.h>

const char cardMatrix[CardMAX][10] = {
    "1광","1오","1피1","1피2",
    "2십","2오","2피1","2피2",
    "3광","3오","3피1","3피2",
    "4십","4오","4피1","4피2",
    "5십","5오","5피1", "5피2",
    "6십","6오","6피1","6피2",
    "7십","7오","7피1","7피2",
    "8광","8십","8피1","8피2",
    "9십","9오","9피1","9피2",
    "10십","10오","10피1","10피2",
    "11광","11쌍피","11피1","11피2",
    "12광","12십","12띠","12쌍피" 
};

void cardInitialize() {
    int i;
    card *initialCard = (card *)malloc(sizeof(card)*CardMAX);
    card *playersCard = (card *)malloc(sizeof(card)*MAX_NUMBER_OF_PLAYER);

    dummyCard = (card *)malloc(sizeof(card));
    blanketCard = (card *)malloc(sizeof(card));

    for(i=0; i < CardMAX; ++i) { // initialize card 
        initialCard[i].data = i; 
        initialCard[i].next = NULL;
    }

    players[0].eating_card = (card *)malloc(sizeof(card));
    players[1].eating_card = (card *)malloc(sizeof(card));
    players[2].eating_card = (card *)malloc(sizeof(card));

    players[0].eating_card->data = -1;
    players[0].eating_card->next = NULL;

    players[1].eating_card->data = -1;
    players[1].eating_card->next = NULL;

    players[2].eating_card->data = -1;
    players[2].eating_card->next = NULL;

    cardShuffle(initialCard);

    divideCard(initialCard, playersCard);
}


void divideCard(card *card_list, card *players_card) {
    int i;
    card *head = NULL;

    head = &players_card[0];
    for(i=0; i < 7; ++i) {
        head->data = card_list[i].data;
        if(i != 6) {
            head->next = &card_list[i+1];

        } else {
            head->next = NULL;    
        }

        head = head->next; 
    }

    orderCard(&players_card[0]);
    players[0].holding_card = &players_card[0];

    head = &players_card[1];
    for(i=7; i < 14; ++i) {
        head->data = card_list[i].data;
        if(i != 13) {
            head->next = &card_list[i+1];

        } else {
            head->next = NULL;    
        }

        head = head->next; 
    }

    orderCard(&players_card[1]);
    players[1].holding_card = &players_card[1];

    head = &players_card[2];
    for(i=14; i < 21; ++i) {
        head->data = card_list[i].data;
        if(i != 20) {
            head->next = &card_list[i+1];

        } else {
            head->next = NULL;    
        }

        head = head->next; 
    }

    orderCard(&players_card[2]);
    players[2].holding_card = &players_card[2];

    // 흔들기 처리
    for(i=0; i < MAX_NUMBER_OF_PLAYER; ++i) {
        setShake(i);  
        setChongtong(i);
    }
    
    head = blanketCard;
    for(i=21; i < 27; ++i) {
        head->data = card_list[i].data;
        if(i != 26) {
            head->next = &card_list[i+1];

        } else {
            head->next = NULL;    
        }

        head = head->next; 
    }
    orderCard(blanketCard);

    head = dummyCard;
    for(i=27; i < CardMAX; ++i) {
        head->data = card_list[i].data;
        if(i != CardMAX-1) {
            head->next = &card_list[i+1];

        } else {
            head->next = NULL;    
        }

        head = head->next; 
    }
}


void cardShuffle(card *card_list) {
    int i;
    int duplicated_check[CardMAX] = { 0, };

    srand((unsigned)time(NULL));

    for(i=0; i < CardMAX; ++i) {
        int value = rand()%CardMAX;     

        if(duplicated_check[value] == false) {
            duplicated_check[value] = true;
            card_list[i].data = value;

        } else {
            i--;
        }
    }
}


void orderCard(card *card_list) {
    card *q;
    card *r;
    int temp;

    if(card_list == NULL) {
        return;
    }
    
    for(q=card_list; q->next != NULL; q=q->next) {
        for(r=card_list; r->next != NULL; r=r->next) {
            if(r->data > r->next->data) {
                temp = r->data;
                r->data = r->next->data;
                r->next->data = temp;
            }
        }
    }
}


card *getCard(card *card_list, int data) {  
    card *head = card_list;

    if(head == NULL) {
        return NULL;
    }

    while(head != NULL) { // 노드가 끝일 때까지
        if(head->data == data) {
            return head;

        } else {
            head = head->next;
        }
    }

    return NULL;
}


int selectCard(card *card_list) {
    card *head = card_list;
    
    if(head == NULL) {
        return -1;
    }

    return head->data; 
}


void cardInsert(card *card_list, int data) { 
    card *head = card_list;
    card *prev = NULL;
    card *temp = (card *)malloc(sizeof(card));

    card *target = (card *)malloc(sizeof(card));
    target->data = data;
    target->next = NULL;

    // holding card가 0인 상태일 때
    if(data == -1) {
        return;
    }

    // 첫 번째 카드에 넣기 
    while(head != NULL) {
        if(head->data == -1) {
            head->data = data;
            head->next = NULL;

        } else {
            if(head->data > data) {
                if(prev == NULL) {
                    temp->data = head->data;
                    head->data = target->data;
                    target->data = temp->data;

                    prev = head;
                    head = head->next;
                }
                    
                prev->next = target;
                target->next = head;

                return;
            }

            // data가 list의 맨 마지막에 들어가는 경우
            if(head->next == NULL) {
                head->next = target; 
                
                return;
            }
        }

        prev = head;
        head = head->next;
    }
}


void cardDelete(card *card_list, int data) {  
    card *head = card_list;
    card *temp = (card *)malloc(sizeof(card));
    card *prev = NULL;
    int i;
    int size = getCardSize(card_list);

    //첫 번째 카드 지우기
    if(head != NULL && head->data == data) { 
        if(getCardSize(head) == 1) {
            head->data = -1;
            head->next = NULL;

            return;
        }

        for(i=0; i < size-1; ++i) {
           head->data = head->next->data; 
           prev = head;
           head = head->next;
        }
        
        prev->next = head->next;
        head->next = head;
        
        return;
    }

    while(head != NULL) {
        if(head->data == data) {
            prev->next = head->next;
            head->next = head;

            return;

        } else {
            prev = head;
            head = head->next;
        }
    }
}


int getCardSize(card *card_list) {
    int size = 0;
    card *head = card_list;

    while(head != NULL) {
        size++;
        head = head->next;
    }

    return size;
}


int* getSame(card *card_list, int data, int *size) {  
    int i = 0;
    *size = 0;
    int *res = (int *)malloc(sizeof(int)*3);
    card *head = card_list;

    memset(res, -1, sizeof(int)*3); // res 초기화

    if(head == NULL) {
        return res;
    }

    if(data == -1) {
        *size = 0;

        return res;
    }

    while(head != NULL) { // 노드가 끝일 때까지
        if((head->data/4) == data/4) {
            *size = *size+1;
            res[i++] = head->data;
        }

        head = head->next;
    }

    return res;
}


void putCard(int num) {
    int hasPair = 0;
    int hasDummyPair = 0;
    int turn;
    int selected_data;
    int index;
    int i;
    int *res;
    int *dummyRes;
    int selected;
    int dummySelected;

    card *holding = NULL;
    card *eating = NULL;
    card *head = NULL;

    turn = getTurn();

    holding = players[turn].holding_card;
    eating = players[turn].eating_card;

    head = holding;

    if(num == 9) {
        toggle();

        printf("카드를 선택해주세요.\n");

        scanf("%d", &num);
    }

    // 사용자 인터페이스에서 1~7 사이의 값으로 입력받은 걸
    // 카드 데이터로 변경
    for(i=0; i < num; ++i) {
        index = head->data; 

        head = head->next;
    }

    res = getSame(blanketCard, index, &hasPair);
    selected_data = selectCard(dummyCard);
    cardDelete(dummyCard, selected_data);
    cardDelete(holding, index);

    if(hasPair > 0) {
        if((selected_data/4) == (index/4)) { 
            if(hasPair > 1) { // 따닥
                cardInsert(eating, index);
                cardInsert(eating, res[0]);
                cardInsert(eating, res[1]);
                cardInsert(eating, selected_data);

                getPi(turn);

            } else { // 설사
                cardInsert(blanketCard, index);
                cardInsert(blanketCard, res[0]);
                cardInsert(blanketCard, selected_data);

                setSulsa();
            }

        } else {
            cardInsert(eating, index);

            if(hasPair > 1) {
                if(hasPair > 2 && (getSulsa() > -1)) { // 싼 거 먹기
                    cardInsert(eating, res[0]); 
                    cardInsert(eating, res[1]); 
                    cardInsert(eating, selected_data);

                    players[getSulsa()].rules->sulsa = 0;

                    getPi(turn);

                } else {
                    printf("짝이 맞는 두 개의 카드 중 어느 카드를 고르시겠습니까? (1, 2 중 하나 입력)\n");
                    for(i=0; i < hasPair; ++i) {
                        if(res[i] == -1) {
                            continue;
                        }
                        printf("%s ", cardMatrix[res[i]]); 
                    }
                    printf("\n");

                    scanf("%d", &dummySelected);

                    if(dummySelected == 1) {
                        cardDelete(blanketCard, res[0]);
                        cardInsert(eating, res[0]); 
                    } else {
                        cardDelete(blanketCard, res[1]);
                        cardInsert(eating, res[1]);
                    }
                }

            } else {
                cardDelete(blanketCard, res[0]);
                cardInsert(eating, res[0]);
            }

            dummyRes = getSame(blanketCard, selected_data, &hasDummyPair);

            if(hasDummyPair > 0) {
                cardInsert(eating, selected_data);

                if(hasDummyPair > 1) {
                    printf("짝이 맞는 두 개의 카드 중 어느 카드를 고르시겠습니까? (1, 2 중 하나 입력)\n");
                    for(i=0; i < hasDummyPair; ++i) {
                        if(dummyRes[i] == -1) {
                            continue;
                        }
                        printf("%s ", cardMatrix[dummyRes[i]]); 
                    }
                    printf("\n");

                    scanf("%d", &dummySelected);

                    if(dummySelected == 1) {
                        cardDelete(blanketCard, dummyRes[0]);
                        cardInsert(eating, dummyRes[0]); 
                    } else {
                        cardDelete(blanketCard, dummyRes[1]);
                        cardInsert(eating, dummyRes[1]);
                    }

                } else {
                    cardDelete(blanketCard, dummyRes[0]);
                    cardInsert(eating, dummyRes[0]);
                }

            } else {
                cardInsert(blanketCard, selected_data);
            }
        }

    } else {
        dummyRes = getSame(blanketCard, selected_data, &hasDummyPair);

        cardInsert(blanketCard, index); 

        if(hasDummyPair > 0) {
            cardInsert(eating, selected_data);

            if(hasDummyPair > 1) {
                printf("짝이 맞는 두 개의 카드 중 어느 카드를 고르시겠습니까? (1, 2 중 하나 입력)\n");
                for(i=0; i < hasDummyPair; ++i) {
                    if(dummyRes[i] == -1) {
                        continue;
                    }
                    printf("%s ", cardMatrix[dummyRes[i]]); 
                }
                printf("\n");

                scanf("%d", &dummySelected);

                if(dummySelected == 1) {
                    cardDelete(blanketCard, dummyRes[0]);
                    cardInsert(eating, dummyRes[0]); 
                } else {
                    cardDelete(blanketCard, dummyRes[1]);
                    cardInsert(eating, dummyRes[1]);
                }

            } else {
                cardDelete(blanketCard, dummyRes[0]);
                cardInsert(eating, dummyRes[0]);
            }

        } else {
            cardInsert(blanketCard, selected_data);
        }
    }

    // 판 쓰리 체크
    if(isClearBoard() == 1) {
        printf("%d 유저가 판 쓰리~ \n", turn);

        sleep(1);
    }
}


void toggle() {
    int turn = getTurn();

    card *eating = players[turn].eating_card;

    if(getCard(eating, 32) != NULL && gusip == 0) {
        gusip = 1;

        printf("9십을 십으로 이동합니다.\n");
    }
}
