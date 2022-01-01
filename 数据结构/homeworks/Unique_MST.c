#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_NODES 501
#define MAX_VERTICES 10000
struct ENode{
	int V1;
	int V2;
	int Weight;
	bool IsEdge;
};
typedef struct ENode *Edge;

int N, M;
int flag = 1;
int Weight = 0;
int Vertex[MAX_NODES];
Edge edge[MAX_VERTICES];

void read_input();
void Kruskal();
void output_cpn();
void sort();
int find(int vertex);
void Union();
void swap(int i, int j);

int main(){
	read_input();
	Kruskal();
	output_cpn();
	return 0;
}

void read_input(){
	int i, V1, V2, weight;
	scanf("%d %d", &N, &M);
	for (i = 0; i < M; i++){
		scanf("%d %d %d", &V1, &V2, &weight);
		edge[i] = (Edge)malloc(sizeof(struct ENode));
		edge[i]->V1 = V1;
		edge[i]->V2 = V2;
		edge[i]->Weight = weight;
		edge[i]->IsEdge = false;
	}
	sort(0, M - 1);
}

void swap(int i, int j){
	Edge tmp;
	tmp = edge[i];
	edge[i] = edge[j];
	edge[j] = tmp;
}

void sort(int start, int end){
	if (start >= end){
		return ;
	}
	int mid = edge[end]->Weight;
	int left = start, right = end - 1;
	while (left < right)
	{
		while (edge[left]->Weight < mid && left < right)
		{
			left++;
		}
		while (edge[right]->Weight >= mid && left < right)
		{
			right--;
		}
		swap(left, right);
	}
	if (edge[left]->Weight >= edge[end]->Weight)
	{
		swap(left, end);
	}
	else
	{
		left++;
	}
	if (left)
	{
		sort(start, left - 1);
	}
	sort(left + 1, end);
}

void Kruskal(){
	int i, j;
	
	for (i = 1; i <= N; i++){
		Vertex[i] = -1;
	}

	for (i = 0; i < M; i++){
		if ((i < M - 1) && (edge[i + 1]->Weight == edge[i]->Weight) && flag == 1){
			j = i + 1;
			if (find(edge[i]->V1) == find(edge[i]->V2)){
				continue;
			}
			edge[i]->IsEdge = true;
			while((j < M) && (edge[j]->Weight == edge[i]->Weight)){
				if (find(edge[j]->V1) != find(edge[j]->V2)){
					edge[j]->IsEdge = true;
				}
				j++;
			}
		}
        
		if (find(edge[i]->V1) != find(edge[i]->V2)){
			Union(edge[i]->V1, edge[i]->V2);
			Weight += edge[i]->Weight;
		}
		else{
			if (edge[i]->IsEdge){
				flag = 0;
			}
			continue;
		}
	}
}

int find(int vertex){
	if (Vertex[vertex] < 0){
		return vertex;
	}
	else{
		return (Vertex[vertex] = find(Vertex[vertex]));
	}
}

void Union(int vertex1, int vertex2){
	if (Vertex[find(vertex1)] < Vertex[find(vertex2)]){
		Vertex[find(vertex1)] += Vertex[find(vertex2)];
		Vertex[find(vertex2)] = find(vertex1);
	}
	else{
		Vertex[find(vertex2)] += Vertex[find(vertex1)];
		Vertex[find(vertex1)] = find(vertex2);
	}
}

void output_cpn(){
	int i;
	int count = 0;
	for (i = 1; i <= N; i++){
		if (Vertex[i] < 0){
			count++;
		}
	}
	if(count > 1){
		printf("No MST\n%d", count);
	}
	else{
		printf("%d\n", Weight);
		if (flag){
			printf("Yes");
		}
		else{
			printf("No");
		}
	}
}
