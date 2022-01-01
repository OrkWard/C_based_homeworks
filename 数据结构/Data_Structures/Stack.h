#include <stdbool.h>
#define ElementType int

typedef int Position;

/* 堆栈定义 */
typedef struct SNode *PtrToSNode;
struct SNode {
	ElementType *Data;	/* 存储数据 */
	Position Top;	/* 栈顶指针 */	
	int MaxSize;	/* 栈容量 */
};
typedef PtrToSNode Stack;	/* 堆栈类型 */

/* 初始化空栈 */
Stack CreateStack(int MaxSize);
/* 判断栈是否为满 */
bool IsFull(Stack S);
/* 压入元素 */
bool Push(Stack S);
/* 判断栈是否为空 */
bool IsEmpty(Stack S);
/* 弹出元素 */
ElementType Pop(Stack S);