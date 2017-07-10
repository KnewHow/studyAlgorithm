/*
 * take.c
 *
 *  Created on: 2017年5月17日
 *      Author: ygh
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 101 /*define the max number of the vertex*/
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
	weightType earliest; /*The earliest data of the project*/
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
		graph->g[v].earliest = 0;
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
adjacentTableGraph buildLGraph(int isOrdered) {
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
			insertEdgeToLink(graph, e, isOrdered);
		}
	}

	return graph;
}

/*==============================define a queue=====================================================*/
/*define a list to store the element in the queue*/
typedef vertex elementType;
typedef struct node3 *pList;
typedef struct node3 {
	elementType element;
	struct node3 *next;
};

/*define a queue to point the list*/
typedef struct node4 *pQueue;
typedef struct node4 {
	pList front; /*the front point to point the head of the list*/
	pList rear; /*the rear point to point the rear of of the list*/
};

/*create a empty list to store the queue element*/
pList createEmptyList() {
	pList list;
	list = (pList) malloc(sizeof(struct node3));
	list->next = NULL;
	return list;
}
/*create a empty queye*/
pQueue createEmptyQueue() {
	pQueue queue = (pQueue) malloc(sizeof(struct node4));
	queue->front = NULL;
	queue->rear = NULL;
	return queue;
}

/*
 Wether the queue is empty
 @param queue The queue need to adjust
 @return If the queue is null,return 1 otherwise return 0
 */
int isQueueEmpty(pQueue queue) {
	return (queue->front == NULL);
}

/*
 Add a element to a queue,If the queue is null,we will create a new queue
 @parama queue The queue we will add elememt to
 @prama element The element we will add to queue
 */
void addQueue(pQueue queue, elementType element) {
	if (isQueueEmpty(queue)) {
		pList list = createEmptyList();
		list->element = element;
		queue->front = queue->rear = list;
	} else {
		pList newNode = (pList) malloc(sizeof(struct node3));
		newNode->element = element;
		newNode->next = queue->rear->next;
		queue->rear->next = newNode;
		queue->rear = newNode;
	}
}

/*
 delete a element from a queue
 @param queue The queue will be deleted a element
 @return The element has been deleted
 */
elementType deleteEleFromQueue(pQueue queue) {
	if (isQueueEmpty(queue)) {
		printf("the queue is empty,don't allow to delete elemet from it!");
		return -1;
	} else {
		pList oldNode = queue->front;
		elementType element = oldNode->element;
		if (queue->front == queue->rear) {
			queue->rear = queue->front = NULL;
		} else {
			queue->front = queue->front->next;
		}
		free(oldNode);
		return element;
	}
}

/*
 * We solve this problem by top sort,but we need to update the adjacent
 * vertex earliest value at decreasing the adjacent vertex in-degree,the
 * earliest the max value of parent's earliest value add the weight(last time).
 * The vertex which has no in-degree will set earliest to 0 at first time
 *
 * Top sort algorithms thoughts:
 * 1.we first initialize all vertex in-degree is zero,then we according to
 * the graph to set the each vertex in-degree.
 * 2.find zero in-degree vertex and put it in queue.
 * 3.get a vertex from a queue and record its index
 * 4.get the all adjacent vertex of the vertex and let them in-degree decrement,at this moment,if
 * some vertex has decrease into zero,we put them into queue.
 * 5.Execute this operation until the queue is empty
 *
 * @param grap A graph which use adjacent list is used to store the vertex
 * @param topOrder A <code>vertex</code> array to store the index of the
 * 			vertex about the top queue
 * @return If the graph is no circle,indicate the top sort is correct 1 will be return
 * otherwise will return 0
 */
int getEarliestDate(adjacentTableGraph graph, vertex topOrder[]) {
	vertex v;
	ptrToAdjNode w;
	int indegree[MAX_VERTEX_NUM], vertexConter = 0;
	/*
	 * Create a queue to store the vertex whose in-degree is zero
	 */
	pQueue queue = createEmptyQueue();
	/*
	 * Initialize topOrder
	 */
	for (v = 0; v < graph->vertex_number; v++) {
		indegree[v] = 0;
	}
	for (v = 0; v < graph->vertex_number; v++) {
		for (w = graph->g[v].head; w; w = w->next) {
			indegree[w->adjVerx]++;
		}
	}

	/*
	 * Add in-degree vertex to queue
	 */
	for (v = 0; v < graph->vertex_number; v++) {
		if (indegree[v] == 0) {
			addQueue(queue, v);
			graph->g[v].earliest = 0;
		}
	}
	while (!isQueueEmpty(queue)) {
		v = deleteEleFromQueue(queue);
		/*
		 * Record the vertex of top sort
		 */
		topOrder[vertexConter++] = v;
		for (w = graph->g[v].head; w; w = w->next) {
			/*
			 * Update the adjacent vertex's earliest
			 */
			if ((graph->g[v].earliest + w->weight)
					> (graph->g[w->adjVerx].earliest)) {
				graph->g[w->adjVerx].earliest = graph->g[v].earliest
						+ w->weight;
			}
			if (--indegree[w->adjVerx] == 0) {
				addQueue(queue, w->adjVerx);
			}
		}
	}

	/*
	 *Adjust whether all vertexes have been recorded
	 */
	if (vertexConter == graph->vertex_number) {
		return 1;
	} else {
		return 0;
	}
}

/*
 * Get the earliest max value from all vertex.we search each vertex and find the max earliest
 * and return
 * @param grap A graph which use adjacent list is used to store the vertex
 */
int getEarliestTime(adjacentTableGraph graph) {
	weightType maxTime = -1;
	vertex v;
	for (v = 0; v < graph->vertex_number; v++) {
		if (graph->g[v].earliest > maxTime) {
			maxTime = graph->g[v].earliest;
		}
	}
	return maxTime;
}

int main() {
	adjacentTableGraph graph = buildLGraph(1);
	vertex topOrder[graph->vertex_number];
	int bool = getEarliestDate(graph, topOrder);
	if (bool) {
		printf("%d\n", getEarliestTime(graph));
	} else {
		printf("Impossible");
	}
	return 0;
}

