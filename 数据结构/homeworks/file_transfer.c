#include <stdio.h>
#define MAXSIZE 10001

typedef int SetType[MAXSIZE];

void Union(SetType S, int root1, int root2);
int Find(SetType S, int X);

int main(){
    int N, i, flag = 1;
    char instruct;
    int root1, root2;
    int X1, X2;

    SetType S;
    scanf("%d", &N);
    for (i = 0; i <= N; i++)
        S[i] = -1;
    
    do{
        instruct = getchar();
        switch (instruct){
            case 'C':
                scanf("%d%d", &X1, &X2);
                root1 = Find(S, X1);
                root2 = Find(S, X2);

                if (root1 == root2)
                    printf("yes\n");
                else
                    printf("no\n");
                break;
            case 'I':
                scanf("%d%d", &X1, &X2);
                root1 = Find(S, X1);
                root2 = Find(S, X2);
                if (root1 != root2)
                    Union(S, root1, root2);
                break;
            case 'S':
                flag = 0;
                break;
        }
    }while(flag == 1);

    int count = 0;
    for(i = 1; i <= N; i++){
        if(S[i] < 0)
            count++;
    }

    if(count == 1)
        printf("The network is connected.\n");
    else
        printf("There are %d components.\n", count);
    
    return 0;
}


int Find(SetType S, int X){
    if (S[X] < 0)
        return X;
    else
        return S[X] = Find(S, S[X]);
}

void Union(SetType S, int root1, int root2){
    if(S[root1] < S[root2]){
        S[root1] += S[root2];
        S[root2] = root1;
    }
    else{
        S[root2] += S[root1];
        S[root1] = root2;
    }
}