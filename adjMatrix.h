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
	printf("3. Directed-Unweighted\n");
	printf("4. Directed-Weighted\n");
	printf("5. Exit\n");
	
	while(1){
		printf("Enter choice (-999 to stop): ");
		scanf("%d", &choice);
		if(choice>0 && choice<6) break;
		printf("Invalid choice!\n");
	}
	
	if(choice==5) return 0; // 0 means no graph given
	
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
