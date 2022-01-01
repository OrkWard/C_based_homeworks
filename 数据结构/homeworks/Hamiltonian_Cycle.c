#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxVertexNum 201    /* 定义最大顶点数 */
#define INFINITY 65535      /* 定义一个不能取到的数，用于表示两点并不相连 */
typedef int Vertex;         /* 定义顶点类型，如果用下标表示顶点则为整型 */
typedef int WeightType;     /* 定义边的权值类型 */
typedef char DataType;      /* 定义顶点存储的数据类型 */

/* 图结点定义 */
typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv; /* 顶点数 */
    int Ne; /* 边数 */
    WeightType G[MaxVertexNum][MaxVertexNum];   /* 邻接矩阵 */
    DataType Data[MaxVertexNum];    /* 存放顶点数据 */
};
typedef PtrToGNode MGraph;  /* 以邻接矩阵形式存储的图类型 */

/* 边定义 */
typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;  /* 有向边<V1, V2> */
    WeightType Weight;  /* 权重 */
};
typedef PtrToENode Edge;    /* 边类型 */

/* 初始化一个有VertexNum个顶点但没有边的图 */
MGraph CreateGraph(int VertexNum);
/* 读入数据建立图，先给出顶点数、边数，再给出所有边和权重，最后给出顶点数据 */
MGraph BuildGraph(void);
/* 在G中增加新边E */
void InsertEdge(MGraph G, Edge E);
/* 从G中删除边E */
void DeleteEdge(MGraph G, Edge E);
/* 判断图是否为空，为空返回true */
bool Graph_IsEmpty(MGraph G);
/* 从顶点V出发进行深度优先遍历 */
void DFS(MGraph G, Vertex V, void (*Visit)(Vertex));
/* 从顶点V出发进行广度优先遍历 */
void BFS(MGraph G, Vertex V, void (*Visit)(Vertex));

int main(){
	MGraph Graph;
	int K, n, i, j;
	Vertex V1, V2, start, end, *Seq;
	bool flag;
	Graph = BuildGraph();

	scanf("%d", &K);
	for (i = 0; i < K; i++){
		flag = true;
		scanf("%d", &n);
		if (n - 1 != Graph->Nv){
			for (j = 0; j < n; j++) scanf("%d", &V1);
			printf("NO\n");
			continue;
		}

		Seq = (Vertex*)malloc((n + 1) * sizeof(Vertex));
		for (j = 1; j < n; j++) Seq[j] = 0;
		scanf("%d%d", &V1, &V2);
		start = V1;
		Seq[V1] = Seq[V2] = 1;
		for (j = 0; j < n - 1; j++){
			if (Graph->G[V1][V2] == INFINITY){
				flag = false;
			}
			V1 = V2;
			if(j < n - 2) scanf("%d", &V2);
			end = V2;
			Seq[V2] = 1;
		}

		if (start != end) flag = false;
		
		for (j = 1; j < n; j++){
			if (Seq[j] != 1){
				flag = false;
			}
		}

		if (flag) printf("YES\n");
		else printf("NO\n");
	}

	return 0;
}

MGraph CreateGraph(int VertexNum){
    Vertex V, W;
    MGraph Graph;

    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    //初始化邻接矩阵，默认定点编号从零开始
    for (V = 0; V < Graph->Nv; V++){
        for (W = 0; W < Graph->Nv; W++){
            Graph->G[V][W] = INFINITY;
        }
    }

    return Graph;
}

void InsertEdge(MGraph Graph, Edge E){
    Graph->G[E->V1][E->V2] = E->Weight;
    //如果为无向图则同时建立反向边
    Graph->G[E->V2][E->V1] = E->Weight;
}

MGraph BuildGraph(void){
    MGraph Graph;
    Edge E;
    Vertex V;
    int Nv, i;

    scanf("%d", &Nv);   //读入顶点个数
    Graph = CreateGraph(Nv);

    scanf("%d", &(Graph->Ne)); //读入边数
    if (Graph->Ne != 0){
        E = (Edge)malloc(sizeof(struct ENode)); //建立边结点
        for (i = 0; i < Graph->Ne; i++){
            //读入边格式为“起点 终点 权重（如果有）
            scanf("%d%d", &E->V1, &E->V2);
            E->Weight = 1;
            InsertEdge(Graph, E);
        }
    }

    //如果顶点有数据则读入
    // for (V = 0; V < Graph->Nv; V++){
    //     scanf("%c", &(Graph->Data[V]));
    // }

	return Graph;
}