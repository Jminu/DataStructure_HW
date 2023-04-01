/*
 * 2291048 진민우
 * 2번 문제
 */

#include <stdio.h>
#define MAX_DEGREE 100

typedef struct {
    int degree; //차수
    float coef[MAX_DEGREE]; //계수
}polynomial;

polynomial AddPolynomial(polynomial A, polynomial B) {
    polynomial C;
    int Apos = 0;
    int Bpos = 0;
    int Cpos = 0;

    int degreeA = A.degree; //A의 차수
    int degreeB = B.degree; //B의 차수
    int degreeC;

    if(degreeA > degreeB) { //A다항식의 차수가 더 높을 때
        C.degree = degreeA;
    }
    else{ //B다항식의 차수가 더 높거나 같을 때
        C.degree = degreeB;
    }

    while(Apos <= A.degree && Bpos <= B.degree) { //A나 B의 차수를 넘을 수 없다
        if(degreeA > degreeB) { //만약 A의 차수가 더 높다면
            C.coef[Cpos++] = A.coef[Apos++];
            degreeA--; //A의 차수 감소
        }
        else if(degreeA == degreeB) { //만약 A와 B의 차수가 같다면
            C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
            degreeA--; //A의 차수 감소
            degreeB--; //B의 차수 감수
        }
        else { //만약 B의 차수가 더 높다면
            C.coef[Cpos++] = B.coef[Bpos++];
            degreeB--; //B의 차수 감소
        }
    }
    return C;
}

void PrintPolynomial(polynomial p) {
    for(int i = p.degree; i > 0; i--) {
        if(p.coef[p.degree - i] == 0) { //계수가 0이면 출력안함
            continue; //건너뜀
        }
        printf("%3.1fx^%d + ", p.coef[p.degree - i], i);
    }
    printf("%3.1f\n", p.coef[p.degree]);
}

int main(void) {
    polynomial a = {5, {10, 0, 0, 0, 5, 1}};
    polynomial b = {5, {-10, 0, 0, 3, 0, 3}};
    polynomial c;

    c = AddPolynomial(a, b);
    PrintPolynomial(c);

    return 0;
}
