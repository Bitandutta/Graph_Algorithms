#include "adjMatrix.h"
#define unvisited 0
#define visited 1
#define processed 2
#define NIL -1

void dfs(int *adjMat, int v){
	
	int *parent, *status;
	int i, source;
	
	parent = (int*)malloc(v*sizeof(int));
	status = (int*)malloc(v*sizeof(int));
	
	for(i=0; i<v; i++){
		parent[i] = NIL;
		status[i] = unvisited;
	}
	
	printf("\nEnter starting vertex: ");
	scanf("%d", &source);

	dfsVisit(adjMat, v, source, parent, status);
	
	printf("\n\nParent  Child\n");
	for(i=0; i<v; i++){
		printf("  %d\t  %d\n", parent[i], i);	
	}
	
}

void dfsVisit(int *adjMat, int v, int u, int *parent, int *status){
	status[u] = visited;
	printf("%d, ", u);
	
	int i;
	// for(i=0; i<v; i++)
	for(i=v-1; i>=0; i--){ // adjMat[u][i] > 0 i.e. vertex i is adjacent to vertex u
		if( *(adjMat+(u*v)+i) > 0 && status[i]==unvisited){  // if adjacent vertex color is white then
			parent[i] = u;
			dfsVisit(adjMat, v, i, parent, status);
		}
	}
	
	status[u] = processed;
}


int main(){
		
	int *adjMat, v, type;
	adjMat = initializeGraph(&v);
	type = inputGraph(adjMat, v);
	displayGraph(adjMat, v);
	
	dfs(adjMat, v);
	
	return 0;
}
