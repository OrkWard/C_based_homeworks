#include <stdbool.h>
#include <stdlib.h>

#define MaxVertexNum 201    /* 定义最大顶点数 */
#define INFINITY 65535      /* 定义一个不能取到的数，用于表示两点并不相连 */
typedef int Vertex;         /* 定义顶点类型，如果用下标表示顶点则为整型 */
typedef int WeightType;     /* 定义边的权值类型 */
typedef char DataType;      /* 定义顶点存储的数据类型 */

/* 边定义 */
typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;  /* 有向边<V1, V2> */
    WeightType Weight;  /* 权重 */
};
typedef PtrToENode Edge;    /* 边类型 */

/* 邻接点定义 */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode{
    Vertex AdjV;    /* 邻接点下表 */
    WeightType Weight;  /* 边权重 */
    PtrToAdjVNode Next; /* 指向下一个结点的指针 */
};

/* 顶点表头结点定义 */
typedef struct VNode{
    PtrToAdjVNode FirstEdge;    /* 边表头指针 */
    DataType Data;  /* 存储顶点数据 */
}AdjList[MaxVertexNum]; /* 邻接表类型 */

typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv; /* 顶点数 */
    int Ne; /* 边数 */
    AdjList G;  /* 邻接表 */
};
typedef PtrToGNode LGraph;  /* 以邻接表形式存储的图类型 */

/* 初始化一个有VertexNum个顶点但没有边的图 */
LGraph CreateGraph(int VertexNum);
/* 读入数据建立图，先给出顶点数、边数，再给出所有边和权重，最后给出顶点数据 */
LGraph BuildGraph(void);
/* 在G中增加新边E */
void InsertEdge(LGraph G, Edge E);
/* 从G中删除边E */
void DeleteEdge(LGraph G, Edge E);
/* 判断图是否为空，为空返回true */
bool Graph_IsEmpty(LGraph G);
/* 从顶点V出发进行深度优先遍历 */
void DFS(LGraph G, Vertex V, void (*Visit)(Vertex));
/* 从顶点V出发进行广度优先遍历 */
void BFS(LGraph G, Vertex V, void (*Visit)(Vertex));