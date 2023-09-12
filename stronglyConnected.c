#include "adjMatrix.h"


int checkStronglyConnected(int *adjMat, int v){
	
	int i, j, sc;

	sc=1;
	for(i=0; i<v; i++){
		
		for(j=0; j<v; j++){
		
			if(i==j) continue; // do not check in self loop
			
			if( *(adjMat+(i*v)+j) == 0 ) { // adjMat[i][j] == 0 no edge from i to j
				sc=0;
				break;
			}
		}
		
	}
	
	return sc;
}


int main(){
	
	int v, type, *adjMat=NULL;
	adjMat = initializeGraph(&v);
	type = inputGraph(adjMat, v);
	displayGraph(adjMat, v);
	
	
	if( checkStronglyConnected(adjMat, v) )
		printf("\nStrongly Connected");
	else
		printf("\nNot strongly connected");
	
	return 0;
}
