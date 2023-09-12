#include "adjMatrix.h"
#define max 100
#define unvisited 0
#define visited 1
#define processed 2
#define NIL -1

int queue[max], front, rear;

void initialiseQueue(){
	front=-1;
	rear=-1;
}

void enqueue(int ver){
	if(rear==(max-1)) return;
	
	if(queueIsEmpty()) // first time
		front=0;
	queue[++rear] = ver;
}
int queueIsEmpty(){
	if( front==-1 && rear==-1 ) return 1;
	else return 0;
} 
int dequeue(){
	if( !queueIsEmpty()){
		int value = queue[front++];
		if(front > rear) initialiseQueue();
		return value;
	}
	else return -1; // means queue is empty
}

void bfs(int *adjMat, int v){
	
	int i, j, u, source;
	int *parent = (int*)malloc(v*sizeof(int));
	int *status = (int*)malloc(v*sizeof(int));
	
	for(i=0; i<v; i++){
		parent[i] = NIL;
		status[i]= unvisited;
	}
	
	printf("Enter source vertex: ");
	scanf("%d", &source);
	
	initialiseQueue();
	enqueue(source);
	status[source] = visited;
	
	printf("BFS Traversal: ");
	while(!queueIsEmpty()){
		
		u = dequeue();
		
		for(i=0; i<v; i++){
			
			if( *(adjMat+(u*v)+i) >0 && status[i]==unvisited){
				parent[i] = u;
				status[i] = visited;
				enqueue(i);
			}
			
		}
		
		status[u] = processed;
		printf("%d, ", u);
	}
	
	printf("\n\nParent  Child\n");
	for(i=0; i<v; i++){
		printf("  %d\t  %d\n", parent[i], i);	
	}
	
	
}



int main(){
	int v, type;
	int *adjMat = initializeGraph(&v);
	type = inputGraph(adjMat, v);
	displayGraph(adjMat, v);
	
	bfs(adjMat, v);
	
	return 0;
	
}
