/*	将所有寻址距离为0的点入堆；
	1、选出其中最小的数填入；
	2、考察该数的下一个数，如果能填入则入堆；
	3、回到1，直到没有数可填
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct HashTbl{
	int Capacity;
	int *List;
	int *Insertion;
	int *Distance;
	int *Heaped;
};
typedef struct HashTbl *Hash;

struct MinHeap{
	int Capacity;
	int Size;
	int *Elements;
};
typedef struct MinHeap *Heap;

Hash ReadHash(int N);
Heap Initialize(int N);
void InsertH(Heap H, Hash Ha, int x);
int DeleteMin(Heap He, Hash Ha);
bool IsEmpty(Heap H);
void Output(int *Line, int Count);

int main(){
	int N, i, Count = 0;
	Hash Ha;
	Heap He;
	int *Insert;
	int Element, Backward, Next;
	bool Flag;
	
	scanf("%d", &N);
	Ha = ReadHash(N);
	He = Initialize(N);
	Insert = (int*)malloc(N * sizeof(int));
	
	for (i = 0; i < N; i++){
		if (Ha->Distance[i] == 0 && Ha->Insertion[i] == 0){
			InsertH(He, Ha, i);
			Ha->Heaped[i] = 1;
		}
	}
	
	while(1){
		if (IsEmpty(He))
			break;
		
		Element = DeleteMin(He, Ha);
		Ha->Insertion[Element] = 1;
		Insert[Count++] = Ha->List[Element];
		Next = (Element + 1) % N;
		while (Next != Element){
			if (Ha->Insertion[Next] == 0)
				break;
				Next++;
		}
	
		if (Next != Element && Ha->Distance[Next] != 0 && Ha->Heaped[Next] == 0){
			Flag = 1;
			Backward = 0;
			while(Backward < Ha->Distance[Next]){
				if (Ha->Insertion[(Next + N - Backward++ - 1) % N] != 1){
					Flag = 0;
					break;
				}
			}
			if (Flag){
				InsertH(He, Ha, Next);
				Ha->Heaped[Next] = 1;
			}
		}
	}
	
	Output(Insert, Count);
	return 0;
}

Hash ReadHash(int N){
	int i;
	Hash H;
	H = (Hash)malloc(sizeof(struct HashTbl));
	H->Capacity = N;
	H->List = (int*)malloc(N * sizeof(int));
	H->Insertion = (int*)malloc(N * sizeof(int));
	H->Distance = (int*)malloc(N * sizeof(int));
	H->Heaped = (int*)malloc(N * sizeof(int));
	for (i = 0; i < N; i++){
		scanf("%d", &H->List[i]);
		if (H->List[i] < 0){
			H->Insertion[i] = 1;
		}
		else {
			H->Insertion[i] = 0;
		}
		H->Distance[i] = (i - H->List[i] % N + N) % N;
		H->Heaped[i] = 0;
	}
	
	return H;
}

Heap Initialize(int N){
	Heap H;
	
	H = (Heap)malloc((sizeof(struct MinHeap)));
	H->Capacity = N;
	H->Size = 0;
	H->Elements = (int*)malloc((N + 1) * sizeof(int));
	H->Elements[0] = 0;
	
	return H;
}

void InsertH(Heap He, Hash Ha, int x){
	int i;
	
	for (i = ++He->Size; i / 2 > 0 && Ha->List[He->Elements[i / 2]] > Ha->List[x]; i /= 2)
	He->Elements[i] = He->Elements[i / 2];
	He->Elements[i] = x;
}

int DeleteMin(Heap He, Hash Ha){
	int i, Child, MinElement, LastElement;
	
	MinElement = He->Elements[1];
	LastElement = He->Elements[He->Size--];
	
	for (i = 1; i * 2 <= He->Size; i = Child){
			Child = i * 2;
		if (Child != He->Size && Ha->List[He->Elements[Child + 1]] < Ha->List[He->Elements[Child]])
			Child++;
		
		if (Ha->List[LastElement] > Ha->List[He->Elements[Child]])
			He->Elements[i] = He->Elements[Child];
		else
			break;
	}
	He->Elements[i] = LastElement;
	return MinElement;
}

bool IsEmpty(Heap H){
	return H->Size == 0;
}

void Output(int *Line, int Count){
	int Flag = 0, i;
	for (i = 0; i < Count; i++){
		if (Flag)
			printf(" ");
		Flag = 1;
		printf("%d", *(Line + i));
	}
}