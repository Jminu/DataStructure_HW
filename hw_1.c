/*
 * 자료구조 과제 2291048 진민우
 * 1번 문제 중 (1), (2)
 * 앙 버전 1
 **/

#include <stdio.h>
#include <math.h>

//학생 구조체
typedef struct student {
    int id;
    double eng;
    double math;
} student;

//수학 평균
double MathEverage(student s[]) {
    int sum = 0;
    for (int i = 0; i < 10; i++) {
        sum += s[i].math; //수학 점수의 누적합
    }
    return sum / 10; //10명으로 나누면 평균
}

//영어 평균
double EngEverage(student s[]) {
    int sum = 0;
    for (int i = 0; i < 10; i++) {
        sum += s[i].eng; //영어 점수의 누적합
    }
    return sum / 10; //10명으로 나누면 평균
}

//영어 표준 편차
double EngStdDeviation(student s[]) {
    int sum = 0;
    double result = 0;
    for (int i = 0; i < 10; i++) {
        sum += pow((s[i].eng - EngEverage(s)), 2); //(영어점수 - 영어평균)을 제곱한 것을 누적합
    }
    result = sqrt(sum / 9); //제곱근 구하기

    return result;
}

//수학 표준 편차
double MathStdDeviation(student s[]) {
    int sum = 0;
    double result = 0;
    for (int i = 0; i < 10; i++) {
        sum += pow((s[i].math - MathEverage(s)), 2); //(수학점수 - 수학평균)을 제곱한 것을 누적합
    }
    result = sqrt(sum / 9); //제곱근 구하기

    return result;
}

//수학 최고점 출력
void PrintMathHighScore(student s[]) {
    double highScore = 0;
    int highId = 0;
    for (int i = 0; i < 10; i++) { //최고점 찾는 알고리즘
        if (highScore < s[i].math) {
            highScore = s[i].math;
            highId = s[i].id;
        }
    }
    printf("수학 최고점 : %lf 학번 : %d\n", highScore, highId);
}

//영어 최고점 출력
void PrintEngHighScore(student s[]) {
    double highScore = 0;
    int highId = 0;
    for (int i = 0; i < 10; i++) { //최고점 찾는 알고리즘
        if (highScore < s[i].eng) {
            highScore = s[i].eng;
            highId = s[i].id;
        }
    }
    printf("영어 최고점 : %lf 학번 : %d\n", highScore, highId);
}

//특정 학생의 수학 등수
int ShowMathRank(student entireStudent[], student searchStudent) {
    int rank = 1;
    for(int i = 0; i < 10; i++) {
        if(searchStudent.math < entireStudent[i].math) { //자신보다 높은 점수 있으면, rank++
            rank++;
        }
    }
    return rank;
}

//특정 학생의 영어 등수
int ShowEngRank(student entireStudent[], student searchStudent) {
    int rank = 1;
    for(int i = 0; i < 10; i++) {
        if(searchStudent.eng < entireStudent[i].eng) { //자신보다 높은 점수 있으면, rank++
            rank++;
        }
    }
    return rank;
}

int main(void) {
    int searchId = 0; //찾을 학번
    int rank; //등수

    //학생들 정보 저장
    student s[10] = {
            {1234, 78, 87},
            {1235, 65, 55},
            {1365, 88, 95},
            {2546, 45, 56},
            {3124, 58, 88},
            {1976, 71, 54},
            {1657, 32, 55},
            {2547, 90, 43},
            {2456, 66, 78},
            {1765, 54, 99}
    };

    printf("수학 평균 : %lf  영어 표준 편차 : %lf\n", MathEverage(s), MathStdDeviation(s)); //평균, 표준편차 출력
    printf("영어 평균 : %lf  수학 표준 편차 : %lf\n", EngEverage(s), EngStdDeviation(s)); //평균, 표준편차 출력
    printf("==========================================\n");

    PrintEngHighScore(s); //영어 최고점자 출력
    PrintMathHighScore(s); //수학 최고점자 출력
    printf("==========================================\n");

    printf("학번을 입력해주세요 : ");
    scanf("%d", &searchId); //찾는 학번 입력

    for (int i = 0; i < 10; i++) {
        if (s[i].id == searchId) {
            printf("수학 성적 : %lf  영어 성적 : %lf\n", s[i].math, s[i].eng);
            rank = ShowMathRank(s, s[i]);
            printf("수학 등수 : %d ", rank);
            rank = ShowEngRank(s, s[i]);
            printf("영어 등수 : %d\n", rank);
        }
    }
    return 0;
}
