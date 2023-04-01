/*
 * 2291048 진민우 과제1
 * 3번 문제
 * */
#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 100

typedef struct {
    float coef; //계수
    int expon; //지수
} polynomial;

polynomial terms[MAX_TERMS] = {
        {8,  3},
        {7,  1},
        {1,  0},
        {10, 3},
        {3,  2},
        {1,  0}
};

char compare(int a, int b) {
    if (a > b) {
        return '>';
    } else if (a == b) {
        return '=';
    } else {
        return '<';
    }
}

void AttachToResult(float coef, int expon, int *avail) { //avail을 포인터로 받음
    if (*avail > MAX_TERMS) {
        printf("항의 개수가 많습니다.\n");
        exit(1);
    }
    terms[*avail].coef = coef; //*avail사용 -> 원본 수정
    terms[*avail].expon = expon;
    (*avail)++; //여기서 avail을 증가시켜도 main함수에 있던 avail이 증가한다.
}

void AddPoly(int As, int Ae, int Bs, int Be, int *Cs, int *Ce, int *avail) {
    float tempcoef = 0;
    *Cs = *avail;

    while (As <= Ae && Bs <= Be) {
        switch (compare(terms[As].expon, terms[Bs].expon)) {
            case '>':
                AttachToResult(terms[As].coef, terms[As].expon, avail);
                As++;
                break;
            case '=':
                tempcoef = terms[As].coef + terms[Bs].coef;
                if(tempcoef) { //tempcoef가 0이 아니면
                    AttachToResult(tempcoef, terms[As].expon, avail);
                }
                As++;
                Bs++;
                break;
            case '<':
                AttachToResult(terms[Bs].coef, terms[Bs].expon, avail);
                Bs++;
                break;
        }
    }

    //남은 나머지 항 이동
    for(; As <= Ae; As++) {
        AttachToResult(terms[As].coef, terms[As].expon, *avail);
    }
    for(; Bs <= Be; Bs++) {
        AttachToResult(terms[Bs].coef, terms[Bs].expon, *avail);
    }
    *Ce = *avail - 1;
}

void PrintPoly(int start, int end) {
    for(int i = start; i < end; i++) {
        printf("%3.1fx^%d + ", terms[i].coef, terms[i].expon);
    }
    printf("%3.1fx^%d\n", terms[end].coef, terms[end].expon);
}

int main(void) {
    int As = 0;
    int Ae = 2;
    int Bs = 3;
    int Be = 5;
    int Cs;
    int Ce;

    int avail = Ae + Bs + 1; //avail변수를 지역변수로 변경

    PrintPoly(As, Ae);
    PrintPoly(Bs, Be);
    AddPoly(As, Ae, Bs, Be, &Cs, &Ce, &avail); //avail을 포인터로 받음(원본수정)
    printf("--------------------------------\n");
    PrintPoly(Cs, Ce);

    return 0;
}