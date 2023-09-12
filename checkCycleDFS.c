#include "adjMatrix.h"
#define white 0
#define gray 1
#define black 2
#define NIL -1

void dfs(int *adjMat, int v, type){
	
	int *parent, *color;
	int i;
	
	parent = (int*)malloc(v*sizeof(int));
	color = (int*)malloc(v*sizeof(int));
	
	for(i=0; i<v; i++){
		parent[i] = NIL;
		color[i] = white;
	}
	

	dfsVisit(adjMat, v, 0, parent, color, type);
	
	for(i=1; i<v; i++){
		if(color[i] == white)
			dfsVisit(adjMat, v, i, parent, color, type);
	}
	
	printf("\n\nParent  Child\n");
	for(i=0; i<v; i++){
		printf("  %d\t  %d\n", parent[i], i);	
	}
	
}

void dfsVisit(int *adjMat, int v, int u, int *parent, int *color, type){
	color[u] = gray;
	printf("%d, ", u);
	
	int i;
	
	for(i=v-1; i>=0; i--){ // adjMat[u][i] > 0 i.e. vertex i is adjacent to vertex u
		
		if( *(adjMat+(u*v)+i) > 0 && color[i]==white){  // if adjacent vertex color is white then
			parent[i] = u;
			dfsVisit(adjMat, v, i, parent, color, type);
		}
		
		else if(color[i]==gray && type>2){  // directed
			printf("\nBack edge found at %d, %d", u, v);
			printf("\nGraph contains a cycle");
			exit(1); // terminates the program
		}
		
		else if(parent[u] != i && type<3){   // un-directed
			printf("\nBack edge found at %d, %d", u, v);
			printf("\nGraph contains a cycle");
			exit(1); // terminates the program
		}
		
	}
	
	color[u] = black;
}


int main(){
		
	int *adjMat, v, type;
	adjMat = initializeGraph(&v);
	type = inputGraph(adjMat, v);
	displayGraph(adjMat, v);
	
	dfs(adjMat, v, type);
	
	return 0;
}
