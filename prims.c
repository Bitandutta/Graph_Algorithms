#include<stdio.h>
#include<stdlib.h>
#define infinity 2147483647
#define NIL -1

typedef struct N{
	int v, w;
	struct N *next;
}node;

typedef struct G{
	int vertex;
	struct node **list;
}Graph;

Graph* initializeGraph(){
	int ver, i;
	while(1){
		printf("Enter total vertices: ");
		scanf("%d", &ver);
		if(ver>0) break;
		printf("Invalid vertex number!\n");
	}
	
	Graph *g;
	g=(Graph*)malloc(sizeof(Graph));
	(g->vertex)=ver;
	(g->list)=(node*)malloc(ver*(sizeof(node*)));
	
	printf("\nThe veritices are: ");
	for(i=0; i<ver; i++){
		(g->list)[i]=NULL;
		printf("%d, ", i);
	}
	printf("\n");
	
	return g;
}

void addEdge(Graph *g, int s, int e, int weight){
	if(g==NULL) return;
	node *n;
	n=(node*)malloc(sizeof(node));
	n->v=e;
	n->w=weight;
	n->next=(g->list)[s]; // keep add present in (g->list)[s] into n->next
	(g->list)[s]=n; // keep n in (g->list)[s]
}

int inputGraph(Graph *g){
	if(g==NULL) return;
	
	int type, w, s, e;
	// for prims only undirected graphs are allowed
	printf("\n1. Undirected-Unweighted\n");
	printf("2. Undirected-Weighted\n");
	//printf("3. Directed-Unweighted\n");
	//printf("4. Directed-Weighted\n");
	printf("3. Exit\n");
	while(1){
		printf("Enter type of graph: ");
		scanf("%d", &type);
		if(type>0 && type<4) break;
		printf("Invalid choice!\n");
	}
	
	if(type==3) return 0; // user choosed to exit the function
	
	
	printf("\nEnter the start and end vertex. Terminate by entering -999\n\n");
	while(1){
		printf("Start Vertex: ");
		scanf("%d", &s);
		if(s == -999) break; // end of graph input
		
		if(s<0 || s>=(g->vertex)){
			printf("Invalid start vertex!\n");
			continue;
		}
		while(1){
			printf("End Vertex: ");
			scanf("%d", &e);
			if(e>=0 && e<(g->vertex)) break;
			printf("Invalid end vertex!\n");
		}
		
		if(s==e){
			printf("Self loop is not allowed\n");
			continue;
		}
		
		if(type==2){ // undirected-weighted
			while(1){
				printf("Enter the weight: ");
				scanf("%d", &w);
				if(w>=1) break; // corect weight is given
				printf("Invalid Weight\n");
			}
			
			addEdge(g, s, e, w); // weighted edge added from start to end
			addEdge(g, e, s, w); // weighted edge added from end to start
		}
		else{ // un-weighted
			addEdge(g, s, e, 0); // edge added from start to end
			addEdge(g, e, s, 0); // edge added from end to start
		}
		
	}
	return type;
}

void displayGraph(Graph *g, int type) {
	if(g==NULL) return;
	
	int i;
	printf("\nAdjacency List\n");
	for(i=0; i < (g->vertex); i++) {
		printf("%d", i);
		
		node *t= (g->list)[i]; // t stores the adjacent vertices list of ith vertex
		
		while(t!=NULL){
			if(type==2) printf(" -> |%d, %d|", t->v, t->w); // weighted
			else printf(" -> |%d|", t->v); // unweighted
			t=t->next;
		}
		printf("\n");
		
	}

}



////////////////////////////////////////////////////////////////////////////////////

void mstPrims(Graph *g, int source){

	int i, flag, min, u, v = (g->vertex);
	
	int *key = (int*)malloc(v*sizeof(int)); // tells us to pick which of the following vertex
	int *parent = (int*)malloc(v*sizeof(int));
	int *queue = (int*)malloc(v*sizeof(int)); // tells us which vertex is not yet selected
	
	for(i=0; i<v; i++){ // line 1 start
		key[i] = infinity;
		parent[i] = NIL;
		queue[i] = 1; // line 5 implementation
	} // line 3 end
	
	key[source]=0; // line 4
	node *temp;
	
	while(1){
		
		flag=1;  // line 6 start
		for(i=0; i<v; i++){	
			if(queue[i]==1){
				flag=0;
				break;
			}
		}
		if(flag) break; // break if flag=1
				// line 6 end
		
		
				// line 7 start
		// finding the vertex with minimum key value i.e. not yet included in the mst
		min = infinity;
		
		for(i=0; i<v; i++){
			if( key[i] < min && queue[i]==1 ){
				min = key[i];
				u=i; // i is the vertex with minimum key
			}
		}
				// line 7 end
		queue[u]=0;
		temp = (g->list)[u]; // temp points to the link list storing adjacent vertices of u
		
		printf("%d, ", u); 
		
		while(temp){ // now temp is adjacent to u
			
			if( queue[temp->v]==1 && (temp->w) < key[temp->v] ){
				parent[temp->v] = u;
				key[temp->v] = temp->w;
			}

			temp = temp->next;
		}
		
		/*  if we have used adjacency matrix
		for(i=0; i<v; i++){
			
			if(adjMat[u][i]>0){ // vertex i adjacent ot vertex u

				if( queue[i]==1 && (adjMat[u][i]) < key[i] ){
					parent[i] = u;
					key[i] = adjMat[u][i];
				}
	
			}

		}
		
		*/
	}
	
	
	printf("\nParent\tChild\tWeight\n");
	for( i=0; i<v; i++) printf("  %d\t  %d\t  %d\n", parent[i], i, key[i]);
	
}



int main(){
	
	Graph *g;
	int type;
	
	g = initializeGraph();
	type = inputGraph(g);
	displayGraph(g, type);
	
	int choice;
	printf("\n1. Source-provided Prims\n2. No-source Prims\nEnter choice: ");
	scanf("%d", &choice);
	
	if(choice==1){
		int source;
		printf("\nEnter source vertex: ");
		scanf("%d", &source);
		mstPrims(g, source);
	}
	else mstPrims(g, 0);
	
	return 0;
}





