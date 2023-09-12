#include "incedenceMatrix.h"

int* incedenceToAdjacency(int *incMat, int v, int e, int type){
	
	if(incMat==NULL || v<=0 || type==0) return NULL;
	
	int *adjMat = (int*)malloc(v*v*sizeof(int));
	int i, j, start, end, weight;
	
	// initializing the Adjacency Matrix
	for(i=0; i<v; i++)
		for(j=0; j<v; j++)
			*(adjMat+(i*v)+j)=0; // adjMat[i][j]=0
			
			
	for(i=0; i<e; i++){ // column number  [ edge names ]
	
		start=-1, end=-1;
	
		if(type<3){ // undirected graph

			for(j=0; j<v; j++){ // row number  [ vertex names ]
				
				if( *(incMat+(j*e)+i) > 0){ // vertex j is connected to edge i
					if(start==-1){ // if start is -1 then the j vertex is the starting vertex
						start=j;
					}
					else{ // if start is not -1 that means we already have start vertex thus j is end vertex
						end=j;
						weight = *(incMat+(j*e)+i); // incMat[j][i]
						break;
					}
				}
			}
			
			if(end==-1) end=start; // if self loop found
			
			
			*(adjMat+(start*v)+end)=weight; // adjMat[start][end]=weight
			*(adjMat+(end*v)+start)=weight; // adjMat[end][start]=weight

		}
		else{ // directed graph
			
			for(j=0; j<v; j++){ // row number  [ vertex names ]
				
				if(start != -1 && end != -1) break;
				
				if( *(incMat+(j*e)+i) != 0){ // vertex j is connected to edge i
					
					if( *(incMat+(j*e)+i) > 0){ // if weight is +ve that means vertex j is start vertex
						start=j;
						weight = *(incMat+(j*e)+i); // incMat[j][i]
					}
					else{ // if weight is -ve that means vertex j is end vertex
						end=j;
					}
				}
			}
			
			if(end==-1) end=start; // if self loop found

			*(adjMat+(start*v)+end)=weight; // adjMat[start][end]=weight

		}
	}
	
	return adjMat;
}

void displayAdjacencyMatrix(int *adjMat, int v){
	int i, j;
	printf("\nAdjacency Matrix\n");
	for(i=0; i<v; i++){
		for(j=0; j<v; j++) printf("%d\t", *(adjMat+(i*v)+j));
		printf("\n");
	}
}

int main(){
	
	int *incMat, v, e, type;
	incMat = initializeGraph(&v, &e);
	type = inputGraph(incMat, v, e);
	displayGraph(incMat, v, e);
	// convert Incedence Matrix into adjacency Matrix
	int *adjMat;
	adjMat = incedenceToAdjacency(incMat, v, e, type);
	displayAdjacencyMatrix(adjMat, v);
}
