#include <stdio.h>
#define MAX_TERMS 100

typedef struct {
    int row; //행
    int col; //열
    int value; //값
} element;

typedef struct {
    element data[MAX_TERMS];

    int rows; //행의 개수
    int cols; //열의 개수
    int terms; //항의 개수
} SparseMatrix;

SparseMatrix change(SparseMatrix m, int i, int j) {
    SparseMatrix b;

    int index;
    b.rows = m.rows; //완전 전치행렬이 아니기 때문에 b.rows = n.cols를 하지않음. 필요한 부분만 서로 맞바꿔야함
    b.cols = m.cols;
    b.terms = m.terms;

    if (m.terms > 0) {
        index = 0;

        /*
         * 만약 0행과 2행을 바꾼다고 가정한다면, data배열을 돌면서 row가 0인(i)인 것을 찾고,
         * 그 row를 2로(j) 바꾸고,
         * row가 2인(j)인 것을 찾으면,
         * 그 row를 0으로(i) 바꾼다.
         * */
        for (int k = 0; k < m.terms; k++) {
            if (m.data[k].row == j) {
                m.data[k].row = i;
            } else if (m.data[k].row == i) {
                m.data[k].row = j;
            }
        }

        /*
         * 그러고 나면, 행을 위주로 정렬만 하면 된다.
         * */
        for (int c = 0; c < b.rows; c++) {
            for (int k = 0; k < m.terms; k++) {
                if (m.data[k].row == c) {
                    b.data[index].row = m.data[k].row;
                    b.data[index].col = m.data[k].col;
                    b.data[index].value = m.data[k].value;
                    index++;
                }
            }
        }
    }
    return b;
}

void PrintSparseMatrix(SparseMatrix m) {
    printf("========================\n");
    for (int i = 0; i < m.terms; i++) {
        printf("(%d, %d, %d)\n", m.data[i].row, m.data[i].col, m.data[i].value);
    }
    printf("========================\n");
}

int main(void) {
    SparseMatrix m = {
            {
                    {0, 0, 2},
                    {0, 2, -3},
                    {1, 2, 4},
                    {2, 0, 4},
                    {2, 1, -2},
                    {2, 2, 1},
                    {3, 3, 3},
            },
            4,
            4,
            7
    };

    SparseMatrix result;
    result = change(m, 0, 2);
    PrintSparseMatrix(result);

    return 0;
}