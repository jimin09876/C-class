#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_TRAINEES 8
#define MAX_NAME_LEN 20
#define MAX_TRAUMA_LEN 100
#define MAX_ANSWER_LEN 100
#define MAX_SESSIONS 24
#define MAX_QUESTIONS 5

// 구조체 정의

typedef struct {
    char nickname[MAX_NAME_LEN];
    int ability;
} Trainee;

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int menteeNum;
} Mentor;

typedef struct {
    char nickname[MAX_NAME_LEN];
    int age;
    char trauma[MAX_TRAUMA_LEN];
} TraumaInfo;

typedef struct {
    int id;
    char content[150];
} CounselQuestion;

typedef struct {
    char nickname[MAX_NAME_LEN];
    char question[150];
    char answer[MAX_ANSWER_LEN + 1];
} CounselSession;

typedef struct {
    char keyword[10];
    char message[500];
} EasterEgg;

// 전역 변수
Trainee trainees[MAX_TRAINEES];
Mentor mentors[MAX_TRAINEES];
TraumaInfo traumaMembers[MAX_TRAINEES];
CounselQuestion questions[MAX_QUESTIONS] = {
    {1, "어떤 상황에서 그 트라우마를 경험하셨나요?"},
    {2, "해당 상황이 어떻게 당신의 일상생활과 감정에 어떤 영향을 미치고 있는지 말씀해주세요."},
    {3, "이 트라우마를 어떻게 극복하려고 노력하셨나요?"},
    {4, "트라우마와 관련하여 어떤 감정을 느끼고 계신가요?"},
    {5, "트라우마를 극복하기 위해 어떤 지원이 필요한 것으로 생각하시나요?"}
};
CounselSession sessions[MAX_SESSIONS];
int sessionCount = 0;

EasterEgg egg = {
    "specter",
    "나는 고백한다. 대학 졸업 후 스타트업 창업이라는 허세에 빠져 치기 어린 행동으로 친구들의 앞길을 막았다. 나는 나의 아이디어가 설득되는 사람이 나 뿐일 때 파괴적인 결과를 보게 된다는 것을 뼈저리게 경험했다. 과거의 아서는 독선과 아집의 망령이다."
};

// 함수 정의
int parseIntMember(char *nickname) {
    int sum = 0;
    for (int i = 0; nickname[i]; i++) sum += nickname[i];
    return sum;
}

int getRandomAbility() {
    return rand() % 901 + 100;
}

void initTrainees() {
    char *names[MAX_TRAINEES] = {"Zeta", "Orion", "Lyra", "Nova", "Vega", "Sirius", "Luna", "Mira"};
    for (int i = 0; i < MAX_TRAINEES; i++) {
        strcpy(trainees[i].nickname, names[i]);
        trainees[i].ability = getRandomAbility();
    }
}

void inputMentors() {
    for (int i = 0; i < MAX_TRAINEES; i++) {
        printf("멘토 #%d 이름 입력: ", i + 1);
        scanf("%s", mentors[i].name);
        mentors[i].id = i + 1;
        mentors[i].menteeNum = -1;
    }
}

void matchMentoring() {
    printf("\n[멘토링 매칭 결과]\n");
    for (int i = 0; i < MAX_TRAINEES; i++) {
        int id = parseIntMember(trainees[i].nickname) % MAX_TRAINEES + 1;
        for (int j = 0; j < MAX_TRAINEES; j++) {
            if (mentors[j].id == id) {
                mentors[j].menteeNum = i;
                printf("연습생 %s - 멘토 %s(ID: %d)\n", trainees[i].nickname, mentors[j].name, mentors[j].id);
                break;
            }
        }
    }
}

void inputTrauma() {
    char name[MAX_NAME_LEN];
    while (1) {
        printf("닉네임 입력 (0 입력 시 종료): ");
        scanf("%s", name);
        if (strcmp(name, "0") == 0) break;

        int found = 0;
        for (int i = 0; i < MAX_TRAINEES; i++) {
            found = strcmp(name, trainees[i].nickname) == 0 ? 1 : found;
            if (found) {
                strcpy(traumaMembers[i].nickname, name);
                printf("나이 입력: ");
                scanf("%d", &traumaMembers[i].age);
                printf("트라우마 내용 입력: ");
                scanf(" %[^"]s", traumaMembers[i].trauma);
                break;
            }
        }
        found ? printf("입력 완료\n") : printf("존재하지 않는 닉네임입니다. 다시 입력하세요.\n");
    }
}

