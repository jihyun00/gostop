#include "card.h"
#include "player.h"

const char cardMatrix[CardMAX][10] = {
    "1광","1오","1피","1피",
    "2십","2오","2피","2피",
    "3광","3오","3피","3피",
    "4십","4오","4피","4피",
    "5십","5오","5피", "5피",
    "6십","6오","6피","6피",
    "7십","7오","7피","7피",
    "8광","8십","8피","8피",
    "9십","9오","9피","9피",
    "10십","10오","10피","10피",
    "11광","11쌍피","11피","11피",
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
    orderCard(dummyCard);
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
    
    // 첫 번째 카드에 넣기 
    while(head != NULL) {
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


int getSame(card *card_list, int data) {  
    card *head = card_list;
    int cnt = 0;

    if(head == NULL) {
        return -1;
    }

    while(head != NULL) { // 노드가 끝일 때까지
        if((head->data/4) == data/4) {
            cnt++;
        }

        head = head->next;
    }

    return cnt;
}
