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
    card **initialCard = (card **)malloc(sizeof(card)*CardMAX);
    card *dummpyCard = (card *)malloc(sizeof(card));
    card *blanketCard = (card *)malloc(sizeof(card));
    card *playerOneCard = (card *)malloc(sizeof(card));
    card *playerTwoCard = (card *)malloc(sizeof(card));
    card *playerThreeCard = (card *)malloc(sizeof(card));
   
    for(i=0; i < CardMAX; ++i) { // initialize card 
        initialCard[i]->data = i; 
        initialCard[i]->next = NULL;
    }

    cardShuffle(initialCard);

    playerOneCard = initialCard[0];
    for(i=1; i < 7; ++i) {
        playerOneCard->next = initialCard[i];
    }
    players[0]->holding_card = playerOneCard;

    playerTwoCard = initialCard[7];
    for(i=8; i < 14; ++i) {
        playerTwoCard->next = initialCard[i];
    }
    players[1]->holding_card = playerTwoCard;

    playerThreeCard = initialCard[14];
    for(i=14; i < 20; ++i) {
        playerThreeCard->next = initialCard[i];
    }
    players[2]->holding_card = playerThreeCard;

    blanketCard = initialCard[20]; 
    for(i=20; i < 25; ++i) {
        blanketCard->next = initialCard[i];
    }

    dummyCard = initialCard[25];
    for(i=25; i < CardMAX; ++i) {
        dummyCard->next = initialCard[i];
    }
}


void cardShuffle(card **card_list) {
    int i;
    bool duplicated_check[CardMAX] = { 0, };

    srand((unsigned)time(NULL));

    for(i=0; i < CardMAX; ++i) {
        int value = rand()%CardMAX;     

        if(duplicated_check[value] == false) {
            duplicated_check[value] = true;
            card_list[i]->data = value;
        }
    }
}


card *orderCard(card **card_list) {
    // bubble sort 써서 정렬?     
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
