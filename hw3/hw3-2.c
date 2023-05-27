#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct QueueNode {
    element data;
    struct QueueNode *link;
} QueueNode;

typedef struct LinkedListQueue {
    struct QueueNode *head;
    struct QueueNode *tail;
    struct LinkedListQueue *link;
} LinkedListQueue;

typedef struct LinkedListType {
    LinkedListQueue *head;
    int length;
} LinkedListType;

void init(LinkedListType *list) { //LinkedListType 초기화
    list->head = NULL;
    list->length = 0;
}

void init_queue(LinkedListType *list, int line) { //list의 head가 가리키는 연결리스트에는 노드 line개
    list->length = line;
    LinkedListQueue *p;

    for (int i = 0; i < list->length; i++) {
        if (list->head == NULL) { //처음
            LinkedListQueue *new = (LinkedListQueue *) malloc(sizeof(LinkedListQueue));
            list->head = new;
            p = new;
            new->link = NULL;
            new->head = NULL;
            new->tail = NULL;
        } else {
            LinkedListQueue *new = (LinkedListQueue *) malloc(sizeof(LinkedListQueue));
            p->link = new;
            p = new;
            p->link = NULL;
            new->head = NULL;
            new->tail = NULL;
        }
    }
}

void add_queue(LinkedListQueue *list, int pos, element value) {
    QueueNode *new = (QueueNode *) malloc(sizeof(QueueNode));
    LinkedListQueue *insertPos = list->head;

    for (int i = 0; i < pos; i++) { //삽입할 위치로 이동
        insertPos = insertPos->link;
    }

    if (insertPos->head == NULL) { //삽입할 위치에 처음 삽입 하는 것이라면
        insertPos->head = new;
        insertPos->tail = new;
        new->data = value;
        new->link = NULL;
    } else {
        insertPos->tail->link = new;
        insertPos->tail = new;
        new->data = value;
        new->link = NULL;
    }
}

void delete_queue(LinkedListQueue *list, int pos) {
    LinkedListQueue *deletePos = list->head;
    QueueNode *removed = NULL;

    for (int i = 0; i < pos; i++) { //삭제할 위치로 이동
        deletePos = deletePos->link;
    }

    if (deletePos->head == NULL) { //삭제할 큐에 노드가 하나도 없다면
        printf("Empty! You can't delete\n");
        return;
    } else {
        removed = deletePos->head; //맨 앞에 노드 삭제
        deletePos->head = removed->link;
        free(removed);
    }
}

void display_data(LinkedListType *list) {
    LinkedListQueue *p = list->head;
    QueueNode *pNode = NULL;

    while (p != NULL) {
        pNode = p->head;
        while (pNode != NULL) {
            printf("%d | ", pNode->data);
            pNode = pNode->link;
        }
        printf("\n");
        p = p->link;
    }
}

int main(void) {
    LinkedListType list1;
    init(&list1);

    int line;
    printf("how many lines? : ");
    scanf("%d", &line);
    init_queue(&list1, line);

    add_queue(&list1, 0, 1);
    add_queue(&list1, 0, 2);
    add_queue(&list1, 0, 3);

    add_queue(&list1, 1, 11);
    add_queue(&list1, 1, 22);
    add_queue(&list1, 1, 33);

    add_queue(&list1, 2, 111);
    add_queue(&list1, 2, 222);
    add_queue(&list1, 2, 333);

    display_data(&list1);

    printf("삭제 후\n");

    delete_queue(&list1, 0);
    delete_queue(&list1, 1);
    display_data(&list1);

    return 0;
}