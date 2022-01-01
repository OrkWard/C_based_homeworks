#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define LEFT 0
#define RIGHT 1
#define MAXSIZE 300

typedef int ElementType;

typedef struct TNode *Tree;
struct TNode{
    ElementType Element;
    Tree Left;
    Tree Right;
};

typedef struct QNode *Queue;
struct QNode{
    Tree PtrT[MAXSIZE];
    int Front, Rear;
};

//根据先序遍历和中序遍历结果生成树
Tree BuildTree(int *postorder, int *inorder, int N);
//层扭曲遍历树
void ZigZag_Traversal(Tree T, int N);
//根据制定的方向遍历树的某一行
void Line_Traversal(Queue Q, int signal);
//在数组中寻找指定的数，返回下标
int Search(int *array, int N, int num);
//判断队列是否已满
bool IsEmpty(Queue Q);
//将元素压入队列
void AddQ(Queue Q, Tree T);
void AddQL(Queue Q, Tree T);
//将元素从队列中删除并返回
Tree DeleteQ(Queue Q);
//将元素从队列左边删除并返回
Tree DeleteQL(Queue Q);

int main(){
    int N, i;
    int postorder[MAXSIZE], inorder[MAXSIZE];
    scanf("%d", &N);

    for (i = 0; i < N; i++)
        scanf("%d", inorder + i);
    for (i = 0; i < N; i++)
        scanf("%d", postorder + i);
    
    Tree T;
    T = BuildTree(postorder, inorder, N);
    ZigZag_Traversal(T, N);
    printf("\n");
    return 0;
}

Tree BuildTree(int *postorder, int *inorder, int N){
    Tree T;
    int Position;
    if (N > 0){
        T = (Tree)malloc(sizeof(struct TNode));
        T->Element = postorder[N - 1];
        Position = Search(inorder, N, postorder[N - 1]);
        T->Left = BuildTree(postorder, inorder, Position);
        T->Right = BuildTree(postorder + Position, inorder + Position + 1, N - Position - 1);
        return T;
    }
    else 
        return NULL;
}

int Search(int *array, int N, int num){
    int i;
    for (i = 0; i < N; i++){
        if (array[i] == num)
            return i;
    }
    return -1;
}

void ZigZag_Traversal(Tree T, int N){
    Queue Q;
    Q = (Queue)malloc(sizeof(struct QNode));
    int signal = RIGHT;
    Q->Front = Q->Rear = -1;
    AddQ(Q, T);
    while(!IsEmpty(Q)){
        Line_Traversal(Q, signal);
        signal = !signal;
    }
}

void Line_Traversal(Queue Q, int signal){
    Tree tmp;
    int i, pace;
    static int first = 1;
    pace = (Q->Rear - Q->Front) % MAXSIZE;
    if (signal == LEFT){
        for (i = 0; i < pace; i++){
            tmp = DeleteQ(Q);
            if (first != 1)
                printf(" ");
            printf("%d", tmp->Element);
            first = 0;
            if (tmp->Left)
                AddQ(Q, tmp->Left);
            if (tmp->Right)
                AddQ(Q, tmp->Right);
        }
    }
    else{
        for (i = 0; i < pace; i++){
            tmp = DeleteQL(Q);
            if (first != 1)
                printf(" ");
            printf("%d", tmp->Element);
            first = 0;
            if (tmp->Right)
                AddQL(Q, tmp->Right);
            if (tmp->Left)
                AddQL(Q, tmp->Left);
        }
    }
}

bool IsEmpty(Queue Q){
    if (Q->Rear == Q->Front)
        return 1;
    else
        return 0;
}

void AddQ(Queue Q, Tree T){
    Q->Rear = (Q->Rear + 1) % MAXSIZE;
    (Q->PtrT)[Q->Rear] = T;
}

void AddQL(Queue Q, Tree T){
    (Q->PtrT)[Q->Front] = T;
    Q->Front = (Q->Front - 1) % MAXSIZE;
}

Tree DeleteQ(Queue Q){
    Q->Front = (Q->Front + 1) % MAXSIZE;
    return (Q->PtrT)[Q->Front];
}

Tree DeleteQL(Queue Q){
    Tree T = (Q->PtrT)[Q->Rear % MAXSIZE];
    Q->Rear = (Q->Rear - 1) % MAXSIZE;
    return T;
}