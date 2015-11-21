#include "card.h"
#include "player.h"

void cardInitialize() {
    int i;
    card *initialCard = (card *)malloc(sizeof(card)*CardMAX);
    card *playersCard = (card *)malloc(sizeof(card)*MAX_NUMBER_OF_PLAYER);
   
    for(i=0; i < CardMAX; ++i) { // initialize card 
        initialCard[i].data = i; 
        initialCard[i].next = NULL;
    }

    cardShuffle(initialCard);

    divideCard(initialCard, playersCard);
}


void divideCard(card *card_list, card *players_card) {
    card *head = NULL;
    int i;

    players_card[0] = card_list[0];
    for(i=1; i < 7; ++i) {
        players_card[0].next = &card_list[i];
        if(i == 6) {
            players_card[0].next = NULL;
        }
    }
    orderCard(&players_card[0]);
    players[0].holding_card = players_card[0];

    players_card[1] = card_list[7];
    for(i=8; i < 14; ++i) {
        players_card[1].next = &card_list[i];
        if(i == 13) {
            players_card[1].next = NULL;
        }
    }
    orderCard(&players_card[1]);
    players[1].holding_card = players_card[1];

    players_card[2] = card_list[14];
    for(i=14; i < 20; ++i) {
        players_card[2].next = &card_list[i];
        if(i == 19) {
            players_card[2].next = NULL;
        }
    }
    orderCard(&players_card[2]);
    players[2].holding_card = players_card[2];

    blanketCard = card_list[20]; 
    for(i=20; i < 25; ++i) {
        blanketCard.next = &card_list[i];
        if(i == 24) {
            blanketCard.next = NULL;
        }
    }

    dummyCard = card_list[25];
    for(i=25; i < CardMAX; ++i) {
        dummyCard.next = &card_list[i];
        if(i == CardMAX-1) {
            dummyCard.next = NULL;
        }
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


void cardInsert(card *card_list, int data) { 
    card *head = card_list;
    card *target = (card *)malloc(sizeof(card)); 

    while(head->next != NULL) {
        if(head->data > data) {
            target->next = head->next;
            head->next = target;

            return;

        } else {
            head = head->next;
        }
    }

    head->next = target;
}


void cardDelete(card *card_list, int data) {  
    card *head = card_list;
    card *prev = NULL;

    while(head != NULL) {
        if(head->data == data) {
            prev->next = head->next;
            head->next = head;
            
        } else {
            prev = head;
            head = head->next;
        }
    }
}
