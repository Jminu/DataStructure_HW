#include <stdio.h>
#include <stdlib.h>

typedef struct student {
    int id;
    int eng;
    int math;
} element;

typedef struct ListNode {
    element data;
    struct ListNode *link;
} ListNode;

ListNode *insert_sort(ListNode *head, element a) {
    ListNode *p = head; //현재 위치
    ListNode *q = head; //이전 위치

    ListNode *new = (ListNode *)malloc(sizeof(ListNode)); //새로운 노드

    new->data.id = a.id;
    new->data.eng = a.eng;
    new->data.math = a.math;

    if(head == NULL) { //처음 넣을 때 NULL을 가르킴(비어 있을 때)
        head = new;
        new->link = NULL;

        return head;
    }
    else { //처음 넣는거 아닐 때
        while(1) {
            if(p == NULL) { //연결리스트의 끝에 도착하면
                q->link = new;
                new->link = NULL;

                return head;
            }

            if(p->data.id > new->data.id) { //새로운 노드보다 큰 현재 노드를 발견 -> 이전 노드에 이어 붙임
                if(head->data.id > new->data.id) { //새로운 노드를 맨 앞에 삽입해야할 때
                    new->link = head;
                    head = new;

                    return head;
                }
                else { //중간에 삽입 해야할 때
                    new->link = q->link;
                    q->link = new;

                    return head;
                }
            }
            else { //새로운 노드id보다 p노드가 작다면, p와 q를 이동
                q = p; //q는 p를 따라가고
                p = p->link; //p는 전진
            }
        }
    }
}

int main(void) {
    element a[5] = {
            {134, 88, 65},
            {125, 95, 90},
            {145, 70, 55},
            {128, 75, 50},
            {129, 60, 60}
    };

    ListNode *head = NULL;

    for(int i = 0; i < 5; i++) {
        head = insert_sort(head, a[i]);
    }

    for(ListNode *p = head; p != NULL; p = p->link){
        printf("id : %d eng : %d math : %d \n", p->data.id, p->data.eng, p->data.math);
    }

    return 0;
}