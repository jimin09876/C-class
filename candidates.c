#include <stdio.h>
#include <stdlib.h>

#define NUM_CANDIDATES 6
#define MAX_LEN 150

typedef struct {
    char name[MAX_LEN];
    char birth[MAX_LEN];     // YYYY/MM/DD 형식 입력 후 YYYYMMDD로 저장
    char gender;
    char email[MAX_LEN];
    char nationality[MAX_LEN];
    float bmi;
    char main_skill[MAX_LEN];
    char sub_skill[MAX_LEN];
    int topik;               // 0은 원어민
    char mbti[MAX_LEN];
    char intro[MAX_LEN];
} MemberInfo;

// 구조체 6개 변수
MemberInfo candidate01, candidate02, candidate03;
MemberInfo candidate04, candidate05, candidate06;

void format_birth(char* birth) {
    // birth: "YYYY/MM/DD" → "YYYYMMDD"
    char y[5], m[3], d[3];
    sscanf(birth, "%4s/%2s/%2s", y, m, d);
    sprintf(birth, "%s%s%s", y, m, d);
}

void format_topik(int topik, char* out) {
    if (topik == 0) {
        sprintf(out, "원어민");
    } else {
        sprintf(out, "%d", topik);
    }
}

int main() {
    MemberInfo* member_info[NUM_CANDIDATES] = {
        &candidate01, &candidate02, &candidate03,
        &candidate04, &candidate05, &candidate06
    };

    int i = 0;
    int ch;

    printf("####################################\n");
    printf("     오디션 후보자 데이터 입력\n");
    printf("####################################\n");

    // 입력
    while (i < NUM_CANDIDATES) {
        printf("\n%d번째 후보자의 정보를 입력합니다.\n", i + 1);
        printf("---------------------------------\n");

        while ((ch = getchar()) != '\n' && ch != EOF);  // 버퍼 비우기

        printf("1. 성명: ");
        scanf(" %[^\n]", member_info[i]->name);

        printf("2. 생일(YYYY/MM/DD 형식): ");
        scanf(" %s", member_info[i]->birth);
        format_birth(member_info[i]->birth);

        printf("3. 성별(여성이면 F 또는 남성이면 M): ");
        scanf(" %c", &member_info[i]->gender);

        while ((ch = getchar()) != '\n' && ch != EOF);  // 버퍼 비우기

        printf("4. 메일 주소: ");
        scanf(" %s", member_info[i]->email);

        printf("5. 국적: ");
        scanf(" %s", member_info[i]->nationality);

        printf("6. BMI: ");
        scanf(" %f", &member_info[i]->bmi);

        printf("7. 주 스킬: ");
        scanf(" %s", member_info[i]->main_skill);

        printf("8. 보조 스킬: ");
        scanf(" %[^\n]", member_info[i]->sub_skill);

        printf("9. 한국어 등급(TOPIK): ");
        scanf(" %d", &member_info[i]->topik);

        printf("10. MBTI: ");
        scanf(" %s", member_info[i]->mbti);

        while ((ch = getchar()) != '\n' && ch != EOF);  // 버퍼 비우기

        printf("11. 소개: ");
        scanf(" %[^\n]", member_info[i]->intro);

        printf("=================================\n");

        i++;
    }

    // 출력
    printf("\n####################################\n");
    printf("     오디션 후보자 데이터 조회 \n");
    printf("####################################\n");

    printf("=============================================================================================\n");
    printf("성   명 | 생   일 | 성별 | 메   일             | 국적 | BMI  | 주스킬 | 보조스킬        | TOPIK  | MBTI |\n");
    printf("=============================================================================================\n");

    for (int j = 0; j < NUM_CANDIDATES; j++) {
        char topik_str[10];
        format_topik(member_info[j]->topik, topik_str);

        printf("%-6s |%-8s | %-4c | %-19s |%-4s | %4.1f | %-6s | %-14s | %-6s | %-5s |\n",
            member_info[j]->name,
            member_info[j]->birth,
            (member_info[j]->gender == 'F' || member_info[j]->gender == 'f') ? '여' : '남',
            member_info[j]->email,
            member_info[j]->nationality,
            member_info[j]->bmi,
            member_info[j]->main_skill,
            member_info[j]->sub_skill,
            topik_str,
            member_info[j]->mbti
        );
        printf("---------------------------------------------------------------------------------------------\n");
        printf("%s\n", member_info[j]->intro);
        printf("---------------------------------------------------------------------------------------------\n");
    }

    return 0;
}