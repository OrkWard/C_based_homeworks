#include <stdio.h>
#include <stdlib.h>
#define MAXIMUN 100

typedef struct Node * PtrToNode;
struct Node{
    int num;
    PtrToNode next;
};
typedef PtrToNode List;

//读取一个排列
List ReadList(int N);
//复制一个排列，L1到L2
void CopyList(List L1, List L2);
//排列是否为空
int NULLorNot(List L);            
//查询num是否位于L首端
int CheckF(List L, int num);                
//查询num是否位于L末端
int CheckL(List L, int num);                
//在L末端增加元素num
void AddItem(List L, int num);              
//取出L首端的元素
int DeletF(List L);                        
//取出L末端元素
int DeletL(List L);                        

int main(){
    int N, K, i, j, symbol;
    int query[MAXIMUN];
    List tmp, insert, line;

    scanf("%d%d", &N, &K);
    
    insert = ReadList(N);
    
    for (i = 0; i < K; i++){
        for (j = 0; j < N; j++){
            scanf("%d", query + j);
        }
        tmp = (PtrToNode)malloc(sizeof(struct Node));
        tmp->next = NULL;
        CopyList(insert, tmp);
        line = (PtrToNode)malloc(sizeof(struct Node));
        line->next = NULL;

        for (j = 0; j < N; j++){
            symbol = 0;

            while (symbol == 0){
                if (CheckF(line, query[j]) == 1){
                    DeletF(line);
                    symbol = 1;
                }
                else if (CheckL(line, query[j]) == 1){
                    DeletL(line);
                    symbol = 1;
                }
                else {
                    if (NULLorNot(tmp) == 1){
                        break;
                    }
                    AddItem(line, DeletF(tmp));
                }
            }
        }

        if (NULLorNot(line) == 1){
            printf("yes\n");
        }
        else{
            printf("no\n");
        }
    }

    getchar();
    getchar();
    return 0;
}

List ReadList(int N){
    int i;
    PtrToNode L, head;
    L = (PtrToNode)malloc(sizeof(struct Node));
    head = L;
    L->next = NULL;
    for (i = 0; i < N; i++){
        L->next = (PtrToNode)malloc(sizeof(struct Node));
        L = L->next;
        L->next = NULL;
        scanf("%d", &(L->num));
    }

    return head;
}

void CopyList(List L1, List L2){
    PtrToNode p1, p2;
    p1 = L1->next;
    p2 = L2;
    while (p1 != NULL){
        p2->next = (PtrToNode)malloc(sizeof(struct Node));
        p2 = p2->next;
        p2->num = p1->num;
        p2->next = NULL;
        p1 = p1->next;
    }
}

int NULLorNot(List L){
    if (L->next == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

int CheckF(List L, int num){
    if (L->next != NULL && L->next->num == num){
        return 1;
    }
    else
        return 0;
}

int CheckL(List L, int num){
    PtrToNode p1, p2;
    p1 = L->next;
    p2 = L;
    while(p1 != NULL){
        p2 = p1;
        p1 = p1->next;
    }

    if (L->next == NULL){
        return 0;
    }
    else if (p2->num == num){
        return 1;
    }
    else {
        return 0;
    }
}

void AddItem(List L, int num){
    PtrToNode p1, p2;
    p1 = L->next;
    p2 = L;
    while(p1 != NULL){
        p2 = p1;
        p1 = p1->next;
    }

    p2->next = (PtrToNode)malloc(sizeof(struct Node));
    p2 = p2->next;
    p2->num = num;
    p2->next = NULL;
}

int DeletF(List L){
    PtrToNode p;
    int num;
    p = L->next;
    L->next = p->next;
    num = p->num;
    free(p);
    
    return num;
}

int DeletL(List L){
    PtrToNode p1, p2;
    int num;
    p1 = L->next;
    p2 = L;
    while(p1->next != NULL){
        p2 = p1;
        p1 = p1->next;
    }

    num = p1->num;
    p2->next = NULL;
    free(p1);
    return num;
}