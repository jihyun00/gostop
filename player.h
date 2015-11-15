#define MAX_NUMBER_OF_PLAYER    3
#define INITIAL_MONEY   100000
#define NOT_PLAY    0 // play 한 적 없음
#define PLAYED      1 // play 한 적 있음

typedef struct _player {
    char id[5]; // player ID
    int score; // player 점수
    int played;// 이전에 play했는지 체크
    int money; // player가 갖고 있는 돈
    // TODO: 갖고 있는 패, card에 대한 정보

} player;

player players[MAX_NUMBER_OF_PLAYER];
