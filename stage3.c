#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h> // for sleep

#define MAX_QUESTIONS 10
#define QUIZ_COUNT 5
#define SCORE_PER_QUESTION 20
#define STUDENT_COUNT 4

// 문제은행 구조체
typedef struct {
    int id;
    char question[100];
    char answer[100];
} KoreanQuiz;

// 연습생 구조체
typedef struct {
    char name[30];
    char nickname[30];
    char nationality[20];
    int score;
    char passed;
} Trainee;

// 퀴즈 답안 구조체
typedef struct {
    int questionId;
    char correct;
} QuizResult;

// 문제은행 초기화
typedef struct {
    KoreanQuiz quizList[MAX_QUESTIONS];
    int count;
} QuizBank;

QuizBank initQuizBank() {
    QuizBank bank;
    bank.count = MAX_QUESTIONS;
    strcpy(bank.quizList[0].question, "What is 'hello' in Korean?");
    strcpy(bank.quizList[0].answer, "안녕하세요");
    strcpy(bank.quizList[1].question, "What is 'thank you' in Korean?");
    strcpy(bank.quizList[1].answer, "감사합니다");
    strcpy(bank.quizList[2].question, "What is 'love' in Korean?");
    strcpy(bank.quizList[2].answer, "사랑");
    strcpy(bank.quizList[3].question, "What is 'school' in Korean?");
    strcpy(bank.quizList[3].answer, "학교");
    strcpy(bank.quizList[4].question, "What is 'friend' in Korean?");
    strcpy(bank.quizList[4].answer, "친구");
    strcpy(bank.quizList[5].question, "What is 'food' in Korean?");
    strcpy(bank.quizList[5].answer, "음식");
    strcpy(bank.quizList[6].question, "What is 'water' in Korean?");
    strcpy(bank.quizList[6].answer, "물");
    strcpy(bank.quizList[7].question, "What is 'goodbye' in Korean?");
    strcpy(bank.quizList[7].answer, "안녕히 계세요");
    strcpy(bank.quizList[8].question, "What is 'sorry' in Korean?");
    strcpy(bank.quizList[8].answer, "죄송합니다");
    strcpy(bank.quizList[9].question, "What is 'book' in Korean?");
    strcpy(bank.quizList[9].answer, "책");
    for (int i = 0; i < MAX_QUESTIONS; i++) {
        bank.quizList[i].id = i;
    }
    return bank;
}

// 연습생 초기화
void initTrainees(Trainee* trainees) {
    strcpy(trainees[0].name, "지연"); strcpy(trainees[0].nickname, "jiypark"); strcpy(trainees[0].nationality, "Korea");
    strcpy(trainees[1].name, "리오"); strcpy(trainees[1].nickname, "leo"); strcpy(trainees[1].nationality, "USA");
    strcpy(trainees[2].name, "루카스"); strcpy(trainees[2].nickname, "lucas"); strcpy(trainees[2].nationality, "Canada");
    strcpy(trainees[3].name, "에이미"); strcpy(trainees[3].nickname, "amy"); strcpy(trainees[3].nationality, "UK");
    for (int i = 0; i < STUDENT_COUNT; i++) {
        trainees[i].score = 0;
        trainees[i].passed = 'X';
    }
}

// 정답 여부 확인 함수
char isAnswer(KoreanQuiz* q, int id, char* userInput) {
    return strcmp(q[id].answer, userInput) == 0 ? 'O' : 'X';
}

// 퀴즈 실행자 선택
int selectRandomTakers(Trainee* trainees) {
    time_t t;
    srand((unsigned) time(&t));
    int index;
    while (1) {
        index = rand() % STUDENT_COUNT;
        if (strcmp(trainees[index].nationality, "Korea") != 0) {
            printf("{%s}님, 한국어 퀴즈 세션에 오신 걸 환영합니다!\n", trainees[index].name);
            return index;
        }
    }
}

// 퀴즈 문제 출제
void serveRandomQuiz(QuizBank* bank, Trainee* trainee) {
    int selected[QUIZ_COUNT] = {-1};
    QuizResult results[QUIZ_COUNT];
    int used[MAX_QUESTIONS] = {0};
    int score = 0;
    printf("30초 후 퀴즈가 시작됩니다. 준비하세요...\n");
    sleep(2); // 테스트용으로 실제는 sleep(30)

    srand(time(NULL));
    for (int i = 0; i < QUIZ_COUNT; ) {
        int q = rand() % MAX_QUESTIONS;
        if (used[q] == 0) {
            used[q] = 1;
            selected[i] = q;
            printf("\n문제 %d: %s\n", i + 1, bank->quizList[q].question);
            char userInput[100];
            printf("답변 입력: ");
            fgets(userInput, sizeof(userInput), stdin);
            userInput[strcspn(userInput, "\n")] = '\0';

            char result = (strlen(userInput) == 0 || strlen(userInput) > 100) ? 'X' : isAnswer(bank->quizList, q, userInput);
            results[i].questionId = q;
            results[i].correct = result;
            if (result == 'O') score += SCORE_PER_QUESTION;
            i++;
        }
    }

    trainee->score = score;
    trainee->passed = (score >= 80) ? 'O' : 'X';

    printf("\n퀴즈 종료!\n정답지:\n");
    for (int i = 0; i < QUIZ_COUNT; i++) {
        printf("문제 %d - %s\n", bank->quizList[results[i].questionId].question, results[i].correct == 'O' ? "정답" : "오답");
    }
    printf("총점: %d점\n합격 여부: %c\n", trainee->score, trainee->passed);
}

void testKoreanLang() {
    Trainee trainees[STUDENT_COUNT];
    initTrainees(trainees);
    QuizBank bank = initQuizBank();
    int takerIndex = selectRandomTakers(trainees);
    serveRandomQuiz(&bank, &trainees[takerIndex]);
}

int main() {
    char menu;
    printf("[II. 훈련 > 3. 언어 및 발음 훈련]\n");
    printf("A. 한국어 퀴즈\n0. 종료\n");
    printf("메뉴를 선택하세요: ");
    scanf(" %c", &menu);
    getchar();
    if (toupper(menu) == 'A') {
        testKoreanLang();
    } else if (menu == '0') {
        printf("프로그램 종료\n");
    }
    return 0;
}
