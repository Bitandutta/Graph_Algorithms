#include "adjMatrix.h"

int* createDegree(int *adjMat, int v, int type){

	if(adjMat==NULL || type==0) return; // no graph
	
	int *degree = (int*)malloc(v*2*sizeof(int));  // v x 2 matrix
	
	int i, j;
	
	for(i=0; i<v; i++) {
		*(degree+(i*2)+0)=0;
		*(degree+(i*2)+1)=0;
	}
	
	if(type<3){ // undirected	
		for(i=0; i<v; i++){
			for(j=0; j<v; j++){
				if(*(adjMat+(i*v)+j)>0) { // adjMat[i][j] > 0  then i is connected to j
					*(degree+(i*2)+0) += 1; // degree[i][0] += 1    [indegree = outdegree for undirected]
					*(degree+(i*2)+1) += 1; // degree[i][1] += 1
				}
			}
		}
	}
	else{ // directed	
		for(i=0; i<v; i++){
			for(j=0; j<v; j++){
				if(*(adjMat+(i*v)+j)>0) { // adjMat[i][j] > 0  then i is connected to j
						*(degree+(i*2)+1) += 1; // degree[i][1] += 1 [ i th vertex outdegree ++]
						*(degree+(j*2)+0) += 1; // degree[j][0] += 1 [ j th vertex indegree ++]
					}
				}	
			}
		}
	}
	
	return degree;
}

void displayDegree(int *degree, int v){
	if(v<=0) return;
	printf("Vertex  In-degree  Out-degree\n");
	
	int i;
	
	for(i=0; i<v; i++)
		printf("  %d\t    %d\t\t%d\n", i, *(degree+(i*2)+0), *(degree+(i*2)+1));
	
	printf("\n");
}

/*
for(i=0; i<v; i++){
	printf("%d\t", i);
	for(j=0; j<2; j++)
		printf("%d\t", *(degree+(i*2)+j));
	printf("\n");
}
*/

int countIsolatedVertices(adjMat, v, type){
	int *degree = createDegree(adjMat, v, type);
	
	int i, iv=0;
	for(i=0; i<v; i++){
		if( *(degree+(i*2)+0)==0 && *(degree+(i*2)+1)==0){ // i th vertex is isolated
			if(iv==0) printf("Isolated Vertices are: ");
			else printf(", ");
			iv++;
			printf("%d", i);
		}
	}
	if(iv>0) printf("\t");
	return iv;
}

int countPendantVertices(adjMat, v, type){
	int *degree = createDegree(adjMat, v, type);
	
	int i, pv=0;
	for(i=0; i<v; i++){
		if(type<3){ // undirected
			if( *(degree+(i*2)+0)==1 && *(degree+(i*2)+1)==1){ // i th vertex is pendant
				if(pv==0) printf("Pendant Vertices are: ");
				else printf(", ");
				pv++;
				printf("%d", i);
			}
		}
		
		else{ // directed
			if( *(degree+(i*2)+0) + *(degree+(i*2)+1) == 1 ){ // i th vertex is isolated
			 	if(pv==0) printf("Pendant Vertices are: ");
			 	else printf(", ");
				pv++;
				printf("%d", i);
			}
		}
	}
	if(pv>0) printf("\t");
	return pv;
}

void displayTotalDegree(adjMat, v, type){
	int *degree = createDegree(adjMat, v, type);
	
	int m1, m2, i;
	
	if(type<3){ // undirected
		m1 = *(degree + (0*2) + 0); // m1=degree[0][0]   m1 <- maximum
		m2 = *(degree + (0*2) + 0); // m2=degree[0][0]   m2 <- minimum
		
		for(i=1; i<v; i++){
			
			if( *(degree + (i*2) + 0) > m1 ) // degree[i][0] > m1
				m1 = *(degree + (i*2) + 0);
			
			if( *(degree + (i*2) + 0) < m2 ) // degree[i][0] < m2
				m2 = *(degree + (i*2) + 0);
			
		}
		printf("\nMaximum Degree = %d\nMinimum Degree = %d\n", m1, m2);
	}
	else{ // directed
		m1 = *(degree + (0*2) + 0); // m1=degree[0][0]   m1 <- maximum in degree
		m2 = *(degree + (0*2) + 1); // m2=degree[0][1]   m2 <- maximum out degree
		
		for(i=1; i<v; i++){
			
			if( *(degree + (i*2) + 0) > m1 ) // degree[i][0] > m1
				m1 = *(degree + (i*2) + 0);
			
			if( *(degree + (i*2) + 1) > m2 ) // degree[i][1] < m2
				m2 = *(degree + (i*2) + 1);
			
		}
		printf("\nMaximum In-Degree = %d\nMaximum Out-Degree = %d\n", m1, m2);
	}
}

int isSelfLoop(int *adjMat, int v){
	int i, sl=0;
	for(i=0; i<v; i++){
		if( *(adjMat+(i*v)+i) > 0 ){ // adjMat[i][i] > 0
			
			if(sl==0) printf("Vertices with self loops are: ");
			else printf(", ");
			
			printf("%d", i);
			sl++;
		}
	}
	if(sl>0) printf("\t");
	return sl;
}

int main(){
	int *adjMat=NULL, v=0, type;

	adjMat = initializeGraph(&v);
	type = inputGraph(adjMat, v);
	displayGraph(adjMat, v, type);
	
	int *degree = createDegree(adjMat, v, type);
	displayDegree(degree, v);
	
	printf("Total Self loop Found = %d\n", isSelfLoop(adjMat, v));
	
	printf("Total isolated Vertices Found = %d\n", countIsolatedVertices(adjMat, v, type));
	
	printf("Total pendant Vertices Found = %d\n", countPendantVertices(adjMat, v, type));
	
	displayTotalDegree(adjMat, v, type);
	
	return 0;
}
