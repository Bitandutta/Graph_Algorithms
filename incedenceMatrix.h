#include<stdio.h>
#include<stdlib.h>

int* initializeGraph(int*, int*);
void displayGraph(int*, int, int);
int inputGraph(int*, int, int);

int* initializeGraph(int *v, int *e){
	int i, j, ver, ed, *incMat;
	
	while(1){
		printf("Enter the number of vertices: ");
		scanf("%d", &ver);
		if(ver>0) break;
		printf("Invalid number of vertices given!\n");
	}
	
	while(1){
		printf("Enter the number of edges: ");
		scanf("%d", &ed);
		if(ed>0) break;
		printf("Invalid number of edges given!\n");
	}
	
	(*v) = ver;
	(*e) = ed;
	
	incMat = (int*)malloc(ver*ed*sizeof(int)); // incedence Matrix created
	
	for(i=0; i<ver; i++) 
		for(j=0; j<ed; j++)
			*(incMat+(i*ed)+j)=0; // incMat[i][j]=0
	
	return incMat;
}

void displayGraph(int *incMat, int v, int e){
	if(incMat==NULL || v<=0) return; // invalid matrix for display  [ not initialised ]
	
	int i, j;
	
	printf("\nIncedence Matrix\n");
	printf("    ");
	for(i=0; i<e; i++) printf("%d\t", i);
	printf("\n");
	for(i=0; i<e; i++) printf("-------", i);
	printf("\n");
	
	for(i=0; i<v; i++){
		printf("%d | ", i);
		for(j=0; j<e; j++)
			printf("%d\t", *(incMat+(i*e)+j) ); // incMat[i][j]	
		printf("\n");
	}
	printf("\n");
}

int inputGraph(int *incMat, int v, int ed){
	if(incMat==NULL || v<=0 || ed<=0) return; // invalid matrix for display  [ not initialised ]
	
	int choice, s, e, w, edgeNo;
	
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
	
	edgeNo=0;
	
	// for(edgeNo=0; edgeNo<ed; edgeno++){
	
	while(edgeNo < ed){
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
				//break; // un-comment this line to allow self loop
				if(s!=e) break; // self loop not allowed
			}
			printf("Invalid end vertex!\n");
		}
	
		if(choice==1 || choice==3){  // unweighted
			*(incMat+(s*ed)+edgeNo) = 1;  // incMat[s][edgeNo]=1
			if(choice==1) *(incMat+(e*ed)+edgeNo)=1; // incMat[e][edgeNo]=1 undirected-unweighted
			else *(incMat+(e*ed)+edgeNo)=-1; // incMat[e][edgeNo]=-1 directed-unweighted
		}	
		else { // weighted  [ choice=2 OR choice=4 ]
	
			while(1){ // taking start vertex from user
				printf("Enter weight: ");
				scanf("%d", &w);
				if(w>0) break;
				printf("Invalid weight!\n");
			}
		
			*(incMat+(s*ed)+edgeNo)=w; // incMat[s][edgeNo]=weight
			if(choice==2) *(incMat+(e*ed)+edgeNo)=w; // incMat[e][edgeNo]=weight  undirected-weighted
			else *(incMat+(e*ed)+edgeNo)=(-1)*w;// incMat[e][edgeNo]= -weight  directed-weighted
		}
		
		edgeNo++;
	}
	
	return choice;
}
