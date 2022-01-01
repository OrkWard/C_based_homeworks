#include <stdint.h>
#include "LGraph.h"

LGraph ReadG(); /* details omitted */

bool IsTopSeq( LGraph Graph, Vertex Seq[] );

int main()
{
    int i, j, N;
    Vertex Seq[MaxVertexNum];
    LGraph G = ReadG();
    scanf("%d", &N);
    for (i=0; i<N; i++) {
        for (j=0; j<G->Nv; j++)
            scanf("%d", &Seq[j]);
        if ( IsTopSeq(G, Seq)==true ) printf("yes\n");
        else printf("no\n");
    }

    return 0;
}

bool IsTopSeq(LGraph Graph, Vertex Seq[]){
	int InDegree[MaxVertexNum];
	Vertex V;
	PtrToAdjVNode W;

	for (V = 0; V < Graph->Nv; V++){
		InDegree[V] = 0;
	}

	for (V = 0; V < Graph->Nv; V++){
		for (W = Graph->G[V].FirstEdge; W; W = W->Next){
			InDegree[W->AdjV]++;
		}
	}

	for (V = 0; V < Graph->Nv; V++){
		if (InDegree[Seq[V] - 1] != 0)	break;
		for(W = Graph->G[Seq[V] - 1].FirstEdge; W; W = W->Next){
			InDegree[W->AdjV]--;
		}
	}

	if (V == Graph->Nv) return true;
	else return false;
}