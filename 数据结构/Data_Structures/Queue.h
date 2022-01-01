#include <stdbool.h>
#include <stdlib.h>

#define ElementType int	/* 定义存储的数据类型 */
#define ERROR 65535		/* 定义一个不可能取到的数据用于表示删除失败 */

typedef int Position;	/* 定义存储位置的数据类型 */

/* 队列定义 */
typedef struct QNode *PtrToNode;
struct QNode{
	ElementType *Data; /* 存储队列数据 */
	Position Front, Rear;	/* 存储队列头、尾位置，头指向第一个元素前，尾指向最后一个元素 */
	int MaxSize;	/* 队列最大长度 */
};
typedef PtrToNode Queue;

/* 初始化空队列 */
Queue CreateQueue(int MaxSize);
/* 判断队列是否为满 */
bool Queue_IsFull(Queue Q);
/* 将元素X插到队列尾，成功则返回true */
bool AddQ(Queue Q, ElementType X);
/* 判断队列是否为空 */
bool Queue_IsEmpty(Queue Q);
/* 从队列中删除第一个元素并返回 */
ElementType DelateQ(Queue Q);