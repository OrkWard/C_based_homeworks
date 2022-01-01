#include <stdbool.h>

#define ElementType int

typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
	ElementType Data;
	BinTree Left;
	BinTree Right;
};

bool IsEmpty(BinTree BT);
void Traversal(BinTree BT);
BinTree CreateBinTree();

Position Find(BinTree BST, ElementType X);
Position FindMin(BinTree BST);
Position FindMax(BinTree BST);
BinTree Insert(BinTree BST, ElementType X);
BinTree Delete(BinTree BST, ElementType X);