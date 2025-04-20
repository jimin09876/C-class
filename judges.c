#include <stdio.h>
#include <stdlib.h>

#define MAX_JUDGES 100
#define BUFFER_SIZE 1024

char judges_array[MAX_JUDGES][BUFFER_SIZE];

int main() {
    char project[100];
    int total = 0;
    int select = 0;

    printf("####################################\n");
    printf("#      심사위원 명단 데이터 입력       #\n");
    printf("####################################\n");

    printf("> 참여 프로젝트: ");
    fgets(project, sizeof(project), stdin);
    // 개행 문자 제거
    int p = 0;
    while (project[p] != '\0') {
        if (project[p] == '\n') {
            project[p] = '\0';
            break;
        }
        p++;
    }

    printf("> 심사 총 인원: ");
    scanf("%d", &total);
    getchar(); // 개행 문자 제거

    printf("> 선발 멤버 수: ");
    scanf("%d", &select);
    getchar();

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("%d명의 심사위원 정보 입력을 시작합니다.\n", total);
    printf("++++++++++++++++++++++++++++++++++++\n");

    int i = 0;
    while (i < total) {
        char name[100], gender[10], company[100], title[100];
        char field[100], email[100], phone[100];

        printf("*심사위원 %d:\n", i + 1);

        printf("  이름: ");
        fgets(name, sizeof(name), stdin);
        printf("  성별: ");
        fgets(gender, sizeof(gender), stdin);
        printf("  소속: ");
        fgets(company, sizeof(company), stdin);
        printf("  직함: ");
        fgets(title, sizeof(title), stdin);
        printf("  전문분야: ");
        fgets(field, sizeof(field), stdin);
        printf("  메일: ");
        fgets(email, sizeof(email), stdin);
        printf("  전화: ");
        fgets(phone, sizeof(phone), stdin);

        // 개행 문자 제거
        int j = 0;
        while (name[j] != '\0') {
            if (name[j] == '\n') name[j] = '\0';
            j++;
        }
        j = 0;
        while (gender[j] != '\0') {
            if (gender[j] == '\n') gender[j] = '\0';
            j++;
        }
        j = 0;
        while (company[j] != '\0') {
            if (company[j] == '\n') company[j] = '\0';
            j++;
        }
        j = 0;
        while (title[j] != '\0') {
            if (title[j] == '\n') title[j] = '\0';
            j++;
        }
        j = 0;
        while (field[j] != '\0') {
            if (field[j] == '\n') field[j] = '\0';
            j++;
        }
        j = 0;
        while (email[j] != '\0') {
            if (email[j] == '\n') email[j] = '\0';
            j++;
        }
        j = 0;
        while (phone[j] != '\0') {
            if (phone[j] == '\n') phone[j] = '\0';
            j++;
        }

        // 필수 항목 누락 체크
        if (name[0] == '\0' || gender[0] == '\0' || company[0] == '\0' ||
            title[0] == '\0' || field[0] == '\0' || email[0] == '\0' || phone[0] == '\0') {
            printf("입력 항목이 정확하지 않습니다. 다시 입력해주세요.\n");
            continue;
        }

        // JSON 형식 문자열로 조합
        int len = 0;
        len += sprintf(judges_array[i] + len, "\"이름\":\"%s\",", name);
        len += sprintf(judges_array[i] + len, "\"성별\":\"%s\",", gender);
        len += sprintf(judges_array[i] + len, "\"소속\":\"%s\",", company);
        len += sprintf(judges_array[i] + len, "\"직함\":\"%s\",", title);
        len += sprintf(judges_array[i] + len, "\"전문분야\":\"%s\",", field);
        len += sprintf(judges_array[i] + len, "\"메일\":\"%s\",", email);
        len += sprintf(judges_array[i] + len, "\"전화\":\"%s\"", phone);

        i++; // 다음 심사위원으로
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("심사위원 정보 입력이 끝났습니다.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");

    char confirm;
    printf("\"%s\" 심사위원 정보를 확인할까요? (Y/N): ", project);
    scanf(" %c", &confirm);

    if (confirm == 'Y') {
        printf("####################################\n");
        printf("#        심사위원 데이터 출력        #\n");
        printf("####################################\n");

        for (int j = 0; j < total; j++) {
            char name[100], gender[10], company[100], title[100], field[100], email[100], phone[100];

            sscanf(judges_array[j],
                "\"이름\":\"%[^\"]\",\"성별\":\"%[^\"]\",\"소속\":\"%[^\"]\",\"직함\":\"%[^\"]\",\"전문분야\":\"%[^\"]\",\"메일\":\"%[^\"]\",\"전화\":\"%[^\"]\"",
                name, gender, company, title, field, email, phone);

            printf("[심사위원 %d]\n", j + 1);
            printf("이름:%s\n", name);
            printf("성별:%s\n", gender);
            printf("소속:%s\n", company);
            printf("직함:%s\n", title);
            printf("전문분야:%s\n", field);
            printf("메일:%s\n", email);
            printf("전화:%s\n", phone);
            printf("-----------------------------------\n");
        }
    } else {
        printf("프로그램을 종료합니다.\n");
    }

    return 0;
}