void startCounseling() {
    printf("\n[상담 가능한 연습생 목록]\n");
    for (int i = 0; i < MAX_TRAINEES; i++) {
        if (strlen(traumaMembers[i].trauma) > 0)
            printf("- %s\n", traumaMembers[i].nickname);
    }

    char name[MAX_NAME_LEN];
    printf("상담할 닉네임 선택: ");
    scanf("%s", name);

    for (int i = 0; i < 3 && sessionCount < MAX_SESSIONS; i++) {
        int qIndex = rand() % MAX_QUESTIONS;
        printf("Q%d: %s\n", i + 1, questions[qIndex].content);
        printf("답변 입력: ");
        char answer[MAX_ANSWER_LEN + 1];
        while (1) {
            fgets(answer, sizeof(answer), stdin);
            if (strlen(answer) > 1 && strlen(answer) <= MAX_ANSWER_LEN) break;
            printf("답변이 비어있거나 너무 깁니다. 다시 입력해주세요.\n");
        }
        strcpy(sessions[sessionCount].nickname, name);
        strcpy(sessions[sessionCount].question, questions[qIndex].content);
        strcpy(sessions[sessionCount].answer, answer);
        sessionCount++;
    }
}

void viewSessionResults() {
    char name[MAX_NAME_LEN];
    printf("답변 확인할 닉네임 입력: ");
    scanf("%s", name);

    for (int i = 0; i < MAX_TRAINEES; i++) {
        if (strcmp(traumaMembers[i].nickname, name) == 0) {
            printf("\n닉네임: %s\n나이: %d\n트라우마: %s\n", traumaMembers[i].nickname, traumaMembers[i].age, traumaMembers[i].trauma);
            break;
        }
    }

    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessions[i].nickname, name) == 0) {
            printf("Q: %s\nA: %s\n", sessions[i].question, sessions[i].answer);
        }
    }
}

void printReverseBinary() {
    printf("<<아서의 이스터에그>>\n");
    for (int i = strlen(egg.keyword) - 1; i >= 0; i--) {
        unsigned char ch = egg.keyword[i];
        for (int j = 7; j >= 0; j--) {
            printf("%d", (ch >> j) & 1);
        }
        printf(" ");
    }
    printf("\n");
}

bool isRightChar(char *input) {
    return strcmp(input, egg.keyword) == 0;
}

bool isEasterEgg(char *word) {
    return strcmp(word, egg.keyword) == 0;
}

void find_easter_egg() {
    printReverseBinary();
    char guess[10];
    while (1) {
        printf("위 이진수 문자 입력: ");
        scanf("%s", guess);
        if (isRightChar(guess)) {
            char word[10];
            printf("단어 조합 입력: ");
            scanf("%s", word);
            if (isEasterEgg(word)) {
                printf("##이스터에그 발견!$$\n%s\n", egg.message);
            } else {
                printf("틀렸습니다. 하위 메뉴로 돌아갑니다.\n");
            }
            break;
        } else {
            printf("문자 오류. 다시 시도.\n");
        }
    }
}

void traumaMenu() {
    char input[20];
    while (1) {
        printf("\n[B. 트라우마 관리]\n a. 트라우마 입력\n b. 상담 시작\n c. 상담 확인\n 0. 이전\n선택 (또는 Arthur 입력): ");
        scanf("%s", input);

        if (strcasecmp(input, "0") == 0) return;
        if (strcasecmp(input, "Arthur") == 0) {
            find_easter_egg();
            continue;
        }

        char sel = toupper(input[0]);
        if (sel == 'A') inputTrauma();
        else if (sel == 'B') startCounseling();
        else if (sel == 'C') viewSessionResults();
        else printf("잘못된 선택입니다.\n");
    }
}

void mainMenu() {
    char input[20];
    while (1) {
        printf("\n[II. 훈련]\n 1. 멘토링\n 2. 자기관리와 팀워크\n 0. 종료\n선택: ");
        scanf("%s", input);

        char sel = toupper(input[0]);
        if (sel == '0') break;
        else if (sel == '1') {
            initTrainees();
            inputMentors();
            matchMentoring();
        } else if (sel == '2') traumaMenu();
        else printf("잘못된 입력입니다.\n");
    }
}

int main() {
    srand(time(NULL));
    mainMenu();
    return 0;
}

