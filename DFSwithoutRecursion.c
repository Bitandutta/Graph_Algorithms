#include "adjMatrix.h"
#define white 0
#define gray 1
#define black 2

typedef struct S{
	int top;
	int length;
	int *arr;
}Stack;

Stack* initializeStack(int len){
	Stack *s = (Stack*)malloc(sizeof(Stack));
	s->top=-1;
	s->length = len;
	s->arr = (int*)malloc(len*sizeof(int)); // array of length elements created
	return s;
}
int stackIsEmpty(Stack *s){
	if(s==NULL || s->top==-1) return 1; // top==-1 then empty
	else return 0;
}
void push(Stack *s, int value){
	(s->arr)[++(s->top)] = value; // arr[++top]=value
}
int pop(Stack *s){
	if(s->top > -1) // data is available
		return (s->arr)[(s->top)--]; // return arr[top--]
	return s->top;
}
int stackIsFull(Stack *s){
	if(s->top < (s->length)-1) return 0;
	else return 1;
}

void dfs(int *adjMat, int v){
	int i, u, start;
	int *color = (int*)malloc(v*sizeof(int));
	int *parent = (int*)malloc(v*sizeof(int));
	
	for(i=0; i<v; i++){
	 	color[i]=white; // ready state, unvisited
	 	parent[i]=-1; // NIL
	}
	
	while(1){
		printf("\nEnter starting vertex: ");
		scanf("%d", &start);
		if(start>=0 && start<v) break;
		printf("Invalid start vertex\n");
	}

	
	Stack *s = initializeStack(v); // stack s created with v elements
	
	push(s, start);
	color[start]=gray; // waiting or visited state

	printf("\nDFS Traversal: ");
	
	while( !stackIsEmpty(s) ){ // while stack is not empty
		u = pop(s); // vertex popped from stack

		for(i=0; i<v; i++){ // adjMat[u][i] > 0 i.e. vertex i is adjacent to vertex u
			if( *(adjMat+(u*v)+i) > 0 && color[i]==white){  // if adjacent vertex color is white then
				push(s, i);
				parent[i] = u;
				color[i] = gray; // waiting state, visited
			}
		}
		
		color[u] = black; // processed state
		printf("%d, ", u);
	}
	
	printf("\n");
	printf("Child\tParent\n");
	for(i=0; i<v; i++) printf("%d\t%d\n", i, parent[i]);
}


int main(){
	
	int *adjMat, v, type;
	adjMat = initializeGraph(&v);
	type = inputGraph(adjMat, v);
	displayGraph(adjMat, v);
	
	dfs(adjMat, v);
	
	return 0;
}
