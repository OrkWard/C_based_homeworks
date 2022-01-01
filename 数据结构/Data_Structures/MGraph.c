#include "MGraph.h"

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