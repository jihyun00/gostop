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

card *getSecondCard(card *card_list, int data) {  
    card *head = card_list;
    card *ans=NULL;
    if(head == NULL) {
        return NULL;
    }

    while(head != NULL) { // 노드가 끝일 때까지
        if((head->data)/4 == (head->data)/4) {
            ans=head;

        } else {
            head = head->next;
        }
    }

    return ans;
}

int getSame(card *card_list, int data) {  
    card *head = card_list;
    int cnt=0;
    if(head == NULL) {
        return 0;
    }

    while(head != NULL) { // 노드가 끝일 때까지
        if((head->data)/4 == ((head->next)->data)/4) {
            cnt++;

        } else {
            head = head->next;
        }
    }

    return cnt;
}

