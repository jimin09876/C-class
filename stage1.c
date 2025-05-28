#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMBERS 5
#define MAX_NAME 20
#define TEST_COUNT 7
#define DAYS 6

// 밀리웨이즈 멤버 이름
char milliways_members[MAX_MEMBERS][MAX_NAME] = {
    "고니", "철이", "영지", "경이", "아서"
};

// 체력 항목 이름
char test_names[TEST_COUNT][30] = {
    "1마일 러닝", "스프린트", "푸시업", "스쿼트", "팔굽혀펴기", "수영", "무게들기"
};

// 체력 점수 문자열 저장
char health_scores[MAX_MEMBERS][TEST_COUNT][20];

// 운동 유형 및 운동 이름
char *exercise_types[5][3] = {
    {"러닝", "자전거", "빠른걷기"},         // 유산소
    {"푸시업", "스쿼트", ""},              // 전신 근력
    {"레그프레스", "레그컬", ""},           // 하체 근력
    {"철봉", "풀업바", ""},                // 상체 근력
    {"플랭크", "크런치", ""}               // 코어
};

// 멤버별 운동 루틴 [멤버][요일(6)][2개의 운동][운동명 문자열]
char member_routine[MAX_MEMBERS][DAYS][2][20] = {{{0}}};

// 멤버 인덱스 찾기
int findMemberIndex(char nickname[]) {
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(nickname, milliways_members[i]) == 0)
            return i;
    }
    return -1;
}

