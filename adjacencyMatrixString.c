/* 
ASCII A-Z => 65 to 90
ASCII a-z => 97 to 122
ASCII 0-9 => 48 to 57
ASCII ' ' => 32
*/

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
		printf("%c", (char)(i+65) );
		for(j=0; j<ver; j++)
			*(adjMat+(i*ver)+j)=0; // adjMat[i][j]=0
	}
	printf("\n");
	return adjMat;
}

void displayGraph(int *adjMat, int v){
	if(adjMat==NULL || v<=0) return; // invalid matrix for display  [ not initialised ]
	
	int i, j;
	
	printf("\nAdjacency Matrix:\n");
	printf("\t");
	for(i=0; i<v; i++) printf("%c\t", (char)(i+65));
	printf("\n");
	for(i=0; i<v; i++){
		printf("%c\t", (char)(i+65));
		for(j=0; j<v; j++)
			printf("%d\t", *(adjMat+(i*v)+j) ); // adjMat[i][j]
		printf("\n");
	}
	printf("\n");
}

int inputGraph(int *adjMat, int v){
	if(adjMat==NULL || v<=0) return 0; // invalid matrix for display  [ not initialised ]
	
	int choice, w, t, st, et;
	char s, e;
	
	printf("\n1. Undirected-Unweighted\n");
	printf("2. Undirected-Weighted\n");
	printf("3. Directed-Unweighted\n");
	printf("4. Directed-Weighted\n");
	printf("5. Exit\n");
	
	while(1){
		printf("Enter choice (` to stop): ");
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
			fflush(stdin);
			scanf("%c", &s);
			
			if(s=='`') return choice; // no more edge to add therefore return
			
			
			st = (int)(s); // finding ASCII of character s
			
			if(st>=97 && st<=122) st = st-32; // upper-case conversion
			
			st=st-65; // converting t into vertex no.
			
			if(st>=0 && st<v) break; 
			
			printf("Invalid start vertex!\n");
		}
		
		
		while(1){ // taking end vertex from user
			printf("Enter end vertex: ");
			fflush(stdin);
			scanf("%c", &e);
			
			et = (int)(e); // finding ASCII of character e
			
			if(et>=97 && et<=122) et = et-32; // upper-case conversion
			
			et=et-65; // converting t into vertex no.
			
			if(et>=0 && et<v) {
				break; // un-comment this line to allow self loop
				if(st != et) break; // self loop not allowed
			}
			printf("Invalid end vertex!\n");
		}
	
		if(choice==1 || choice==3){  // unweighted
	
			*(adjMat+(st*v)+et)=1; // adjMat[st][et]=1
			if(choice==1) *(adjMat+(et*v)+st)=1; // adjMat[et][st]=1 undirected-unweighted

		}	
		else { // weighted  [ choice=2 OR choice=4 ]
	
			while(1){ // taking start vertex from user
				printf("Enter weight: ");
				scanf("%d", &w);
				if(w>0) break;
				printf("Invalid weight!\n");
			}
		
			*(adjMat+(st*v)+et)=w; // adjMat[st][et]=weight
			if(choice==2) *(adjMat+(et*v)+st)=w; // adjMat[et][st]=weight  undirected-weighted
		}

	}
	
	return choice;
}



int main(){
	int *adjMat=NULL, v=0, type;
	
	adjMat = initializeGraph(&v); // for graph 1
	type = inputGraph(adjMat, v);
	
	printf("Graph \n");
	displayGraph(adjMat, v);  // display graph 1

	
	return 0;
}
