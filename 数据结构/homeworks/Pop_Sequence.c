#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Position;
typedef struct SNode * PtrToSNode;
struct SNode {
    int Data[1000];
    Position Top;
    int MaxSize;
};
typedef PtrToSNode Stack;

Stack CreateStack(int MaxSize){
    Stack S = (Stack)malloc(sizeof(struct SNode));
    S->Top = -1;
    S->MaxSize = MaxSize;
    return S;
}

bool IsFull(Stack S){
    return (S->Top == S->MaxSize - 1);
}

bool IsEmpty(Stack S){
    return (S->Top == -1);
}

bool Push(Stack S, int X){
    if (IsFull(S)){
        return false;
    }
    else {
        S->Data[++(S->Top)] = X;
        return true;
    }
}

int Pop(Stack S){
    if (IsEmpty(S)){
        return false;
    }
    else {
        return (S->Data[(S->Top--)]);
    }
}

int main(){
    int M, N, K;
    Stack S, S_tmp, S0;
    scanf("%d%d%d", &M, &N, &K);
    S = CreateStack(M);
    S_tmp = CreateStack(N);
    S0 = CreateStack(N);

    int i, j, X;
    for (i = 0; i < K; i++){
        for (j = 0; j < N; j++){
            S->Data[j] = 0;
            S_tmp->Data[j] = 0;
            S0->Data[j] = 0;
        }
        S->Top = -1;
        S_tmp->Top = -1;
        S0->Top = -1;
        for (j = 0; j < N; j++){
            scanf("%d", &X);
            Push(S0, X);
        }
        for (j = 0; j < N; j++){
            Push(S_tmp, Pop(S0));
        }
        for (j = N; j > 0; j--){
            Push(S0, j);
        }

        while(!IsEmpty(S_tmp)){
            if (S->Data[S->Top] == S_tmp->Data[S_tmp->Top]){
                Pop(S);
                Pop(S_tmp);
            }
            else {
                if (IsEmpty(S0)){
                    break;
                }
                else {
                    if (IsFull(S))
                        break;
                    Push(S, Pop(S0));
                }
            }
        }

        if (IsEmpty(S_tmp)){
            printf("YES\n");
        }
        else 
            printf("NO\n");
    }

    return 0;
}