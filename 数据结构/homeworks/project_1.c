#include <stdio.h>
#include <time.h>
#include <math.h>

clock_t start, stop;//定义两个全局变量用于记录时间
double duration;

//算法1
double Algorithm_1(double X, long long N);
//算法2的迭代版本
double Algorithm_2_iterative(double X, long long N);
//算法2的递归版本
double Algorithm_2_recursive(double X, long long N);

int main(){
    //由于要测试的值已经确定，这里不再使用scanf读入，直接在代码中列出；同时由于量比较少，也不必使用文件读入
    double X = 1.0001;
    long long N[16] = {1000, 5000, 10000, 20000, 40000, 60000, 80000, 100000, //由于提供的值用于算法2测试不太合适，这里另外增加了一些值
                       200000, 400000, 800000, 1600000, 3200000, 6400000, 12800000, 25600000};
    int i, j, k;//计数器
    int K = 10000;//重复次数
    double (*Algorithm[3])(double, long long);//定义一个函数指针数组，便于轮换调用三个算法
    Algorithm[0] = Algorithm_1, Algorithm[1] = Algorithm_2_iterative, Algorithm[2] = Algorithm_2_recursive;

    //输出结果
    printf("1000\t\t5000\t\t10000\t\t20000\t\t40000\t\t60000\t\t\t80000\t\t\t100000\n");//表头
    for (i = 0; i < 3; i++){
        for (j = 0; j < 8; j++){
            printf("%.12lf\t", Algorithm[i](X, N[j]));
        }
        printf("\n");
    }
    printf("\n\n");//分隔结果和运行时间测试

    //输出表格头
    //另外设了一个值k，用于计算运算时间和指数N的比值
    printf("N\tIterations(K)\tTicks\tTotal Time(sec)\tDuration(sec)\tk\n");
    for (i = 0; i < 3; i++){
        for (j = 0; j < 16; j++){
            if (j > 7 && i == 0)
                break;//后面的值对算法1来说过大，无法在合理时间内完成运算
            
            start = clock();//开始计时
            for (k = 0; k < K; k++){//计算K次
                Algorithm[i](X, N[j]);
            }
            stop = clock();//停止计时
            duration = ((double)(stop - start)) / CLOCKS_PER_SEC;//macOS需要用CLOCK_PER_SEC代替CLK_TCK

            //打印一行表格，N大小/重复次数K/Ticks数/总时长/计算一次时长
            if (i == 0)
                printf("%8lld\t%d\t\t%.0lf\t%lf\t%lf\t%lf\n", 
                        N[j], K, stop - (double)start, duration, 
                        duration / K, duration / K * 1000000 / N[j]);//过长，进行换行
            else
                printf("%8lld\t%d\t\t%.0lf\t%lf\t%lf\t%lf\n", 
                        N[j], K, stop - (double)start, duration, 
                        duration / K, duration / K * 1000000 / (j + 5));
        }
        printf("\n");
    }

    return 0;
}

double Algorithm_1(double X, long long N){
    long long i;//计数器
    double result = 1;//用于存储结果的变量
    for (i = 0; i < N; i++){
        result = result * X;//迭代过程
    }
    return result;
}

double Algorithm_2_iterative(double X, long long N){
    /*
    进行两次迭代：第一次反复用2去除N，得到一个余数序列；
    第二次根据余数序列反向迭代计算X^N的值。
    由于两次迭代时间复杂度一致，故重复进行一次不会改变时间复杂度的数量级
    */
    char remain[1000];//存放余数，由于迭代进行的次数为log2N级，数组大小可以置很小的值
    int i = 0;//计数器，基于同样的原因不用选择long long型变量
    double result = 1;//用于存放结果的变量
    while (N > 0){
        if (N % 2 == 0){//N为偶数的情况
            remain[i] = 0;
            N = N / 2;
        }
        else{//N为奇数的情况
            remain[i] = 1;
            N = (N - 1) / 2;
        }
        i++;//计数器增加，为存储下一个余数做准备
    }

    for (i = i - 1 ; i >= 0; i--){//上个循环结束后，i停在最后一个余数的后一位
        if (remain[i] == 1){//余数为奇数的情况，平方后再乘X
            result = result * result * X;
        }
        else{//余数为偶数的情况，直接平方
            result = result * result;
        }
    }

    return result;
}

double Algorithm_2_recursive(double X, long long N){
    if (N == 1){//递归出口
        return X;
    }
    else if (N % 2 == 0){//这里调用pow函数，是避免出现两个递归，导致不必要的空间复杂度
        return pow(Algorithm_2_recursive(X, N / 2), 2);
    }
    else{
        return pow(Algorithm_2_recursive(X, N / 2), 2) * X;
    }
}