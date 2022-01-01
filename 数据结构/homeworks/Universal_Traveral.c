#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_NODES 500
#define INFINITY 2147483648
int e;  // number of edges
int N = 0; // number of satellies
int capacity[MAX_NODES][MAX_NODES] = {0}; // capacity matrix
char name[MAX_NODES][4]; // store names of satellites

int find_serial(char *target);
int find_min(int *dist, bool *found);
int max_flow();
bool Dijkstra(int *path);
void read_input();
int minimum(int x, int y);
int min_capacity(int *path);

int main(){
	read_input();
	printf("%d", max_flow());
	return 0;
}

int minimum(int x, int y){
    return x < y ? x : y;  // returns minimum of x and y
}

int find_serial(char *target){
	int i;
	for (i = 0; i < N; i++){
		if (!strcmp(target, name[i])){
			return i;
		}
	}
	strcpy(name[N], target);
	return N++;
}

int max_flow(){
	int satellite, cap;
	int max_flow = 0;
	int *path;
	path = (int*)malloc(N * sizeof(int));
	while (Dijkstra(path)){
		cap = min_capacity(path);
		max_flow += cap;
		for (satellite = 1; path[satellite] != -1; satellite = path[satellite]){
			capacity[path[satellite]][satellite] -= cap;
			capacity[satellite][path[satellite]] += cap;
		}
	}
	free(path);
	return max_flow;
}

int min_capacity(int *path){
	int cap = INFINITY;
	int vertex;
	for (vertex = 1; path[vertex] != -1; vertex = path[vertex]){
		cap = minimum(cap, capacity[path[vertex]][vertex]);
	}
	return cap;
}

bool Dijkstra(int *path){
	int i, vertex, *dist;
	bool *found;
	found = (bool*)malloc(N * sizeof(bool));
	dist = (int*)malloc(N * sizeof(int));
	for (i = 0; i < N; i++){
		dist[i] = INFINITY;
		found[i] = false;
		path[i] = -1;
	}

	dist[0] = 0;
	while ((vertex = find_min(dist, found)) != -1){
		found[vertex] = true;
		for (i = 0; i < N; i++){
			if (capacity[vertex][i] == 0){
				continue;
			}
			else{
				if (dist[vertex] + capacity[vertex][i] < dist[i]){
					dist[i] = dist[vertex] + capacity[vertex][i];
					path[i] = vertex;
				}
			}
		}
	}
	
	free(found);
	free(dist);
	return (path[1] != -1);
}

int find_min(int *dist, bool *found){
	int vertex = -1, i, min;
	min = INFINITY;

	for (i = 0; i < N; i++){
		if (found[i]){
			continue;
		}
		else{
			if (dist[i] < min){
				min = dist[i];
				vertex = i;
			}
		}
	}

	return vertex;
}

void read_input(){
	char satellite1[4], satellite2[4];
	int c, i;
	scanf("%s%s", satellite1, satellite2);
	find_serial(satellite1), find_serial(satellite2);
	scanf("%d", &e);

	for (i = 0; i < e; i++){
		scanf("%s%s%d", satellite1, satellite2, &c);
		capacity[find_serial(satellite1)][find_serial(satellite2)] = c;
	}
}
