#include "incedenceMatrix.h"

int main(){
	int *incMat=NULL, v=0, e=0, type;

	incMat = initializeGraph(&v, &e); // for graph
	type = inputGraph(incMat, v, e);
	displayGraph(incMat, v, e);  // display graph
	
	return 0;
}
