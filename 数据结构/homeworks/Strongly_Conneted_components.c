#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 10  /* maximum number of vertices */
typedef int Vertex;     /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode {
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

void PrintV( Vertex V )
{
   printf("%d ", V);
}

void Dfs(Graph G, int *Number, int Root, int *Visited, int* Count);
Graph Reverse(Graph G);
void Dfs_r(Graph G, int Root, int *Visited);
void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) );
Graph Read();

int main()
{
    Graph G = Read();
    StronglyConnectedComponents( G, PrintV );
    return 0;
}

Graph Read(){
    int E, V, i;
    int w, v;
    scanf("%d %d", &V, &E);
    Graph G = (Graph)malloc(sizeof(struct GNode));
    G->NumOfEdges = E;
    G->NumOfVertices = V;
    G->Array = (PtrToVNode*)malloc(4 * sizeof(PtrToVNode));
    PtrToVNode P;

    for (i = 0; i < G->NumOfEdges; i++){
        G->Array[i] = NULL;
    }

    for (i = 0; i < G->NumOfEdges; i++){
        scanf("%d %d", &w, &v);
        P = (PtrToVNode)malloc(sizeof(struct VNode));
        P->Vert = v;
        P->Next = G->Array[w];
        G->Array[w] = P;
    }
    return G;
}

void StronglyConnectedComponents(Graph G, void (*visit)(Vertex V)){
    int *Number, i, *Visited, Count = 0;
    Graph Gr;
    Number = (int*)malloc(G->NumOfVertices * sizeof(int));
    Visited = (int*)malloc(G->NumOfVertices * sizeof(int));

    for (i = 0; i < G->NumOfVertices; i++){
        Visited[i] = 0;
    }

    for (i = 0; i < G->NumOfVertices; i++){
        if (!Visited[i]){
            Dfs(G, Number, i, Visited, &Count);
        }
    }
    Gr = Reverse(G);
    
    for (i = 0; i < Gr->NumOfVertices; i++){
        Visited[i] = 0;
    }
    for (i = Gr->NumOfVertices - 1; i >= 0; i--){
        if (!Visited[Number[i]]){
            Dfs_r(Gr, Number[i], Visited);
            printf("\n");
        }
    }
}

void Dfs(Graph G, int *Number, int Root, int *Visited, int* Count){
    PtrToVNode P;
    Visited[Root] = 1;
    for (P = G->Array[Root]; P; P = P->Next){
        if (!Visited[P->Vert]){
            if (G->Array[P->Vert]){
                Dfs(G, Number, P->Vert, Visited, Count);
            }
        }
    }
    Number[*Count] = Root;
    (*Count)++;
}

Graph Reverse(Graph G){
    int i;
    PtrToVNode P, Pr;
    Graph Gr;
    Gr = (Graph)malloc(sizeof(struct GNode));
    Gr->NumOfEdges = G->NumOfEdges;
    Gr->NumOfVertices = G->NumOfVertices;
    Gr->Array = (PtrToVNode*)malloc(G->NumOfVertices * sizeof(PtrToVNode));

    for (i = 0; i < Gr->NumOfVertices; i++){
        Gr->Array[i] = NULL;
    }

    for (i = 0; i < Gr->NumOfVertices; i++){
        for (P = G->Array[i]; P; P = P->Next){
            Pr = (PtrToVNode)malloc(sizeof(struct VNode));
            Pr->Vert = i;
            Pr->Next = Gr->Array[P->Vert];
            Gr->Array[P->Vert] = Pr;
        }
    }

    return Gr;
}

void Dfs_r(Graph G, int Root, int *Visited){
    PtrToVNode P;
    Visited[Root] = 1;
    printf("%d ", Root);
    for (P = G->Array[Root]; P; P = P->Next){
        if (!Visited[P->Vert]){
            if (G->Array[P->Vert]){
                Dfs_r(G, P->Vert, Visited);
            }
        }
    }
}
