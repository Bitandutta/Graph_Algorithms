#include<stdio.h>
#include<stdlib.h>

typedef struct N{
	int v, w;
	struct N *next;
}node;

typedef struct G{
	int vertex;
	struct node **list;
}Graph;

Graph* intializeGraph(){
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
	n->next=(g->list)[s];
	(g->list)[s]=n;
}

int inputGraph(Graph *g){
	if(g==NULL) return;
	
	int type, w, s, e;
	
	printf("\n1. Undirected-Unweighted\n");
	printf("2. Undirected-Weighted\n");
	printf("3. Directed-Unweighted\n");
	printf("4. Directed-Weighted\n");
	printf("5. Exit\n");
	while(1){
		printf("Enter type of graph: ");
		scanf("%d", &type);
		if(type>0 && type<6) break;
		printf("Invalid choice!\n");
	}
	
	if(type==5) return 0; // user choosed to exit the function
	
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
		
		if(type==2 || type==4){ // weighted graph
			while(1){
				printf("Enter the weight: ");
				scanf("%d", &w);
				if(w>=1) break; // corect weight is given
				printf("Invalid Weight\n");
			}
			
			addEdge(g, s, e, w);
			if(type==2) addEdge(g, e, s, w); // undirected
		}
		else{ // un-weighted
			addEdge(g, s, e, 0);
			if(type==1) addEdge(g, e, s, 0); // undirected un-weighted
		}
		
	}
	return type;
}

void displayGraph(Graph *g, int type){
	if(g==NULL) return;
	
	int i;
	printf("\nAdjacency List\n");
	for(i=0; i < (g->vertex); i++){
		printf("%d", i);
		
		node *t= (g->list)[i];
		
		while(t!=NULL){
			if(type==2 || type==4) printf(" -> |%d, %d|", t->v, t->w); // weighted
			else printf(" -> |%d|", t->v); // unweighted
			t=t->next;
		}
		printf("\n");
	}

}


int main(){
	Graph *g1;
	int t1;
	
	g1=intializeGraph();
	t1=inputGraph(g1);
	displayGraph(g1, t1);
	
	return 0;
}
