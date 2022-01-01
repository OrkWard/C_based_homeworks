#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MaxVertexNum 1011		/* 最大顶点数，dispatch center从1001开始 */
#define MaxSpotNum 1000			/* 最大呼救点数 */
#define INFINITY 65535		/* 表示两点间无路径 */
#define ERROR -1			/* 错误标志 */
typedef int Vertex;			/* 顶点类型 */
typedef int WeightType;		/* 边的权值类型 */

/* 边定义 */
typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;
    WeightType Time;
};
typedef PtrToENode Edge;	/* 边类型 */

/* 邻接点定义 */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode{
    Vertex AdjV;
    WeightType Time;
    PtrToAdjVNode Next;
};

/* 顶点表头结点定义 */
typedef struct VNode{
    PtrToAdjVNode FirstEdge;
}AdjList[MaxVertexNum];	/* 邻接表类型 */

/* 图定义 */
typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv; /* 顶点数 */
    int Ne; /* 边数 */
    AdjList G;  /* 邻接表 */
};
typedef PtrToGNode LGraph;  /* 以邻接表形式存储的图类型 */

/* 初始化一个有VertexNum个顶点但没有边的图 */
LGraph CreateGraph(int VertexNum);
/* 读入数据建立图 */
LGraph BuildCity(int Nv);
/* 在G中增加新边E */
void InsertEdge(LGraph G, Edge E);
/* 用于获取最小路径的Dijkstra算法 */
void Dijkstra(LGraph G, int dist[], int path[], Vertex S);
/* 返回未被收录定点中的最小者 */
Vertex FindMinDist(LGraph Graph, int dist[], int collected[]);
/* 返回满足所有条件的距离最近的center */
Vertex FindClstCen(int Ambulance[], int dist[], int path[], Vertex S);
/* 输出路径和所需时间 */
void Output(Vertex Center, int dist, int path[], Vertex S);

int main(){
	int Ns, Na, i, K;
	int Ambulance[11];	/* 用于存储各center的救护车数量 */
	Vertex Pick_up, Center;	/* Pick_up存储求救点，center存储最终响应的派遣中心 */
	LGraph Graph;	/* 存储整个城市的图 */
	int dist[MaxVertexNum], path[MaxVertexNum];	/* 最短路径 */

	scanf("%d%d", &Ns, &Na);	/* 读入Ns和Na */
	for (i = 0; i <= MaxVertexNum - MaxSpotNum; i++){	//初始化救护车数
		Ambulance[i] = 0;
	}
	for (i = 1; i <= Na; i++){	//读入救护车数
		scanf("%d", Ambulance + i);
	}

	Graph = BuildCity(Ns + Na);	//生成图
	scanf("%d", &K);	//读入呼救次数
	for (i = 0; i < K; i++){
		scanf("%d", &Pick_up);
		Dijkstra(Graph, dist, path, Pick_up);	//最短路径算法
		Center = FindClstCen(Ambulance, dist, path, Pick_up);	//根据路径获取派遣中心

		if (Ambulance[Center - MaxSpotNum] != 0){
			Ambulance[Center - MaxSpotNum]--;
			Output(Center, dist[Center], path, Pick_up);
		}
		else {
			printf("All Busy\n");
		}
		
	}
}


