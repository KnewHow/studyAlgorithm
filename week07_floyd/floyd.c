/*
 * floyd.c
 *
 *  Created on: 2017年5月14日
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

/*define the data structure of the graph*/
typedef struct gNode *ptrToGNode;
typedef struct gNode {
	int vertex_number; /*the number of the vertex*/
	int edge_nunber; /*the number of the edge*/
	weightType g[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; /*define the adjacent matrix weight of graph*/
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
	if (!isOriented) {
		graph->g[e->v2][e->v1] = e->weight;
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
	int vertex_num;
	scanf("%d", &vertex_num);
	graph = createGraph(vertex_num);
	scanf("%d", &(graph->edge_nunber));
	if (graph->edge_nunber) {
		e = (edge) malloc(sizeof(struct eNode));
		for (i = 0; i < graph->edge_nunber; i++) {
			scanf("%d %d %d", &e->v1, &e->v2, &e->weight);
			e->v1--;
			e->v2--;
			inserEdge(graph, e, isOrdered);
		}
	}
	return graph;

}

/*
 * Floyd algorithms:
 1.D k [i][j] = 路径{ i --> { l -->  k } -->  j }的最小长度
 2.D 0 , D 1 , ..., D |V|-1 [i][j]即给出了i到j的真正最短距离
 3.最初的D -1 是什么?
 4.当D k-1 已经完成,递推到D k 时:
	 或者k 属于最短路径{ i -->  { l -->  k } --> j },则D k = D k-1
	 或者k 属于最短路径{ i -->  { l -->  k } -->  j },则该路径必定由两
	 段最短路径组成: D k [i][j]=D k1 [i][k]+D k1 [k][j]
 *@param graph A graph store by adjacent matrix
 *@param d A two-dimensional array to store the distance value
 *@param path A two-dimensional array to store the path
 */
int floyd(adjacentMatrixGraph graph, weightType d[][MAX_VERTEX_NUM],
		vertex path[][MAX_VERTEX_NUM]) {
	vertex i, j, k;
	/*
	 * Initialize array
	 */
	for (i = 0; i < graph->vertex_number; i++) {
		for (j = 0; j < graph->vertex_number; j++) {
			d[i][j] = graph->g[i][j];
			path[i][j] = -1;
		}
	}
	for (k = 0; k < graph->vertex_number; k++) {
		for (i = 0; i < graph->vertex_number; i++) {
			for (j = 0; j < graph->vertex_number; j++) {
				if (d[i][k] + d[k][j] < d[i][j]) {
					d[i][j] = d[i][k] + d[k][j];
					/*
					 * Find negative circle
					 */
					if (i == j && d[i][j] < 0) {
						return 0;
					}
					path[i][j] = k;
				}
			}
		}
	}
	return 1;
}

/*
 * Print the distance matrix
 */
void toStringDistance(int d[MAX_VERTEX_NUM][MAX_VERTEX_NUM], int length) {
	vertex i, j;
	for (i = 0; i < length; i++) {
		printf("%d:", i);
		for (j = 0; j < length; j++) {
			printf("%d ", d[i][j]);
		}
		printf("\n");
	}
}

/*
 * Print the path from source to destination
 * we will recursive method to print the path
 * 1.find the k between source and destination
 * 2.find point between source and k and recursive this method until there no points between them
 * 3.find the point between k and destination and recursive this method until there no points between them
 * @param source The index of the source point
 * @param destination The index of the destination
 * @param path A two-dimensional array to store the path
 */
void toStringPath(int source, int destination, vertex path[][MAX_VERTEX_NUM]) {
	if (destination == -1 || source == -1) {
		return;
	} else {
		toStringPath(source, path[source][destination], path);
		if (path[source][destination] != -1) {
			printf("%d ", path[source][destination]);
		}
		toStringPath(path[source][destination], destination, path);
	}

}

/*
 * A test method
 */
int main() {
	adjacentMatrixGraph graph = buildGraph(1);
	int d[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int path[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int source = 1;
	int destination = 5;
	floyd(graph, d, path);
	printf("toDistance\n");
	toStringDistance(d, graph->vertex_number);
	printf("toPath:");
	printf("%d ", source);
	toStringPath(source, destination, path);
	printf("%d", destination);
	return 0;
}

