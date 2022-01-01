#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAXSIZE 100

//树结构体定义
typedef struct TNode* Tree;
struct TNode{
    int Element;
    Tree Left;
    Tree Right;
};
//队列结构体定义
typedef struct QNode* Queue;
struct QNode{
    Tree *Data;
    int Front, Rear;
    int Maxsize;
};

//读入一个数字，或者‘-’
int Read_chara(void);
//主要函数，根据读入的结果构造树
Tree Create_tree(int N, int* in_order, int* pre_order, int* post_order);
//中序遍历
void in_traversal(Tree T);
//先序遍历
void pre_traversal(Tree T);
//后序遍历
void post_traversal(Tree T);
//层序遍历
void line_traversal(Tree T);
//在数组array中寻找chara，找到则返回第一个相符下标
int Search(int N, int* array, int chara);
//对于仅缺少一个数的特殊序列，直接进行填充
void fill_in(int N, int* array);

//队列操作集，构造队列
Queue Create_queue(int Maxsize);
//判断队列是否为空
bool IsEmpty(Queue Q);
//删除队列元素，并返回被删除的元素
Tree DeleteQ(Queue Q);
//增加队列元素
void AddQ(Queue Q, Tree T);

//一个全局变量，用于记录是否能生成树
bool flag = true;

int main(){
    int N, i;
    int in_order[MAXSIZE], pre_order[MAXSIZE], post_order[MAXSIZE];//用于存储输入
    scanf("%d", &N);
    for (i = 0; i < N; i++)//读入中序遍历
        in_order[i] = Read_chara();
    for (i = 0; i < N; i++)//读入先序遍历
        pre_order[i] = Read_chara();
    for (i = 0; i < N; i++)//读入后序遍历
        post_order[i] = Read_chara();

    fill_in(N, in_order);
    fill_in(N, pre_order);
    fill_in(N, post_order);

    Tree T = Create_tree(N, in_order, pre_order, post_order);
    if (flag){
        in_traversal(T); printf("\n");
        pre_traversal(T); printf("\n");
        post_traversal(T); printf("\n");
        line_traversal(T); printf("\n");
    }
    else
        printf("Impossible\n");
}

Tree Create_tree(int N, int* in_order, int* pre_order, int* post_order){
    Tree T;
    int point;//用于记录根节点在中序遍历中的位置
    if (N == 0){//空树，返回NULL
        return NULL;
    }
    else {
        if (pre_order[0] == 0){//先序遍历首数未给出，无法获知根节点
            if (post_order[N - 1] == 0){//后序遍历尾数未给出，无法获知根节点
                flag = 0;//无法构造树
                return NULL;
            }
            else {
                T = (Tree)malloc(sizeof(struct TNode));
                T->Element = post_order[N - 1];//分配根节点空间并赋值
                point = Search(N, in_order, post_order[N - 1]);//在中序遍历中寻找根节点
                if (point == -1){//没有找到
                    free(T);//释放空间防止内存溢出
                    flag = 0;//无法构造树
                    return NULL;
                }
                else {
                    T->Left = Create_tree(point, in_order, 
                                          pre_order + 1, 
                                          post_order);//递归构造左子树
                    T->Right = Create_tree(N - point - 1, 
                                            in_order + point + 1, 
                                            pre_order + point + 1, 
                                            post_order + point);//递归构造右子树
                }
            }
        }
        else {
            if (post_order[N - 1] != 0){
                if (pre_order[0] != post_order[N - 1]){//树错误
                    flag = 0;
                    return NULL;
                }
            }
            T = (Tree)malloc(sizeof(struct TNode));
            T->Element = pre_order[0];//分配根节点空间并赋值
            point = Search(N, in_order, pre_order[0]);//在中序遍历中寻找根节点
            if (point == -1){//没有找到
                free(T);//释放空间防止内存溢出
                flag = 0;//无法构造树
                return NULL;
            }
            else {
                T->Left = Create_tree(point, in_order, 
                                      pre_order + 1, 
                                      post_order);//递归构造左子树
                T->Right = Create_tree(N - point - 1, 
                                        in_order + point + 1, 
                                        pre_order + point + 1, 
                                        post_order + point);//递归构造右子树
            }
        }
    }

    return T;
}

int Search(int N, int* array, int chara){
    int i;
    for (i = 0; i < N; i++){
        if (array[i] == chara)
            return i;
    }//如果找到，直接返回下标

    int count = 0;//记录‘-’个数
    for (i = 0; i < N; i++){
        if (array[i] == 0)
            count++;
    }
    if (count == 1){//‘-’只有一个，可以判断这就是要找的chara所在
        return Search(N, array, 0);
    }
    
    return -1;//‘-’多于一个，找不到chara
}

void in_traversal(Tree T){//递归的中序遍历
    if (T){
        in_traversal(T->Left);
        printf("%d ", T->Element);
        in_traversal(T->Right);
    }
}

void pre_traversal(Tree T){//递归的先序遍历
    if (T){
        printf("%d ", T->Element);
        pre_traversal(T->Left);
        pre_traversal(T->Right);
    }
}

void post_traversal(Tree T){//递归的后序遍历
    if (T){
        post_traversal(T->Left);
        post_traversal(T->Right);
        printf("%d ", T->Element);
    }
}

void line_traversal(Tree T){//利用队列的非递归层序遍历
    Queue Q;
    Tree tmp_T;

    if (!T)return;
    Q = Create_queue(MAXSIZE);
    AddQ(Q, T);
    while(!IsEmpty(Q)){
        tmp_T = DeleteQ(Q);
        printf("%d ", tmp_T->Element);
        if (tmp_T->Left) AddQ(Q, tmp_T->Left);
        if (tmp_T->Right) AddQ(Q, tmp_T->Right);
    }
}

Queue Create_queue(int Maxsize){//生成空队列
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

int Read_chara(void){
    char ch;
    int num = 0;
    do {
        ch = getchar();
    }while(ch == ' ' || ch == '\n' || ch == '\r');//读入第一个非空白字符

    if (ch == '-')
        return 0;//如果是‘-’直接返回
    else {
        do {
            num = num * 10 + ch - '0';
        }while((ch = getchar()) != ' ' && ch != '\n' && ch != '\r');
        return num;//不是‘-’，依次读入直至遇见空白字符
    }
}

void fill_in(int N, int* array){
    int record[MAXSIZE] = {0}, i, Count = 0;//record用于记录哪些数出现
    for(i = 0; i < N; i++){
        record[array[i]]++;
    }

    for(i = 1; i <= N; i++){
        if(record[i] == 0)
            Count++;
    }
    if (Count == 1){
        array[Search(N, array, 0)] = Search(N, record + 1, 0) + 1;
    }//仅有一个'-'，将该项替换为缺少的数
}