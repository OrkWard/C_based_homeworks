#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass( ElementType list[], ElementType sorted[], int N, int length );

void output( ElementType list[], int N )
{
    int i;
    for (i=0; i<N; i++) printf("%d ", list[i]);
    printf("\n");
}

void  merge_sort( ElementType list[],  int N )
{
    ElementType extra[MAXN];  /* the extra space required */
    int  length = 1;  /* current length of sublist being merged */
    while( length < N ) { 
        merge_pass( list, extra, N, length ); /* merge list into extra */
        output( extra, N );
        length *= 2;
        merge_pass( extra, list, N, length ); /* merge extra back to list */
        output( list, N );
        length *= 2;
    }
} 


int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &A[i]);
    merge_sort(A, N);
    output(A, N);

    return 0;
}

void merge_pass(ElementType list[], ElementType extra[], int N, int length){
	int i, j;
	int pleft, pright, pdest;
	for (i = 0; i + 2 * length < N; i += 2 * length){
		pleft = i;
		pright = i + length;
		for (pdest = i; pdest < i + 2 * length; pdest++){
			if (pleft == i + length)
				extra[pdest] = list[pright++];
			else if (pright == i + 2 * length)
				extra[pdest] = list[pleft++];
			else if (list[pleft] < list[pright])
				extra[pdest] = list[pleft++];
			else
				extra[pdest] = list[pright++];
		}
	}

	if (i + length < N){
		pleft = i;
		pright = i + length;
		for (pdest = i; pdest < N; pdest++){
			if (pleft == i + length)
				extra[pdest] = list[pright++];
			else if (pright == N)
				extra[pdest] = list[pleft++];
			else if (list[pleft] < list[pright])
				extra[pdest] = list[pleft++];
			else
				extra[pdest] = list[pright++];
		}
	}
	else {
        for (pdest = i; pdest < N; pdest++)
            extra[pdest] = list[pright++];
	}
	return;
}