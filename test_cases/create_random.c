#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){
    int i;
    FILE *fp;

    fp = fopen("random.txt", "w");
    for(i = 0; i < 160; i++){
        srand(i * 1000);
        char a[10];
        int number = rand() % 100;
        fprintf(fp, "%d ", number);
        if(i % 16 == 15)
            fprintf(fp, "\n");
    }
    fclose(fp);
    return 0;
}