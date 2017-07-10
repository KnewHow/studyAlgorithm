/*
 * prim.c
 *
 *  Created on: 2017年5月15日
 *      Author: ygh
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 100 /*define the max number of the vertex*/
#define INFINITY 65535     /*define double byte no negitive integer max number is 65535*/
#define ERROR -1

typedef int vertex; /*define the data type of the vertex*/
typedef int weightType; /*define the data type of the weight*/
typedef char dataType; /*define the data type of the vertex value*/

/*define the data structure of the Edge*/
typedef struct eNode *ptrToENode;
typedef struct eNode {
	vertex v1, v2; /*two vertex between the edge <v1,v2>*/
	weightType weight; /*the value of the edge's weight */
};
typedef ptrToENode edge;

/*==================A adjacent matrix to describe a graph=========================================*/

/*define the data structure of the graph*/
typedef struct gMNode *ptrTogMNode;
typedef struct gMNode {
	int vertex_number; /*the number of the vertex*/
	int edge_nunber; /*the number of the edge*/
	weightType g[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; /*define the adjacent matrix weight of graph*/
	dataType data[MAX_VERTEX_NUM]; /*define the dataType array to store the value of vertex*/
};
typedef ptrTogMNode adjacentMatrixGraph; /*a graph show by adjacent matrix*/

/*
 create a graph given the vertex number.
 @param vertexNum The verter number of the graph
 @return a graph with vertex but no any egdgs
 */
adjacentMatrixGraph createMGraph(int vertexNum) {
	vertex v, w;
	adjacentMatrixGraph graph;
	graph = (adjacentMatrixGraph) malloc(sizeof(struct gMNode));
	graph->vertex_number = vertexNum;
	graph->edge_nunber = 0;
	/*initialize the adjacent matrix*/
	for (v = 0; v < graph->vertex_number; v++) {
		for (w = 0; w < graph->vertex_number; w++) {
			graph->g[v][w] = INFINITY;
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
void inserEdgeToMatrix(adjacentMatrixGraph graph, edge e, int isOriented) {
	graph->g[e->v1][e->v2] = e->weight;
	if (!isOriented) {
		graph->g[e->v2][e->v1] = e->weight;
	}
}

/*
 construct a graph according user's input

 @return a graph has been filled good
 */
adjacentMatrixGraph buildMGraph(int isOrdered) {
	adjacentMatrixGraph graph;
	edge e;
	vertex i;
	int vertex_num;
	scanf("%d", &vertex_num);
	graph = createMGraph(vertex_num);
	scanf("%d", &(graph->edge_nunber));
	if (graph->edge_nunber) {
		e = (edge) malloc(sizeof(struct eNode));
		for (i = 0; i < graph->edge_nunber; i++) {
			scanf("%d %d %d", &e->v1, &e->v2, &e->weight);
			e->v1--;
			e->v2--;
			inserEdgeToMatrix(graph, e, isOrdered);
		}
	}
	return graph;

}

/*==================A adjacent link to describe a graph=========================================*/
/*define the data structure adjacent table node*/
typedef struct adjNode *ptrToAdjNode;
typedef struct adjNode {
	vertex adjVerx; /*the index of the vertex*/
	weightType weight; /*the value of the weight*/
	ptrToAdjNode next; /*the point to point the next node*/
};

/*define the data structure of the adjacent head*/
typedef struct vNode *ptrToVNode;
typedef struct vNode {
	ptrToAdjNode head; /*the point to point the adjacent table node*/
	dataType data; /*the space to store the name of the vertex,but some time the vertex has no names*/
} adjList[MAX_VERTEX_NUM];

/*define the data structure of graph*/
typedef struct gLNode *ptrTogLNode;
typedef struct gLNode {
	int vertex_number; /*the number of the vertex*/
	int edge_nunber; /*the number of the edge*/
	adjList g; /*adjacent table*/
};
typedef ptrTogLNode adjacentTableGraph; /*a graph show by adjacent table*/

/*
 create a graph given the vertex number.
 @param vertexNum The verter number of the graph
 @return a graph with vertex but no any egdgs
 */
adjacentTableGraph createLGraph(int vertexNum) {
	adjacentTableGraph graph;

	vertex v;
	graph = (adjacentTableGraph) malloc(sizeof(struct gLNode));
	graph->vertex_number = vertexNum;
	graph->edge_nunber = 0;
	/*initialize the adjacent table*/
	for (v = 0; v < graph->vertex_number; v++) {
		graph->g[v].head = NULL;
	}
	return graph;
}

/*
 insert a edge to graph.We will distinct oriented graph and undirected graph
 The e->v1 and e->v2 are the vertexs' indexs in the adjacent table
 @param graph The graph you want to insert edge
 @param e The edge you want to insert the graph
 @param isOriented Whether the graph is oriented graph.If the graph is oriented
 we will set adjacent table graph[v1]->head=v2 and set graph[v1].head=v2
 otherwise we only set graph[v1].head=v2
 */
void insertEdgeToLink(adjacentTableGraph graph, edge e, int isOriented) {
	/*build node<v1,v2>*/
	ptrToAdjNode newNode;
	newNode = (ptrToAdjNode) malloc(sizeof(struct adjNode));
	newNode->adjVerx = e->v2;
	newNode->weight = e->weight;
	newNode->next = graph->g[e->v1].head;
	graph->g[e->v1].head = newNode;
	/*if the graph is directed graph*/
	if (!isOriented) {
		newNode = (ptrToAdjNode) malloc(sizeof(struct adjNode));
		newNode->adjVerx = e->v1;
		newNode->weight = e->weight;
		newNode->next = graph->g[e->v2].head;
		graph->g[e->v2].head = newNode;
	}
}

/*
 build a graph stored by adjacent table
 */
adjacentTableGraph buildLGraph() {
	adjacentTableGraph graph;
	edge e;
	vertex i;
	int vertex_num;

	scanf("%d", &vertex_num);
	graph = createLGraph(vertex_num);
	scanf("%d", &(graph->edge_nunber));
	if (graph->edge_nunber) {
		e = (edge) malloc(sizeof(struct eNode));
		for (i = 0; i < graph->edge_nunber; i++) {
			scanf("%d %d %d", &e->v1, &e->v2, &e->weight);
			insertEdgeToLink(graph, e, 0);
		}
	}

	return graph;
}

/*
 * Find the minimal node closest to created tree
 */
vertex findMinDist(adjacentMatrixGraph graph, weightType dist[]) {
	vertex minV, v;
	weightType minDist = INFINITY;
	for (v = 0; v < graph->vertex_number; v++) {
		if (dist[v] != 0 && dist[v] < minDist) {
			minDist = dist[v];
			minV = v;
		}
	}
	if (minDist < INFINITY) {
		return minV;
	} else {
		return ERROR;
	}
}

/*
 * Prim algorithms,we will store the minimal created tree with a adjacent
 * list table and return the minimal weight
 * @param mGraph The graph showed by adjacent matrix is to store graph
 * @param lGraph The graph showed by adjacent list is to store the minimal created tree
 * @return The weight of the minimal created tree if the graph is connected, otherwise return
 * <code>ERROR</code>
 */
int prim(adjacentMatrixGraph mGraph, adjacentTableGraph lGraph) {

	weightType dist[mGraph->vertex_number], totalWeight;
	vertex parent[mGraph->vertex_number], v, w;
	int vCounter;
	edge e;

	/*
	 * Initialize dist and parent,default the start point is 0 index
	 */
	for (v = 0; v < mGraph->vertex_number; v++) {
		dist[v] = mGraph->g[0][v];
		parent[v] = 0;
	}

	/*
	 * Initialize weight and vertex counter
	 */
	totalWeight = 0;
	vCounter = 0;
	/*
	 * Initialize a edge
	 */
	e = (edge) malloc(sizeof(struct eNode));

	/*
	 * Initialize dist[0] as the root of tree and set parent[0] to -1
	 */
	dist[0] = 0;
	vCounter++;
	parent[0] = -1;
	/*
	 * Execute Prim algorithms
	 */
	while (1) {
		v = findMinDist(mGraph, dist);
		if (v == ERROR) {
			break;
		}

		/*
		 * Put <v,parent[v]> to tree
		 */
		e->v1 = parent[v];
		e->v2 = v;
		e->weight = dist[v];
		insertEdgeToLink(lGraph, e, 1);
		totalWeight += dist[v];
		vCounter++;
		dist[v] = 0;

		/*
		 * Update the v adjacent vertex distance with minimal tree
		 */
		for (w = 0; w < mGraph->vertex_number; w++) {
			/*
			 * If w is v adjacent vetex and not be added to minimal tree
			 */
			if (dist[w] != 0 && mGraph->g[v][w] < INFINITY) {
				/*
				 * Update the distance to minimal created tree
				 */
				if (mGraph->g[v][w] < dist[w]) {
					dist[w] = mGraph->g[v][w];
					parent[w] = v;
				}
			}
		}
	}
	if (vCounter < mGraph->vertex_number) {
		return ERROR;
	} else {
		return totalWeight;
	}
}

/*========Use DFS to print the result of the minimal created tree==========*/
/*
 * A method to access graph
 */
void visit(adjacentTableGraph graph, vertex v) {
	printf("%d ", v);
}

/*
 Depth first search a graph
 @param graph The graph need to search
 @param startPoint The fisrt point we start search the graph
 @paran int *visited The array we use to tag the vertex we has accessed.
 */
void DFS(adjacentTableGraph graph, vertex startPoint, int *visited) {
	ptrToAdjNode p;
	visit(graph, startPoint);
	p = graph->g[3].head;
	visited[startPoint] = 1;
	for (p = graph->g[startPoint].head; p; p = p->next) {
		if (visited[p->adjVerx] == 0) {
			DFS(graph, p->adjVerx, visited);
		}
	}
}

/*
 * Initialize a visited array that make them all to zero
 */
void initVisited(int length, int *visited) {
	int i;
	for (i = 0; i < length; i++) {
		visited[i] = 0;
	}
}

int main() {
	adjacentTableGraph lGraph;
	adjacentMatrixGraph mGraph = buildMGraph(0);
	vertex visited[mGraph->vertex_number];
	lGraph = createLGraph(mGraph->vertex_number);
	weightType totalWeigt = prim(mGraph, lGraph);
	printf("totalWeigh:%d\n", totalWeigt);
	initVisited(mGraph->vertex_number, visited);
	DFS(lGraph, 0, visited);
	return 0;
}