LGraph CreateGraph(int VertexNum){
	Vertex V;
	LGraph Graph;

	Graph = (LGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;

	//初始化邻接表头指针，默认定点编号从零开始
	for (V = 0; V < MaxVertexNum; V++){
		Graph->G[V].FirstEdge = NULL;
	}

	return Graph;
}

void InsertEdge(LGraph Graph, Edge E){
	PtrToAdjVNode NewNode;
	//插入边<V1, V2>，为V2建立新的邻接点
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;
	NewNode->Time = E->Time;
	//将V2插入V1的表头
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;

	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V1;
	NewNode->Time = E->Time;
	//将V1插入V2的表头
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
}

LGraph BuildCity(int Nv){
	LGraph Graph;
	Edge E;
	Vertex V;
	int i;
	char ch;

	Graph = CreateGraph(Nv);

	scanf("%d", &(Graph->Ne));	//读入边数

	E = (Edge)malloc(sizeof(struct ENode));	//建立边结点
	for (i = 0; i < Graph->Ne; i++){	//读入边，对于两边的顶点，先读入一个字符判断是否为派遣中心；随后相应地读入数据
		while((ch = getchar()) != 'A' && (ch < '0' || ch > '9'));
		if (ch == 'A'){
			scanf("-%d", &E->V1);
			E->V1 += MaxSpotNum;	//派遣中心从MaxSpotNum开始存储
			scanf("%d%d", &E->V2, &E->Time);
		}
		else {
			E->V1 = ch - '0';
			while((ch = getchar()) != ' '){
				E->V1 = E->V1 * 10 + ch - '0';	//如果只读入了最高位则读入后面的数
			}
			if ((ch = getchar()) == 'A'){
				scanf("-%d", &E->V2);
				E->V2 += MaxSpotNum;	//派遣中心从MaxSpotNum开始存储
				scanf("%d", &E->Time);
			}
			else {
				E->V2 = ch - '0';
				while((ch = getchar()) != ' '){
					E->V2 = E->V2 * 10 + ch - '0';
				}
				scanf("%d", &E->Time);
			}
		}
		InsertEdge(Graph, E);	//插入边
	}
	return Graph;
}

Vertex FindMinDist(LGraph Graph, int dist[], int collected[]){
	/* 返回未被收录点中dist最小者 */
	Vertex MiNv, V;
	int MinDist = INFINITY;

	for (V = 1; V < MaxVertexNum; V++){		
		if (collected[V] == false && dist[V] < MinDist){
			MinDist = dist[V];	//更新最小距离
			MiNv = V;	//更新对应顶点
		}
	}
	if (MinDist < INFINITY)	//找到最小dist
		return MiNv;	//返回对应的顶点下标
	else return ERROR;	//若这样的点不存在，返回错误标记
}

void Dijkstra(LGraph Graph, int dist[], int path[], Vertex S){
	int collected[MaxVertexNum];
	Vertex V;
	PtrToAdjVNode W;

	/* 初始化：边不存在用INFINITY表示 */
	for (V = 0; V < MaxVertexNum; V++){
		dist[V] = INFINITY;
		path[V] = -1;
		collected[V] = false;
	}

	/* 起点到目标点距离为零 */
	dist[S] = 0;

	while(1){
		V = FindMinDist(Graph, dist, collected); //V为未被收录点中dist最小者
		if (V == ERROR){	//这样的V不存在
			break;
		}
		collected[V] = true;	//V被收录
		
		for (W = Graph->G[V].FirstEdge; W; W = W->Next){
			/* 若从V到其他点的距离更小 */
			if (collected[W->AdjV] == false && dist[V] + W->Time < dist[W->AdjV]){
				dist[W->AdjV] = dist[V] + W->Time;	//更新dist
				path[W->AdjV] = V;	//更新S到W的路径
			}
		}
	}
}

Vertex FindClstCen(int Ambulance[], int dist[], int path[], Vertex S){
	int i;
	Vertex ClstCen = 1, pass;	//pass用于追踪路径，计算经过的道路数
	int count1, count2;		//用于比较道路数

	for (i = 2; i <= 10; i++){
		if (Ambulance[i] == 0){		//救护车数为零，跳过
			continue;
		}
		if (dist[ClstCen + MaxSpotNum] > dist[i + MaxSpotNum]){		//距离更近，更新
			ClstCen = i;
		}
		else if (dist[ClstCen + MaxSpotNum] = dist[i + MaxSpotNum]){
			if (Ambulance[ClstCen] < Ambulance[i]){		//救护车数更多，更新
				ClstCen = i;
			}
			else if (Ambulance[ClstCen] == Ambulance[i]){
				count1 = count2 = 0;
				pass = ClstCen + MaxSpotNum;
				while (pass != S){		//循环跟踪道路，记录道路数
					count1++;
					pass = path[pass];
				}
				pass = i + MaxSpotNum;
				while (pass != S){
					count2++;
					pass = path[pass];
				}

				if (count1 > count2){	//经过道路数更少，更新
					ClstCen = i;
				}
			}
		}
	}

	return ClstCen + MaxSpotNum;	//返回的是派遣中心存储的位置
}

void Output(Vertex Center, int dist, int path[], Vertex S){
	Vertex pass = Center;	//用于跟踪循环输出经过道路
	printf("A-%d", Center - MaxSpotNum);
	do{
		pass = path[pass];
		printf(" %d", pass);
	} while (pass != S);
	printf("\n");

	printf("%d\n", dist);
}