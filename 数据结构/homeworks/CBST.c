#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define ElementType int
#define MAXSIZE 2000

typedef struct TNode* Tree;
struct TNode{
    ElementType Element;
    Tree Left;
    Tree Right;
};

typedef struct QNode* Queue;
struct QNode{
    Tree* Data;
    int Front, Rear;
    int Maxsize;
};


Tree Create_CBST(ElementType* Element, int N);
void Sort(ElementType* Element, int N);
void line_traversal(Tree T);

Queue Create_queue(int Maxsize);
void AddQ(Queue Q, Tree T);
Tree DeleteQ(Queue Q);
bool IsEmpty(Queue Q);

int main(){
    int N, i;
    Tree T;
    ElementType Element[MAXSIZE];
    scanf("%d", &N);
    for (i = 0; i < N; i++){
        scanf("%d", Element + i);
    }
    Sort(Element, N);
    T = Create_CBST(Element, N);
    line_traversal(T);

    return 0;
}

void Sort(ElementType* Element, int N){
    int i, j;
    ElementType tmp;
    for (i = 0; i < N - 1; i++){
        for (j = 0; j < N - 1 - i; j++){
            if (Element[j] > Element[j + 1]){
                tmp = Element[j];
                Element[j] = Element[j + 1];
                Element[j + 1] = tmp;
            }
        }
    }
}

Tree Create_CBST(ElementType* Element, int N){
    if (N <= 0)
        return NULL;
    
    int root;
    int high = (int)log2(N) + 1;
    if (high == 1)
        root = 0;
    else if (N < 3 * (int)pow(2, high - 2))
        root = N - (int)pow(2, high - 2);
    else
        root = (int)pow(2, high - 1) - 1;
    
    Tree T = (Tree)malloc(sizeof(struct TNode));
    T->Element = Element[root];
    T->Left = Create_CBST(Element, root);
    T->Right = Create_CBST(Element + root + 1, N - root - 1);
    return T;
} 


void line_traversal(Tree T){
    Queue Q;
    Tree tmp_T;
    int flag = 1;

    if (!T)return;
    Q = Create_queue(MAXSIZE);
    AddQ(Q, T);
    while(!IsEmpty(Q)){
        tmp_T = DeleteQ(Q);
        if (flag == 1){
            printf("%d", tmp_T->Element);
            flag = 0;
        }
        else
            printf(" %d", tmp_T->Element);
        if (tmp_T->Left) AddQ(Q, tmp_T->Left);
        if (tmp_T->Right) AddQ(Q, tmp_T->Right);
    }
}

Queue Create_queue(int Maxsize){
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (Tree *)malloc(Maxsize * sizeof(Tree));
    Q->Front = Q->Rear = 0;
    Q->Maxsize = Maxsize;
    return Q;
}

bool IsEmpty(Queue Q){
    return (Q->Front == Q->Rear);
}

Tree DeleteQ(Queue Q){
    Q->Front = (Q->Front + 1) % Q->Maxsize;
    return Q->Data[Q->Front];
}

void AddQ(Queue Q, Tree T){
    Q->Rear = (Q->Rear + 1) % Q->Maxsize;
    Q->Data[Q->Rear] = T;
}