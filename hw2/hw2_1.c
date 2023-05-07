#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef char element;
typedef struct StackType {
    element data[MAX_SIZE];
    int top;
} StackType;

void InitStack(StackType *s) {
    int top = -1;
}

int IsEmpty(StackType *s) {
    if(s->top == -1)
        return 1;
    else
        return 0;
}

int IsFull(StackType *s) {
    if(s->top == MAX_SIZE - 1)
        return 1;
    else
        return 0;
}

void push(StackType *s, element value) {
    if(IsFull(s) == 1)
        printf("Full\n");
    else {
        s->data[++(s->top)] = value;
    }
}

element pop(StackType *s) {
    element value;
    if(IsEmpty(s) == 1)
        printf("Empty\n");
    else{
        value = s->data[(s->top)--];
        return value;
    }
}

element peek(StackType *s) {
    if(IsEmpty(s) == 1)
        printf("Empty\n");
    else
        return s->data[s->top];
}

//연산자 우선순위
int prec(char op) {
    switch (op) {
        case '(':
        case ')':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
    }
    return -1;
}

//중위 -> 후위
char *InfixToPostfix (char infix[]) {
    char *postfix = (char *)malloc(sizeof(MAX_SIZE)); //동적할당(힙) 안하고 배열로만들면, 함수끝나면 사라짐(스택이라)
    int j = 0;

    StackType s;
    InitStack(&s);

    char ch;
    char top_op;
    int len = strlen(infix);

    for(int i = 0; i < len; i++) {
        ch = infix[i];
        switch (ch) {
            case '+':
            case '-':
            case '*':
            case '/':
                while(!IsEmpty(&s) && (prec(ch) <= prec(peek(&s)))) { //들어있는게 더 크면
                    postfix[j] = pop(&s);
                    j++;
                }
                push(&s, ch); //그리고 새로 들어오는 연산자 push
                break;
            case '(':
                push(&s, ch);
                break;
            case ')':
                top_op = pop(&s);
                while(top_op != '(') { //왼쪽 괄호 나올 때까지
                    postfix[j] = top_op;
                    top_op = pop(&s);
                    j++;
                }
                break;
            default: //피연산자이면
                postfix[j] = ch;
                j++;
                break;
        }
    }
    //남아있는 연산자 스택에서 다 pop
    while(!IsEmpty(&s)){
        postfix[j] = pop(&s);
        j++;
    }
    postfix[j] = '\0'; //후위표기식 마지막에 NULL삽입해서 끝

    return postfix; //문자열을 가리키는 포인터 반환
}

//후위표기식 계산
int EvalPostfix (char postfix[]) {
    int op1;
    int op2;
    int value;

    int len = strlen(postfix);
    char ch;

    StackType s;
    InitStack(&s);
    for(int i = 0; i < len; i++) {
        ch = postfix[i];
        if(ch != '+' && ch != '-'&& ch != '*' && ch != '/') {
            value = ch - '0';
            push(&s, value);
        }
        else {
            op2 = pop(&s);
            op1 = pop(&s);
            switch (ch) {
                case '+':
                    push(&s, op1 + op2);
                    break;
                case '-':
                    push(&s, op1 - op2);
                    break;
                case '*':
                    push(&s, op1 * op2);
                    break;
                case '/':
                    push(&s, op1 / op2);
                    break;
            }
        }
    }
    return pop(&s);
}

int main(void) {
    char infixFormula[MAX_SIZE];
    char *postfix;

    printf("중위 표기식 입력 : ");
    scanf("%s", infixFormula);

    postfix = InfixToPostfix(infixFormula);
    printf("%s\n", postfix);

    printf("답 : %d\n", EvalPostfix(postfix));
    free(postfix);

    return 0;
}