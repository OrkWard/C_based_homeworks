#include <stdio.h>
#define LeftChild(i) ((i) * 2 + 1)
#define MAXSIZE 100

int arycmp(int Array_1[], int Array_2[], int N){
	int i;
	for (i = 0; i < N; i++)
		if (Array_1[i] != Array_2[i])
			return 0;
	
	return 1;
}

void arycpy(int Array_1[], int Array_2[], int N){
	int i;
	for (i = 0; i < N; i++)
		Array_1[i] = Array_2[i];
}

void Insertion(int Sequence[], int N, int i){
	int tmp;
	for (tmp = Sequence[i]; i > 0; i--)
		if (Sequence[i] < Sequence[i - 1]){
			Sequence[i] = Sequence[i - 1];
			Sequence[i - 1] = tmp;
		}
		else
			break;
	Sequence[i] = tmp;
}

void output(int Array[], int N){
	int i;
	int flag = 0;
	for (i = 0; i < N; i++){
		if (flag)
			printf(" ");
		printf("%d", Array[i]);
		flag = 1;
	}
}

void Heap(int Sequence[], int N){
	int tmp, child, parent = 0;
	tmp = Sequence[N - 1];
	Sequence[N - 1] = Sequence[0];
	Sequence[0] = tmp;
	for (; LeftChild(parent) < N - 1; parent = child){
		child = LeftChild(parent);
		if (Sequence[child] < Sequence[child + 1] && child + 1 < N - 1)
			child++;
		if (Sequence[child] > tmp){
			Sequence[parent] = Sequence[child];
		}
		else
			break;
	}
	Sequence[parent] = tmp;
}

void BuidHeap(int Sequence[], int N){
	int i, tmp, child, parent;
	for (i = N; LeftChild(i) >= N; i--);
	
	for (; i >= 0; i--){
		parent = i;
		tmp = Sequence[parent];
		for (child = LeftChild(parent); child < N; child = LeftChild(parent)){
			if (Sequence[child] < Sequence[child + 1] && child + 1 < N)
				child++;
			if (Sequence[child] > Sequence[parent]){
				Sequence[parent] = Sequence[child];
				Sequence[child] = tmp;
				parent = child;
			}
			else
				break;
		}
		Sequence[parent] = tmp;
	}
}

int main(int argc, char const *argv[])
{
	int Sequence[MAXSIZE], Partial[MAXSIZE], Tmpary[MAXSIZE];
	int i, N;
	scanf("%d", &N);
	for (i = 0; i < N; i++)
		scanf("%d", Sequence + i);
	arycpy(Tmpary, Sequence, N);
	for (i = 0; i < N; i++)
		scanf("%d", Partial + i);

	for (i = 1; i < N; i++){
		Insertion(Sequence, N, i);
		if (arycmp(Sequence, Partial, N)){
			printf("Insertion Sort\n");
			Insertion(Sequence, N, i + 1);
			output(Sequence, N);
			return 0;
		}
	}

	BuidHeap(Tmpary, N);
	for (i = N; i > 0; i--){
		Heap(Tmpary, i);
		if (arycmp(Tmpary, Partial, N)){
			printf("Heap Sort\n");
			Heap(Tmpary, i - 1);
			output(Tmpary, N);
			return 0;
		}
	}
}
