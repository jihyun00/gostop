void setScore(player playerId);
int getScore(player playerId);
void setMoney(player playerId);
int getMoney(player playerId);
void drawScreen(); // status 변할 때마다 화면에 값 그려주기
                   // 플레이어 차례, 점수, 갖고 있는 패 등 그려주기
void drawInterface(char *command); // 사용자 인터페이스 처리
