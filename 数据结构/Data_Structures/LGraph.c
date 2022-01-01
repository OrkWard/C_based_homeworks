#include "LGraph.h"

LGraph CreateGraph(int VertexNum){
	Vertex V;
	LGraph Graph;

	Graph = (LGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;

	//初始化邻接表头指针，默认定点编号从零开始
	for (V = 0; V < Graph->Nv; V++){
		Graph->G[V].FirstEdge = NULL;
	}

	return Graph;
}

void InsertEdge(LGraph Graph, Edge E){
	PtrToAdjVNode NewNode;
	//插入边<V1, V2>，为V2建立新的邻接点
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;
	NewNode->Weight = E->Weight;
	//将V2插入V1的表头
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;


	//若是无向图，还需要插入边<V2, V1>
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V1;
	NewNode->Weight = E->Weight;
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
}

LGraph BuildGraph(void){
	LGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;

	scanf("%d", &Nv);	//读入顶点个数
	Graph = CreateGraph(Nv);

	scanf("%d", &(Graph->Ne));	//读入边数
	if (Graph->Ne != 0){
		E = (Edge)malloc(sizeof(struct ENode));	//建立边结点
		for (i = 0; i < Graph->Nv; i++){
			//读入边，格式为“起点 终点 权重”
			scanf("%d%d%d", &E->V1, &E->V2, &E->Weight);
			InsertEdge(Graph, E);
		}
	}

	//若顶点有数据则读入
	for (V = 0; V < Graph->Nv; V++){
		scanf("%c", &(Graph->G[V].Data));
	}

	return Graph;
}