// 체력 상태 입력
void setHealth() {
    char nickname[MAX_NAME];
    char input[200];
    int index;

    printf("\n[체력 상태 입력]\n닉네임을 입력하세요: ");
    scanf("%s", nickname);
    getchar();

    index = findMemberIndex(nickname);
    if (index == -1) {
        printf("존재하지 않는 닉네임입니다.\n");
        return;
    }

    printf("체력 항목 7개를 쉼표로 구분하여 입력하세요\n");
    printf("예: 8.2,12.5,3.0,2.5,3.0,10.0,1.5\n");
    printf("입력: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    char *token = strtok(input, ",");
    for (int i = 0; i < TEST_COUNT; i++) {
        if (token == NULL) {
            printf("입력이 부족합니다.\n");
            return;
        }
        strcpy(health_scores[index][i], token);
        token = strtok(NULL, ",");
    }

    printf("체력 정보 입력 완료\n");
}

// 체력 상태 조회
void getHealth() {
    char nickname[MAX_NAME];
    int index;

    printf("\n[체력 상태 조회]\n닉네임을 입력하세요: ");
    scanf("%s", nickname);
    getchar();

    index = findMemberIndex(nickname);
    if (index == -1) {
        printf("존재하지 않는 닉네임입니다.\n");
        return;
    }

    printf("[%s]의 체력 정보:\n", nickname);
    for (int i = 0; i < TEST_COUNT; i++) {
        printf("%s: %s\n", test_names[i], health_scores[index][i]);
    }
}

// 운동 이름 검사 함수들
int isCardio(char ex[]) {
    for (int i = 0; i < 3; i++) {
        if (strcmp(ex, exercise_types[0][i]) == 0)
            return 1;
    }
    return 0;
}

int isCore(char ex[]) {
    for (int i = 0; i < 2; i++) {
        if (strcmp(ex, exercise_types[4][i]) == 0)
            return 1;
    }
    return 0;
}

int isValidExercise(char ex[]) {
    for (int group = 0; group < 5; group++) {
        for (int i = 0; i < 3; i++) {
            if (strcmp(ex, exercise_types[group][i]) == 0)
                return 1;
        }
    }
    return 0;
}

// 기초 운동 루틴 설정
void setExerciseRoutine() {
    char name[20];
    int memberIndex;
    int coreUsed = 0;

    printf("\n[기초 운동 루틴 설정]\n닉네임 입력: ");
    scanf("%s", name);
    memberIndex = findMemberIndex(name);

    if (memberIndex == -1) {
        printf("멤버를 찾을 수 없습니다.\n");
        return;
    }

    printf("월요일부터 토요일까지 6일간 매일 운동 루틴을 설정합니다.\n");
    printf("운동은 반드시 유산소 1개 + 근력 또는 코어 1개 포함해야 하며,\n코어 운동은 하루 1번만 가능합니다.\n");

    for (int day = 0; day < DAYS; day++) {
        char ex1[20], ex2[20];
        int valid = 0;

        while (!valid) {
            printf("%d일차 운동 2개 입력 (예: 러닝 푸시업): ", day + 1);
            scanf("%s %s", ex1, ex2);

            if (!isValidExercise(ex1) || !isValidExercise(ex2)) {
                printf("운동 이름이 잘못되었습니다. 다시 입력하세요.\n");
                continue;
            }

            if (!(isCardio(ex1) || isCardio(ex2))) {
                printf("유산소 운동을 반드시 하나 포함해야 합니다.\n");
                continue;
            }

            if ((isCore(ex1) || isCore(ex2)) && coreUsed) {
                printf("코어 운동은 하루 1번만 가능합니다.\n");
                continue;
            }

            if (isCore(ex1) || isCore(ex2)) coreUsed = 1;

            strcpy(member_routine[memberIndex][day][0], ex1);
            strcpy(member_routine[memberIndex][day][1], ex2);

            valid = 1;
        }
    }

    printf("운동 루틴이 성공적으로 저장되었습니다.\n");
}

// 기초 운동 루틴 조회
void getExerciseRoutine() {
    char name[20];
    int memberIndex;
    char *days[] = {"월", "화", "수", "목", "금", "토"};

    printf("\n[기초 운동 루틴 조회]\n닉네임 입력: ");
    scanf("%s", name);

    memberIndex = findMemberIndex(name);
    if (memberIndex == -1) {
        printf("멤버를 찾을 수 없습니다.\n");
        return;
    }

    printf("%s님의 운동 루틴:\n", name);
    for (int day = 0; day < DAYS; day++) {
        printf("%s요일: %s, %s\n", days[day],
               member_routine[memberIndex][day][0],
               member_routine[memberIndex][day][1]);
    }
}

int main() {
    char training[9] = {'U','U','U','U','U','U','U','U','U'};
    int main_choice, train_choice;
    char input;

    while (1) {
        printf("\n== 마그라테아 주 메뉴 ==\n");
        printf("1. 오디션 관리\n");
        printf("2. 훈련\n");
        printf("3. 데뷔\n");
        printf("0. 종료\n");
        printf("선택: ");
        scanf("%d", &main_choice);
        getchar();

        if (main_choice == 0) {
            printf("프로그램 종료\n");
            break;
        } else if (main_choice == 1) {
            printf("오디션 관리 (준비 중)\n");
        } else if (main_choice == 2) {
            while (1) {
                printf("\n[훈련 메뉴 상태]\n");
                for (int i = 1; i <= 8; i++) {
                    printf("%d. 훈련 %d (%c)\n", i, i, training[i]);
                }
                printf("9. 체력 상태 입력\n");
                printf("10. 체력 상태 조회\n");
                printf("11. 기초 운동 루틴 설정\n");
                printf("12. 기초 운동 루틴 조회\n");
                printf("0. 이전으로\n");
                printf("선택: ");
                scanf("%d", &train_choice);
                getchar();

                if (train_choice == 0) break;
                else if (train_choice == 9) setHealth();
                else if (train_choice == 10) getHealth();
                else if (train_choice == 11) setExerciseRoutine();
                else if (train_choice == 12) getExerciseRoutine();
                else if (train_choice >= 1 && train_choice <= 8) {
                    if (training[train_choice] == 'P') {
                        printf("이미 통과한 훈련입니다.\n");
                        continue;
                    }
                    if (train_choice == 2 && training[1] != 'P') {
                        printf("1번 훈련 먼저 필요\n");
                        continue;
                    }
                    if (train_choice >= 3 && (training[1] != 'P' || training[2] != 'P')) {
                        printf("1, 2번 훈련 먼저 필요\n");
                        continue;
                    }

                    printf("평가 입력하시겠습니까? (Y/N): ");
                    scanf(" %c", &input);
                    getchar();
                    if (input == 'Y' || input == 'y') {
                        printf("결과 입력 (P/F): ");
                        scanf(" %c", &input);
                        getchar();
                        if (input == 'P' || input == 'p') training[train_choice] = 'P';
                        else if (input == 'F' || input == 'f') training[train_choice] = 'F';
                        else printf("잘못된 입력입니다.\n");
                    }
                } else {
                    printf("잘못된 선택입니다.\n");
                }
            }
        } else if (main_choice == 3) {
            printf("데뷔 (준비 중)\n");
        } else {
            printf("잘못된 선택입니다.\n");
        }
    }
    return 0;
}