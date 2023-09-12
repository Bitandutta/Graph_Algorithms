#include "adjMatrix.h"

int* adjacencyToIncedence(int *adjMat, int v, int type, int *edge){ // return's incedence matrix
	
	if(adjMat==NULL) return NULL;
	int i, j, w, edgeNumber;
	
	// edge counting from adjacency Matrix
	*edge=0;  
	if(type<3){ // undirected
		for(i=0; i<v; i++)
			for(j=i; j<v; j++)
				if(*(adjMat+(i*v)+j) > 0) (*edge)++; // adjMat[i][j]>0 then edge++
	}
	else { // directed graph
		for(i=0; i<v; i++)
			for(j=0; j<v; j++)
				if(*(adjMat+(i*v)+j) > 0) (*edge)++;
	}
	
	// creating incedence matrix	
	int *incMat	= (int*)malloc(v*(*edge)*sizeof(int)); // (vertex x edge) matrix created
	
	// initializing incedence matrix
	for(i=0; i<v; i++)
		for(j=0; j<(*edge); j++)
			*(incMat+(i*(*edge))+j)=0; // incMat[i][j]=0
	
	
	// converting adjacency matrix to incedence
	edgeNumber=0;
	
	if(type<3){ // undirected graph
		for(i=0; i<v; i++){
			for(j=i; j<v; j++){
				w=*(adjMat+(i*v)+j); // w = adjMat[i][j]
				if(w>0) { // edge found from i to j
					*(incMat+(i*(*edge))+edgeNumber)=w; // incMat[i][edgeNumber] = w
					*(incMat+(j*(*edge))+edgeNumber)=w; // incMat[j][edgeNumber] = w
					edgeNumber++; 
				}
			}
		}
	}
	else { // directed graph
		for(i=0; i<v; i++){
			for(j=0; j<v; j++){
				w=*(adjMat+(i*v)+j); // adjMat[i][j]
				if(w>0) { // edge found from i to j
					*(incMat+(j*(*edge))+edgeNumber)=(-1*w); // incMat[j][edgeNumber] = w
					/* if self loop found then first -w is kept in (j,edgeNumber)
						 then +w in (i,edgeNumber) as i=j so -w is  replaced by +w */
					*(incMat+(i*(*edge))+edgeNumber)=w; // incMat[i][edgeNumber] = w
					edgeNumber++; 
				}
			}
		}
	}
	
	return incMat;
}

void displayIncedenceMatrix(int *incMat, int v, int edge){
	int i, j;
	
	printf("\nIncedence Matrix\n");
	printf("    ");
	for(i=0; i<edge; i++) printf("%d\t", i);
	printf("\n");
	for(i=0; i<edge; i++) printf("-------", i);
	printf("\n");
	
	for(i=0; i<v; i++){
		printf("%d | ", i);
		for(j=0; j<edge; j++)
			printf("%d\t", *(incMat+(i*edge)+j) ); // incMat[i][j]	
		printf("\n");
	}
	printf("\n");
}


int main(){
	// adjacency matrix created and graph input is taken
	int *adjMat, v, type;
	adjMat = initializeGraph(&v);
	type = inputGraph(adjMat, v);
	displayGraph(adjMat, v, type); // adjacency matrix displayed
	
	// adjacency matrix is converted to incedence matrix
	int *incMat, edge;
	incMat = adjacencyToIncedence(adjMat, v, type, &edge);
	displayIncedenceMatrix(incMat, v, edge);
	
	return 0;
}

