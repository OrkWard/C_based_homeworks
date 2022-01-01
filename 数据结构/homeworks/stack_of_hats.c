#include <stdio.h>
#define MAXIMUN 10000

struct PTA{
    int weight;
    int num;
};

struct Hat{
    int large;
    int num;
};

//在Hat数组中寻找num值为指定值的项
int Search_HAT(struct Hat * hat, int N, int num);

int main(){
    int N, i, j;
    struct PTA PTAer[MAXIMUN], tmp_PTAer;
    struct Hat hat[MAXIMUN], tmp_hat;

    scanf("%d", &N);
    for (i = 0; i < N; i++){
        scanf("%d", &(hat[i].large));
        hat[i].num = i;
    }
    for (i = 0; i < N; i++){
        scanf("%d", &(PTAer[i].weight));
        PTAer[i].num = i;
    }

    for (i = 0; i < N; i++){
        for (j = 0; j < N - i - 1; j++){
            if (PTAer[j + 1].weight < PTAer[j].weight){
                tmp_PTAer.num = PTAer[j + 1].num;
                tmp_PTAer.weight = PTAer[j + 1].weight;
                PTAer[j + 1].num = PTAer[j].num;
                PTAer[j + 1].weight = PTAer[j].weight;
                PTAer[j].num = tmp_PTAer.num;
                PTAer[j].weight = tmp_PTAer.weight;
            }

            if (hat[j + 1].large < hat[j].large){
                tmp_hat.num = hat[j + 1].num;
                tmp_hat.large = hat[j + 1].large;
                hat[j + 1].num = hat[j].num;
                hat[j + 1].large = hat[j].large;
                hat[j].num = tmp_hat.num;
                hat[j].large = tmp_hat.large;
            }
        }
    }

    for (i = N - 1; i >= 0; i--){
        printf("%d", PTAer[Search_HAT(hat, N, i)].num + 1);
        if (i > 0)
            printf(" ");
    }
    return 0;
}

int Search_HAT(struct Hat * hat, int N, int num){
    int i;
    for (i = 0; i < N; i++){
        if (hat[i].num == num)
        return i;
    }
}