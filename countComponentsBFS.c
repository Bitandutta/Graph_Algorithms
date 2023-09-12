#include "adjacencyList.h"
#define NIL -1
#define white 0 // ready ( initialized )
#define gray 1 // waiting ( visited )
#define black 2 // processed 
#define infinity 2147483647

typedef struct Q{
	int vertex;
	struct Q *next;
}queue;

/* This structure can hold head and tail pointer for each Queue there reducing complexcity
typedef struct P{
	struct Q *head;
	struct Q *tail;
}q;

q q1, q2, q3, 
*/

void initializeQueue(queue **head, queue **tail){
	*head=NULL;
	*tail=NULL;
}

int queueIsEmpty(queue *head, queue *tail){
	if(head==NULL && tail==NULL) return 1;
	return 0;
}

void enqueue(queue **head, queue **tail, int value){
	// head = add of (add of actual head node)
	// tail = add of (add of actual tail node)
	// *head = add of actual head node
	// *tail = add of actual tail node
	// *(*head) = actual head ndoe	i.e. add of head node
	// *(*tail) = actual tail node	i.e. add of tail node
	
	queue *temp = (queue*)malloc(sizeof(queue));
	
	temp->vertex=value;
	temp->next=NULL;
	
	if(queueIsEmpty(*head, *tail)){ // insertion should be at head
		*head=temp;
		*tail=temp;
	}
	else{ // insertion should be at tail
		(*tail)->next = temp;
		*tail=temp;
	}
}

int dequeue(queue **head, queue **tail){
	if(queueIsEmpty(*head, *tail)) return -1; // indicates empty queue
	
	int v;
	queue *t;
	
	v = (*head)->vertex; // v = (*(*head)).vertex;
	t = *head; 
	
	//  if *head==*tail can also be done
	if( (*head)->next == NULL){ // after dequeuing the list is to be made empty
		initializeQueue( head, tail ); // queue is initalized thus marked empty
		free(t);
	}
	else{ // list has more then one element
		(*head)=(*head)->next;
		free(t); // deleting the memory
	}
	
	return v;
}

void bfs(Graph *g, int start, int *color, int *parent, int *distance){
	if(g==NULL) return;
	
	int i, u, vert = (g->vertex);

	
	color[start] = gray; // waiting
	distance[start] = 0; // starting vertex's needs 0 cost to reach
	
	queue *head, *tail;
	initializeQueue(&head, &tail); // queue initalized
	enqueue(&head, &tail, start); // start vertex is enqueued into queue
	
	//printf("\nBFS Traversal: ");
	
	node *t;
	while(!queueIsEmpty(head, tail)){
		u = dequeue(&head, &tail);  // a vertex is dequeue from Queue
		t = (g->list)[u]; // now t points to the list of all vertices adjacent to vertex u
		
		while(t!=NULL){
			
			if(color[t->v] == white){
				color[t->v] = gray; // waiting
				distance[t->v] = distance[u]+1;
				parent[t->v] = u;
				enqueue(&head, &tail, t->v);
			}

			t = t->next; // jump to next adjacent vertex
		}
		
		color[u] = black; // processed
		//printf("%d, ", u);
		
	}
	/*
	printf("\n\nParent  Child\n");
	for(i=0; i<vert; i++){
		printf("  %d\t  %d\n", parent[i], i);	
	}
	*/
}

int countComponents(Graph *g){
	
	int i, comp, vert = g->vertex;
	
	int *color = (int*)malloc(vert*sizeof(int));
	int *parent = (int*)malloc(vert*sizeof(int));
	int *distance = (int*)malloc(vert*sizeof(int));
	
	// initializing all the arrays
	for(i=0; i<vert; i++){ // for each vertex i in graph
		color[i] = white; // ready
		distance[i] = infinity;
		parent[i] = NIL;
	}
	
	bfs(g, 0, color, parent, distance);
	
	comp=1;
	for(i=1; i<vert; i++){
		
		if(color[i] == white){
			comp++;
			bfs(g, i, color, parent, distance);
		}
		
	}
	
	return comp;
}


int main(){
	Graph *g;
	int type;
	
	g=initializeGraph();
	type=inputGraph(g);
	displayGraph(g, type);

	printf("\nTotal components: %d", countComponents(g));

	return 0;
}
