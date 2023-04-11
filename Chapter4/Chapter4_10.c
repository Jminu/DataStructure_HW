#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct StackType {
    int size;
    int top;
    element *data;
} StackType;

void InitStack(StackType *s) {
    printf("정수 배열의 크기: ");
    scanf("%d", &s->size);

    s->top = 0;
    s->data = (element *)malloc(sizeof(element));
}

void push(StackType *s, element item) {
    s->data[++(s->top)] = item;
}

element pop(StackType *s) {
    int item;
    item = s->data[(s->top)--];
    return item;
}

int main(void) {
    int pushedItem;
    StackType s;
    InitStack(&s);

    printf("정수를 입력하시오 :");
    for(int i = 0; i < s.size; i++) {
        scanf("%d", &pushedItem);
        push(&s, pushedItem);
    }

    for(int i = 0; i < s.size; i++){
        printf("%d ", pop(&s));
    }

    return 0;
}