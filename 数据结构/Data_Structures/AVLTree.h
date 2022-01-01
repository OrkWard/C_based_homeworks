#include <stdbool.h>

#define ElementType int

typedef struct AVLNode *Position;
typedef Position AVLTree;
typedef struct AVLNode {
	ElementType Data;
	AVLTree Left;
	AVLTree Right;
	int Height;
};

AVLTree Insert(AVLTree T, ElementType X);
AVLTree SingleLeftRotation(AVLTree A);
AVLTree SingleRightRotation(AVLTree A);
AVLTree DoubleLeftRightRotation(AVLTree A);
AVLTree DoubleRightLeftRotation(AVLTree A);