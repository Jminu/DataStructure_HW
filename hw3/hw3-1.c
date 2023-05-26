#include <stdio.h>
#include <stdlib.h>

typedef struct  {
    int row; //행번호
    int col; //열번호
    int value; //값
} element;

typedef struct ListNode {
    element data;
    struct ListNode *link;
} ListNode;

typedef struct {
    int rows;
    int cols;
    ListNode *head;
    ListNode *tail;
} ListHeader;

void init(ListHeader *plist, int r, int c) {
    plist->rows = r; //행 갯수
    plist->cols = c; //열 갯수
    plist->head = NULL;
    plist->tail = NULL;
}

void print_matrix(ListHeader *plist) {
    ListNode *p = plist->head;
    while(p != NULL) {
        printf("%d %d %d\n", p->data.row, p->data.col, p->data.value);
        p = p->link;
    }
    printf("=======\n");
}

void insert_node_last(ListHeader *list, element x) {
    ListNode *new = (ListNode *)malloc(sizeof(ListNode));

    new->data.row = x.row;
    new->data.col = x.col;
    new->data.value = x.value;

    if(list->head == NULL) {
        list->head = new;
        new->link = NULL;
        list->tail = new;
    }
    else {
        list->tail->link = new;
        new->link = NULL;
        list->tail = new;
    }
}

ListHeader *AddMatrix(ListHeader *a, ListHeader *b) {
    ListNode *newhead = NULL;
    ListNode *pre = NULL;
    ListNode *pa = a->head;
    ListNode *pb = b->head;

    /*처음에 A의 희소행렬을 모두 복사한다. 그리고 그 희소행렬 연결리스트를 newhead로 가리킨다.*/
    while(pa != NULL) {
        ListNode *new = (ListNode *)malloc(sizeof(ListNode));

        new->data.row = pa->data.row;
        new->data.col = pa->data.col;
        new->data.value = pa->data.value;

        if(newhead == NULL) {
            newhead = new;
            new->link = NULL;
            pre = new;
        }
        else {
            pre->link = new;
            new->link = NULL;
            pre = new;
        }
        pa = pa->link;
    }

    while(pb != NULL) {
        pa = newhead;
        pre = newhead;

        ListNode *new = (ListNode *)malloc(sizeof(ListNode));

        new->data.row = pb->data.row;
        new->data.col = pb->data.col;
        new->data.value = pb->data.value;

        while(pa != NULL) {
            if(new->data.row == pa->data.row) { //만약 새로운 노드의 행이 같다면
                if(new->data.col < pa->data.col) { //새로운 노드의 열이 작다면
                    new->link = pre->link;
                    pre->link = new;
                    break;
                }
                else if(new->data.col == pa->data.col) { //열도 같다면
                    pa->data.value += new->data.value;
                    break;
                }
                else { //새로운 노드의 열이 크다면
                    pre = pa;
                    pa = pa->link;
                }
            }
            else if(new->data.row < pa->data.row) { //새로운 노드의 행이 작다면
                if(new->data.row < newhead->data.row) { //맨 앞에 삽입하는 경우
                    new->link = newhead;
                    newhead = new;
                    break;
                }
                else { //중간에 삽입하는경우
                    new->link = pre->link;
                    pre->link = new;
                    break;
                }
            }
            else { //새로운 노드의 행이 크다 : 전진
                pre = pa;
                pa = pa->link;
            }
        }
        if(pa == NULL) { //마지막에 도착하면 이어 붙임
            pre->link = new;
            pa = new;
            pa->link = NULL;
        }
        pb = pb->link;
    }

    ListHeader *result = (ListHeader *)malloc(sizeof(ListHeader));
    result->rows = a->rows;
    result->cols = a->cols;
    result->head = newhead;
    ListNode *tail = result->head;
    while(tail->link != NULL) {
        tail = tail->link;
    }
    result->tail = tail;

    return result;
}

int main(void) {
    ListHeader A;
    ListHeader B;
    ListHeader *C; //합을 저장

    init(&A, 3, 4);
    init(&B, 3, 4);
    init(&C, 3, 4); //두 행렬의 합 저장

    element Adata[4] = {
            {0, 0, 2},
            {0, 3, 1},
            {1, 1, 3},
            {2, 0, -2}
    };

    element Bdata[4] = {
            {0, 2, 4},
            {0, 3, -1},
            {2, 2, 1},
            {2, 3, -1}
    };
    printf("행 열 값\n");

    //순서를 지켜서 입력
    for(int i = 0; i < 4; i++) {
        insert_node_last(&A, Adata[i]);
    }
    printf("A = \n");
    print_matrix(&A);

    for(int i = 0; i < 4; i++) {
        insert_node_last(&B, Bdata[i]);
    }
    printf("B = \n");
    print_matrix(&B);

    C = AddMatrix(&A, &B);
    printf("A + B = \n");
    print_matrix(C);

    return 0;
}