/*
 * hash.c
 *
 *  Created on: 2017年5月28日
 *      Author: ygh
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_VERTEX_NUM 10001 /*define the max number of the vertex*/
#define INFINITY 65535     /*define double byte no negitive integer max number is 65535*/
#define ERROR -1
#define MAX_LENGTH 10000
#define MAX_TABLE_SIZE 100000

typedef int vertex; /*define the data type of the vertex*/
typedef int weightType; /*define the data type of the weight*/
typedef int dataType; /*define the data type of the vertex value*/

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
	int isDelete
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
		graph->g[v].isDelete = 0;
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
adjacentTableGraph buildLGraph(int vertex_num, int *arr) {
	adjacentTableGraph graph;
	vertex i;
	graph = createLGraph(vertex_num);
	for (i = 0; i < graph->vertex_number; i++) {
		graph->g[i].data = arr[i];
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
int topSort(adjacentTableGraph graph, vertex topOrder[]) {
	vertex v, k, key;
	ptrToAdjNode w;
	int indegree[graph->vertex_number], vertexConter = 0;
	/*
	 * Create a queue to store the vertex whose in-degree is zero
	 */
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

	for (v = 0; v < graph->vertex_number; v++) {
		dataType min = INFINITY;
		for (k = 0; k < graph->vertex_number; k++) {
			if (graph->g[k].isDelete == 0  && indegree[k] == 0) {
				if (graph->g[k].data < min) {
					min = graph->g[k].data;
					key = k;
				}
			}
		}
		graph->g[key].isDelete = 1;
		topOrder[vertexConter++] = key;
		for (w = graph->g[key].head; w; w = w->next) {
			indegree[w->adjVerx]--;
		}
	}
	if (vertexConter == graph->vertex_number) {
		return 1;
	} else {
		return 0;
	}
}

/*
 * Print the index of the vertex of the top sort
 */
void printTopSort(adjacentTableGraph graph, int topOrder[], int length) {
	int i;
	for (i = 0; i < length; i++) {
		if (graph->g[topOrder[i]].data < 0) {
			continue;
		} else {
			if (i != length - 1) {
				printf("%d ", graph->g[topOrder[i]].data);
			} else {
				printf("%d", graph->g[topOrder[i]].data);
			}
		}
	}
}

/*
 * Get input data and record the index
 * @param arr A array to store the input data
 * @param index A array to record the index of the data in the arr
 */
int getInputData(int *arr, int *index) {
	int n, i;
	dataType data;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &data);
		arr[i] = data;
		index[data] = i;
	}
	return n;
}

int getEmptyQuantity(int *arr, int n) {
	int i;
	int counter = 0;
	for (i = 0; i < n; i++) {
		if (arr[i] < 0) {
			counter++;
		}
	}
	return counter;
}

/*
 * Get a prime number greater than N but no more than
 * <code>MAX_TABLE_SIZE</code> and return it
 */
int nextPrime(int n) {
	int i, p = (n % 2) ? n : n + 1;
	while (p < MAX_TABLE_SIZE) {
		for (i = sqrt(p); i > 2; i--) {
			if (!(p % i)) {
				break;
			}
		}
		/*
		 * Find the prime number
		 */
		if (i == 2) {
			break;
		} else {
			p = p + 2;
		}
	}
	return p;
}

/*
 * Constructor graph by hashing search
 */
adjacentTableGraph constructGraph(int *arr, int *index, int n) {
	adjacentTableGraph graph = buildLGraph(n, arr);
	edge e = (edge) malloc(sizeof(struct eNode));
	int i, j, k;
	for (i = 0; i < n; i++) {
		if (arr[i] < 0) {
			continue;
		}
		if (arr[i] % n != i) {
			j = arr[i] % n;
			if (j < i) {
				for (k = j; k < i; k++) {
					if (arr[k] < 0) {
						continue;
					} else {
						e->v1 = index[arr[k]];
						e->v2 = index[arr[i]];
						e->weight = 1;
						insertEdgeToLink(graph, e, 1);
					}
				}
			} else {
				for (k = j; k < n; k++) {
					if (arr[k] < 0) {
						continue;
					} else {
						e->v1 = index[arr[k]];
						e->v2 = index[arr[i]];
						e->weight = 1;
						insertEdgeToLink(graph, e, 1);
					}
				}

				for (k = 0; k < i; k++) {
					if (arr[k]  < 0) {
						continue;
					} else {
						e->v1 = index[arr[k]];
						e->v2 = index[arr[i]];
						e->weight = 1;
						insertEdgeToLink(graph, e, 1);
					}
				}
			}
		}
	}
	return graph;
}

/*
 * Swap two integer number value
 */
void swap(elementType *a, elementType *b) {
	int temp = *b;
	*b = *a;
	*a = temp;
}

/*
 * Update the element of tree make the tree to be a maximal heap
 * @param a A <code>elementType</code> array to store the elements
 * @param p The index of the element need to update
 * @param n The length of the array
 */
void percDowm(elementType a[], int p, int n) {
	int parent, child;
	elementType x;
	x = a[p];
	for (parent = p; (parent * 2 + 1) < n; parent = child) {
		child = parent * 2 + 1;
		if ((child != n - 1) && a[child] < a[child + 1]) {
			child++;
		}
		if (x >= a[child]) {
			break;
		} else {
			a[parent] = a[child];
		}
	}
	a[parent] = x;
}

/*
 * Implement heap sort
 * @param a A integer array need to sort
 * @param n The length of the array
 */
void heap_sort(elementType a[], int n) {
	int i;
	/*
	 * Build max heap
	 */
	for (i = n / 2 - 1; i >= 0; i--) {
		percDowm(a, i, n);
	}

	/*
	 * Swap and update heap
	 */
	for (i = n - 1; i > 0; i--) {
		swap(&a[0], &a[i]);
		percDowm(a, 0, i);
	}
}

/*
 * Print the array to console
 * @param a A integer array need to sort
 * @param n The length of the array
 */
void printArray(int a[], int n) {
	int i;
	for (i = 0; i < n; i++) {
		if (i == n - 1) {
			printf("%d", a[i]);
		} else {
			printf("%d ", a[i]);
		}
	}
	printf("\n");
}

int main() {
	int n;
	int arr[MAX_LENGTH];
	int index[MAX_LENGTH];
	int emptyCounter;
	adjacentTableGraph graph;
	n = getInputData(arr, index);
	emptyCounter = getEmptyQuantity(arr, n);
	if (emptyCounter == 0) {
		heap_sort(arr, n);
		printArray(arr, n);
		return 0;
	}
	n = nextPrime(n);
	graph = constructGraph(arr, index, n);
	vertex topOrder[graph->vertex_number];
	topSort(graph, topOrder);
	printTopSort(graph, topOrder, n);
	return 0;
}
