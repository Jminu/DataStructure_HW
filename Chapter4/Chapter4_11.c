#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 100
typedef struct StackType {
    int top;
    char data[MAX_STACK];
} StackType;

void InitStack(StackType *s) {
    s->top = 0;
}

int IsFull(StackType *s) {
    if(s->top == MAX_STACK - 1)
        return 1;
    else
        return 0;
}

int IsEmpty(StackType *s) {
    if(s->top == 0)
        return 1;
    else
        return 0;
}

void push(StackType *s, char item) {
    if(IsFull(s) == 1) {
        exit(1);
    }
    s->data[++(s->top)] = item;
}

char pop(StackType *s) {
    char item;
    if(IsEmpty(s) == 1) {
        exit(1);
    }
    item = s->data[(s->top)--];
    return item;
}

int CheckMatching(const char *string) {
    StackType s;
    InitStack(&s);
    int length = strlen(string);
    char ch;
    char openCh;

    StackType countStack;
    InitStack(&countStack);
    char count = 0;

    for(int i = 0; i < length; i++) {
        ch = string[i];
        switch (ch) {
            case '(':
                push(&s, ch);
                push(&countStack, ++count);
                printf("%d ", count);
                break;
            case ')':
                if(IsEmpty(&s) == 1) {
                    return 0;
                }
                openCh = pop(&s);
                printf("%c ", pop(&countStack) + 48);
                if(openCh != '(') {
                    return 0;
                }
                break;
        }
    }
    if(IsEmpty(&s) == 0) {
        return 0;
    }
    return 1;
}

int main(void) {
    char string[100];
    printf("수식 : ");
    scanf("%s", string);

    if(CheckMatching(string) == 1) {
        printf("괄호 검사 성공\n");
    }
    else {
        printf("괄호 검사 실패\n");
    }
    return 0;
}