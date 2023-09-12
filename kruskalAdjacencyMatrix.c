#include<stdio.h>
#include<stdlib.h>

int* initializeGraph(int*);
void displayGraph(int*, int);
int inputGraph(int*, int);

int* initializeGraph(int *v){
	int i, j, ver, *adjMat;
	
	while(1){
		printf("Enter the number of vertices: ");
		scanf("%d", &ver);
		if(ver>0) break;
		printf("Invalid number of vertices given!\n");
	}
	
	(*v) = ver;
	
	adjMat=(int*)malloc(ver*ver*sizeof(int)); // adjacency Matrix created
	printf("The vertices are: ");
	for(i=0; i<ver; i++){
		if(i!=0) printf(", ");
		printf("%d", i);
		for(j=0; j<ver; j++)
			*(adjMat+(i*ver)+j)=0; // adjMat[i][j]=0
	}
	printf("\n");
	return adjMat;
}

void displayGraph(int *adjMat, int v){
	if(adjMat==NULL || v<=0) return; // invalid matrix for display  [ not initialised ]
	
	int i, j;
	
	printf("\nAdjacency Matrix\n");
	for(i=0; i<v; i++){
		for(j=0; j<v; j++)
			printf("%d\t", *(adjMat+(i*v)+j) ); // adjMat[i][j]
		printf("\n");
	}
	printf("\n");
}

int inputGraph(int *adjMat, int v){
	if(adjMat==NULL || v<=0) return 0; // invalid matrix for display  [ not initialised ]
	
	int choice, s, e, w;
	
	printf("\n1. Undirected-Unweighted\n");
	printf("2. Undirected-Weighted\n");
	printf("3. Exit\n");
	
	while(1){
		printf("Enter choice (-999 to stop): ");
		scanf("%d", &choice);
		if(choice>0 && choice<4) break;
		printf("Invalid choice!\n");
	}
	
	if(choice==3) return 0; // 0 means no graph given
	
	printf("\n");
	
	while(1){
		// TAKING start and end vertices from user	
		while(1){ // taking start vertex from user
			printf("Enter start vertex: ");
			scanf("%d", &s);
			
			if(s==-999) return choice; // no more edge to add therefore return
			
			if(s>=0 && s<v) break;
			printf("Invalid start vertex!\n");
		}
		
		
		while(1){ // taking end vertex from user
			printf("Enter end vertex: ");
			scanf("%d", &e);
			if(e>=0 && e<v) {
				break; // un-comment this line to allow self loop
				if(s!=e) break; // self loop not allowed
			}
			printf("Invalid end vertex!\n");
		}
	
		if(choice==1 || choice==3){  // unweighted
	
			*(adjMat+(s*v)+e)=1; // adjMat[s][e]=1
			if(choice==1) *(adjMat+(e*v)+s)=1; // adjMat[e][s]=1 undirected-unweighted

		}	
		else { // weighted  [ choice=2 OR choice=4 ]
	
			while(1){ // taking start vertex from user
				printf("Enter weight: ");
				scanf("%d", &w);
				if(w>0) break;
				printf("Invalid weight!\n");
			}
		
			*(adjMat+(s*v)+e)=w; // adjMat[s][e]=weight
			if(choice==2) *(adjMat+(e*v)+s)=w; // adjMat[e][s]=weight  undirected-weighted
		}
		
	}
	
	return choice;
}

///////////////////////////////////////////////////////////////////////

int findSet(int *parent, int x){
	if( x != parent[x])
		parent[x] = findSet(parent, parent[x]);
	return parent[x];
}

void makeSet(int *parent, int *rank, int x){
	parent[x] = x;
	rank[x] = 0;
}

void link(int *parent, int *rank, int x, int y){
	if( rank[x] > rank[y] ) // line 1
		parent[y] = x; // line 2
	else {
		parent[x] = y; // line 3
		if( rank[x] == rank[y] ) // line 4
			rank[y] = rank[y]+1; // line 5
	}
}


void mstKruskal(int *adjMat, int v){
	
	int i, j, t, edgeNo;
	
	int *parent = (int*)malloc(v*sizeof(int));
	int *rank = (int*)malloc(v*sizeof(int));
	
	for(i=0; i<v; i++) // implementation of line 2-3
		makeSet(parent, rank, i);
	
	// Counting number of edges in the graph
	edgeNo=0;
	for(i=0; i<v-1; i++)
		for(j=i+1; j<v; j++)
			if( *(adjMat+(i*v)+j) > 0) edgeNo++; // if( adjMat[i][j]>0) edgeNo++
	
	// 2D array of dimension edge x 3 created
	int *edgeList = (int*)malloc(edgeNo*3*sizeof(int));
	
	
	t=0;
	for(i=0; i<v-1; i++){
		for(j=i+1; j<v; j++){
			if( *(adjMat+(i*v)+j) > 0) { // edge found from i to j
			
				*(edgeList+(t*3)+0) = i; // edgeList[t][0] = i, start vertex
				*(edgeList+(t*3)+1) = j; // edgeList[t][1] = j, end vertex
				*(edgeList+(t*3)+2) = *(adjMat+(i*v)+j); // edgeList[t][2] = adjMat[i][j], weight
				
				t++; // points to the row of the edgeList
			}
		}
	}
	
	// sorting the edge list with respect to weight column using bubble sort
	for(i=0; i<edgeNo-1; i++){ // line 4 implementation
		
		for(j=0; j<edgeNo-1-i; j++){
			
			// if( edgeList[j][2] > edgeList[j+1][2] )
			
			if( *(edgeList+(j*3)+2) > *(edgeList+((j+1)*3)+2) ){
				
				t = *(edgeList+(j*3)+0); // t = edgeList[j][0]
				*(edgeList+(j*3)+0) = *(edgeList+((j+1)*3)+0); // edgeList[j][0] = edgeList[j+1][0]
			    *(edgeList+((j+1)*3)+0) = t; // edgeList[j+1][0] = t
				
				t = *(edgeList+(j*3)+1); // t = edgeList[j][1]
				*(edgeList+(j*3)+1) = *(edgeList+((j+1)*3)+1); // edgeList[j][1] = edgeList[j+1][1]
			    *(edgeList+((j+1)*3)+1) = t; // edgeList[j+1][1] = t
			    
			    t = *(edgeList+(j*3)+2); // edgeList[j][2]
				*(edgeList+(j*3)+2) = *(edgeList+((j+1)*3)+2);  // edgeList[j][2] = edgeList[j+1][2]
			    *(edgeList+((j+1)*3)+2) = t; // edgeList[j+1][2] = t

			}
		}
		
	}

	printf("\nMST\n");
	for(i=0; i<edgeNo; i++){ // implementation of line 5  , u=edgeList[i][0], v=edgeList[i][1], w=edgeList[i][2]
		
		if( findSet( parent, *(edgeList+(i*3)+0) ) != findSet( parent, *(edgeList+(i*3)+1) ) ) { // line 6
			
			printf("%d -> %d  w[%d]\n", *(edgeList+(i*3)+0), *(edgeList+(i*3)+1), *(edgeList+(i*3)+2) );
			
			link(parent, rank, findSet(parent, *(edgeList+(i*3)+0) ) , findSet(parent, *(edgeList+(i*3)+1) ) );
		}
	
	}
	
	
	
}



int main(){
	
	int *adjMat, v, type;
	adjMat = initializeGraph(&v);
	type = inputGraph(adjMat, v);
	displayGraph(adjMat, v);
	
	
	mstKruskal(adjMat, v);
	
	return 0;
}

