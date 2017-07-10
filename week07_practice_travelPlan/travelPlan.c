/*
 * travelPlan.c
 *
 *  Created on: 2017年5月14日
 *      Author: ygh
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 500 /*define the max number of the vertex*/
#define INFINITY 65535     /*define double byte no negitive integer max number is 65535*/
#define ERROR -1

typedef int vertex; /*define the data type of the vertex*/
typedef int weightType; /*define the data type of the weight*/
typedef char dataType; /*define the data type of the vertex value*/
typedef int priceType;

/*define the data structure of the Edge*/
typedef struct eNode *ptrToENode;
typedef struct eNode {
	vertex v1, v2; /*two vertex between the edge <v1,v2>*/
	weightType weight; /*the value of the edge's weight */
	priceType price; /*The value of price of the price*/
};
typedef ptrToENode edge;

/*define the data structure of the graph*/
typedef struct gNode *ptrToGNode;
typedef struct gNode {
	vertex source; /*The index of the source*/
	vertex destination; /*The index of the destination*/
	int vertex_number; /*the number of the vertex*/
	int edge_nunber; /*the number of the edge*/
	weightType g[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; /*define the adjacent matrix weight of graph*/
	priceType p[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; /*define the adjacent matrix price of graph*/
	dataType data[MAX_VERTEX_NUM]; /*define the dataType array to store the value of vertex*/
};
typedef ptrToGNode adjacentMatrixGraph; /*a graph show by adjacent matrix*/

/*
 create a graph given the vertex number.
 @param vertexNum The verter number of the graph
 @return a graph with vertex but no any egdgs
 */
adjacentMatrixGraph createGraph(int vertexNum) {
	vertex v, w;
	adjacentMatrixGraph graph;
	graph = (adjacentMatrixGraph) malloc(sizeof(struct gNode));
	graph->vertex_number = vertexNum;
	graph->edge_nunber = 0;
	/*initialize the adjacent matrix*/
	for (v = 0; v < graph->vertex_number; v++) {
		for (w = 0; w < graph->vertex_number; w++) {
			graph->g[v][w] = INFINITY;
			graph->p[v][w] = INFINITY;
		}
	}

	return graph;
}

/*
 insert a edge to graph.We will distinct oriented graph and undirected graph
 @param graph The graph you want to insert edge
 @param e The edge you want to insert the graph
 @param isOriented Whether the graph is oriented graph.If the graph is oriented
 we will set adjacent matrix [n][m]=[m][n]=edge's weight,else we only set
 the adjacent matrix [n][m]=edge's weight
 */
void inserEdge(adjacentMatrixGraph graph, edge e, int isOriented) {
	graph->g[e->v1][e->v2] = e->weight;
	graph->p[e->v1][e->v2] = e->price;
	if (!isOriented) {
		graph->g[e->v2][e->v1] = e->weight;
		graph->p[e->v2][e->v1] = e->price;
	}
}

/*
 construct a graph according user's input

 @return a graph has been filled good
 */
adjacentMatrixGraph buildGraph(int isOrdered) {
	adjacentMatrixGraph graph;
	edge e;
	vertex i;
	vertex source, destination;
	int vertex_num;
	scanf("%d", &vertex_num);
	graph = createGraph(vertex_num);
	scanf("%d", &(graph->edge_nunber));
	scanf("%d %d", &source, &destination);
	graph->source = source;
	graph->destination = destination;
	if (graph->edge_nunber) {
		e = (edge) malloc(sizeof(struct eNode));
		for (i = 0; i < graph->edge_nunber; i++) {
			scanf("%d %d %d %d", &e->v1, &e->v2, &e->weight, &e->price);
			inserEdge(graph, e, isOrdered);
		}
	}
	return graph;

}

/*
 * Find the the index of point in the graph whose dist is minimal and has not been
 * accessed.
 * @param graph A graph which use adjacent matrix to store
 * @param dist A integer array to store the length from source to destination, it will be initialize with 65535 at first
 * @param collection A integer array to show whether the point has been accessed
 * 		0 indicates the point has not been accessed,`1 indicates the point has been accessed
 * 		the index in collection is same as the graph
 */
vertex findMinDist(adjacentMatrixGraph graph, int *dist, int *collection) {
	vertex minVertex, v;
	int minDist = INFINITY;
	/*
	 * Find the minimal dist
	 */
	for (v = 0; v < graph->vertex_number; v++) {
		if (dist[v] < minDist && collection[v] == 0) {
			minDist = dist[v];
			minVertex = v;
		}
	}

	if (minDist < INFINITY) {
		return minVertex;
	} else {
		return ERROR;
	}
}

/*
 * Find the shortest path from source to every point in graph with weight
 *@param graph A graph which use adjacent matrix to store
 *@param dist A integer array to store the length from source to destination, it will be initialize with 65535 at first
 *@param path A integer to store the index of last vertex which is shortest to pass current point,it will be initialize -1
 *@return 1 indicate the algorithms is correct calculate the result,0 indicates there is negative edge in the graph,a error happened
 */
int dijkstar(adjacentMatrixGraph graph, int *dist, int *path, int *totalPrice,
		vertex startPoint) {
	int collection[graph->vertex_number];
	vertex v, w;
	for (v = 0; v < graph->vertex_number; v++) {
		dist[v] = graph->g[startPoint][v];
		totalPrice[v] = graph->p[startPoint][v];
		if (dist[v] < INFINITY) {
			path[v] = startPoint;
		} else {
			path[v] = -1;
			collection[v] = 0;
		}
	}
	collection[startPoint] = 1;
	dist[startPoint] = 0;
	totalPrice[startPoint] = 0;
	while (1) {
		v = findMinDist(graph, dist, collection);
		if (v == ERROR) {
			break;
		}
		collection[v] = 1;
		for (w = 0; w < graph->vertex_number; w++) {
			if (collection[w] == 0 && graph->g[v][w] < INFINITY) {
				/*
				 * If a edge weight is a negative,Dijkstra will not to solve it,return 0
				 */
				if (graph->g[v][w] < 0) {
					return 0;
				}
				/*
				 * If v make dist[w] get smaller,updata it
				 */
				if (dist[v] + graph->g[v][w] < dist[w]) {
					dist[w] = dist[v] + graph->g[v][w];
					totalPrice[w] = totalPrice[v] + graph->p[v][w];
					path[w] = v;
				} else if ((dist[v] + graph->g[v][w] == dist[w])
						&& (totalPrice[w] > totalPrice[v] + graph->p[v][w])) {
					totalPrice[w] = totalPrice[v] + graph->p[v][w];
					path[w] = v;
				}
			}
		}
	}
	return 1;
}

/*============================define a stack to print result=============*/
typedef int stackElement;
typedef struct node3 {
	stackElement element;
	struct node3 *next;
} sta, *pStack;

pStack createEmptyStack() {
	pStack stack;
	stack = (pStack) malloc(sizeof(sta));
	if (stack) {
		stack->next = NULL;
	}
	return stack;
}

int isEmpty(pStack stack) {
	if (stack->next == NULL) {
		return 1;
	} else {
		return 0;
	}
}

void push(pStack stack, stackElement element) {
	pStack node = (pStack) malloc(sizeof(sta));
	node->element = element;
	node->next = stack->next;
	stack->next = node;
}

stackElement pop(pStack stack) {
	stackElement element;
	pStack topHead;
	if (isEmpty(stack)) {
		printf("the stack is empty,can not pop");
		return -65536;
	} else {
		topHead = stack->next;
		stack->next = topHead->next;
		element = topHead->element;
		free(topHead);
		return element;
	}
}

void calculateDistanceAndFee(adjacentMatrixGraph graph, int *path, int length,
		int destination) {
	pStack stack = createEmptyStack();
	vertex v;
	int index = destination;
	int totalDistace = 0;
	int totalPrice = 0;
	int arr[graph->vertex_number];
	int counter = 0, i;
	push(stack, index);
	while (v != -1) {
		v = path[index];
		push(stack, v);
		index = v;
	}

	pop(stack);
	while (!isEmpty(stack)) {
		stackElement element = pop(stack);
		arr[counter++] = element;
	}

	for (i = 1; i < counter; i++) {
		totalDistace = totalDistace + graph->g[arr[i - 1]][arr[i]];
		totalPrice = totalPrice + graph->p[arr[i - 1]][arr[i]];
	}

	printf("%d %d", totalDistace, totalPrice);
}

/*
 * Fill a array with value
 * @param arr The array need to be filled
 * @param length The length of the array
 * @param filledValue The value the array will be filled
 */
void fullArray(int *arr, int length, int filledValue) {
	int i;
	for (i = 0; i < length; i++) {
		arr[i] = filledValue;
	}
}
int main() {
	/*
	 * This is a no-direct graph
	 */
	adjacentMatrixGraph graph = buildGraph(0);
	int dist[graph->vertex_number];
	int path[graph->vertex_number];
	int totalPrice[graph->vertex_number];
	dijkstar(graph, dist, path, totalPrice, 0);
	calculateDistanceAndFee(graph, path, graph->edge_nunber,
			graph->destination);
	return 0;
}

