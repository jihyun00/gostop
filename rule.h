#ifndef _RULE_H_
#define _RULE_H_

typedef struct _rule{// rule 구조체
    int shake; //흔들기
    int sulsa; //설사
    int clear_board; // 판쓰리
    int chongtong; // 총통
    int go; // 고
    int nagari;  // 나가리
    int gobak;  //고
} rule; 

void initializeRule(int index);//rules 구조체 초기화
void setShake();//흔들기
void setSulsa();// 설사 기능 설정
int getSulsa();// 설사한 적이 있는지 체크
int isClearBoard();// 판 쓰리 체크
void setClearBoard();// 판쓰리 설정
void setChongtong(int index);// 총통 여부 체크
void isNagari();// 나가리 여부 체크
void getPi(int turn);// 다른 사람에게 피를 한 장씩 가져오는 함수
int setGo();// 점수가 났는지 체크 후 점수 났을 경우 go를 할지 말지 체크
void setStop();// 고를 할 수 있는 상황에서 stop을 했을 때 처리하는 함수
void gameEnd();// 게임이 마무리되고 승자를 가리고, 잔고 등을 출력해주는 함수

#endif
