// splash.c
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 100

int main() {
    char name[MAX_LEN];
    char date_input[MAX_LEN];
    int year, month, day;

    // 날짜 입력
    printf("[현재 날짜를 \"yyyy-mm-dd\" 형식으로 입력하세요]: ");
    scanf(" %s", date_input);

    // 이름 입력 전 버퍼 비우기
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    // 이름 입력
    printf("[당신의 이름을 입력하세요]: ");
    scanf(" %[^\n]", name);  // 공백 포함 입력

    // 날짜 포맷 처리
    if (sscanf(date_input, "%d-%d-%d", &year, &month, &day) != 3) {
        printf("날짜 형식이 잘못되었습니다.\n");
        return 1;
    }

    // 입력 완료 메시지
    printf("**입력이 정상적으로 처리되었습니다.**\n");

    // 스플래시 출력
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
    printf("                         [마그라테아 ver 0.1]                              \n");
    printf("           풀 한 포기 없는 황무지에서 반짝이는 행성을 만들내는 곳 마그라테아,\n");
    printf("         사람들이 보지 못하는 잠재력을 찾고 전문가의 손길을 더해 보석을 빗는 곳,\n");
    printf("           마그라테아에 오신걸 환영합니다.   \n\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("[사용자]: %s                                   [실행 시간]: %d년 %d월 %d일\n", name, year, month, day);
    printf("================================================================================\n");

    return 0;
}