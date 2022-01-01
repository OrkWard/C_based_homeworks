#include <stdbool.h>

#define ElementType int

typedef struct HNode *Heap;
struct HNode {
	ElementType *Data;
	int Size;
	int Capacity;
};
typedef Heap MaxHeap;
typedef Heap MinHeap;

MaxHeap CreateHeap(int MaxSize);
bool IsFull(MaxHeap H);
bool Insert(MaxHeap H, ElementType X);
bool IsEmpty(MaxHeap H);
ElementType DeleteMax(MaxHeap H);