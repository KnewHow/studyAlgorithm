/*
 * save.c
 *
 *  Created on: 2017年5月7日
 *      Author: ygh
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * Algorithm thoughts:
 * we see every crocodile as a point in graph,and we use BFS or DFS to
 * search the path the James can reach river bank.
 * In this question,we store graph use a array,not the standard graph,because
 * in this question, the point in graph is not only crocodies but also the river band
 * how to show them by a graph. So we give up use traditional graph to show them
 * and use a array to show them.
 * But how to judge the adjacent point. we use this point as the central,use the max
 * jump distance as the radius, that which points in this circle is this
 * point's adjacent point.
 *
 * We write the program of BFS and DFS,you can choose one of them of run the program.
 */

#define MAX_LENGTH 100

typedef int vertex;

/*
 * Define a data structure to store a point
 */
typedef int node1Element;
typedef struct node1 {
	node1Element x;		/*The x-coordinate of the point*/
	node1Element y;		/*The y-coordinate of the point*/
} point[MAX_LENGTH];

/*
 * Define a data structure to store a graph
 */
typedef struct node2 *pGraph;
typedef struct node2 {
	int vertex_num;		/*The quantity of the all points*/
	int maxDistance;	/*The max distance the James can jump*/
	point collection;	/*A structure array to store the points*/
};

/*
 * Build a graph by a list of points
 */
pGraph buildGraph() {
	int vertexMum, distance, i;
	vertex x, y;
	scanf("%d", &vertexMum);
	scanf("%d", &distance);
	pGraph graph = (pGraph) malloc(sizeof(struct node2));
	graph->vertex_num = vertexMum;
	graph->maxDistance = distance;
	if (graph->maxDistance) {
		for (i = 0; i < graph->vertex_num; i++) {
			scanf("%d %d", &x, &y);
			graph->collection[i].x = x;
			graph->collection[i].y = y;
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
 * Calculate the distance from point to safe place
 * @param x The x-coordinate of the point
 * @param y THe y-coordinate of the point
 * @param xLine The x base line of square
 * @param yLine The y base line of the square
 */
int calculateDtoSafe(int x, int y, int xLine, int yLine) {
	int distanceX, distanceY;
	distanceX = abs(x - xLine);
	distanceY = abs(y - yLine);
	return (distanceX > distanceY ? distanceY : distanceX);
}

/**
 * Calculate two points distance
 * @return The float distance of twp points
 */
float calculateTwoPointDistance(int x1, int y1, int x2, int y2) {
	return (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

/*
 * Judge the point that whether the James Bond can jump into river bank
 * @param graph A graph to stored all points' collection
 * @param point The index of point in the points' collection
 * @return 1 will be return if James Bond can jump into river bank, otherwise
 * return 0
 */
int isSafe(pGraph graph, vertex point) {
	int x, y, distance;
	x = graph->collection[point].x;
	y = graph->collection[point].y;
	if (x > 0 && y > 0) {
		distance = calculateDtoSafe(x, y, 50, 50);
	}
	if (x > 0 && y < 0) {
		distance = calculateDtoSafe(x, y, 50, -50);
	}

	if (x < 0 && y > 0) {
		distance = calculateDtoSafe(x, y, -50, 50);
	}

	if (x < 0 && y < 0) {
		distance = calculateDtoSafe(x, y, -50, -50);
	}

	if (distance <= graph->maxDistance) {
		return 1;
	} else {
		return 0;
	}
}

int isJump(pGraph graph, vertex source, vertex destination) {
	if (calculateTwoPointDistance(graph->collection[source].x,
			graph->collection[source].y, graph->collection[destination].x,
			graph->collection[destination].y) > graph->maxDistance) {
		return 0;
	} else {
		return 1;
	}
}

/*
 Breadth first search and find whether having a safe path to reach river bank
 @param graph The graph stored by the adjacent table
 @param startPoint The point we start search
 @param visited A array to tag the elemeent whether has been visited
 @retuen
 */
int BFS(pGraph graph, vertex startPoint, int *visited) {
	visited[startPoint] = 1;
	/*
	 * The point index in the graph's points' collection
	 */
	vertex w, v;
	int flag = 0;
	pQueue queue = createEmptyQueue();
	addQueue(queue, startPoint);
	if (isSafe(graph, startPoint)) {
		flag = 1;
		return flag;
	} else {
		while (!isQueueEmpty(queue)) {
			w = deleteEleFromQueue(queue);
			for (v = 0; v < graph->vertex_num; v++) {
				if (visited[v] == 0 && isJump(graph, v, w)) {
					if (isSafe(graph, v)) {
						flag = 1;
						return flag;
					}
					visited[v] = 1;
					addQueue(queue, v);
				}
			}
		}
	}
	return flag;
}

/*
 Depth first search and find whether having a safe path to reach river bank
 @param graph The graph stored by the adjacent table
 @param startPoint The point we start search
 @param visited A array to tag the elemeent whether has been visited
 @retuen
 */
int DFS(pGraph graph, vertex startPoint, int *visited) {
	int flag = 0;
	vertex v;
	visited[startPoint] = 1;
	if (isSafe(graph, startPoint)) {
		flag = 1;
		return flag;
	} else {
		for (v = 0; v < graph->vertex_num; v++) {
			if (visited[v] == 0 && isJump(graph, startPoint, v)) {
				flag = DFS(graph, v, visited);
				if (flag == 1) {
					return flag;
				}
			}
		}
	}
	return flag;
}

/*
 *James first jump action,similar of the isJump method,but sometimes ewe
 *need to consider the radius if the start points, so we separate the
 *first jump from followed jumps
 *@param graph The graph to store points collection and some information
 *@param startPoint_x The x-coordinate of the start point
 *@param startPoint_y The x-coordinate of the start point
 *@param v The index of the point in the graph's collection
 */
int firstJump(pGraph graph, int startPoint_x, int startPoint_y, vertex v) {
	if (calculateTwoPointDistance(startPoint_x, startPoint_y,
			graph->collection[v].x, graph->collection[v].y)
			> graph->maxDistance) {
		return 0;
	} else {
		return 1;
	}
}

/*
 * Save James By BFS method
 *@param graph The graph to store points collection and some information
 *@param startPoint_x The x-coordinate of the start point
 *@param startPoint_y The x-coordinate of the start point
 *@param v The index of the point in the graph's collection
 *@param visited A array to tag which point has been accessed
 */
int saveJamesBFS(pGraph graph, int startPoint_x, int startPoint_y, int *visited) {
	vertex v;
	int flag = 0;
	for (v = 0; v < graph->vertex_num; v++) {
		if (visited[v] == 0
				&& firstJump(graph, startPoint_x, startPoint_y, v)) {
			flag = BFS(graph, v, visited);
			if (flag == 1) {
				return flag;
			}
		}
	}
	return flag;
}

/*
 * Save James By BFS method
 *@param graph The graph to store points collection and some information
 *@param startPoint_x The x-coordinate of the start point
 *@param startPoint_y The x-coordinate of the start point
 *@param v The index of the point in the graph's collection
 *@param visited A array to tag which point has been accessed
 */
int saveJamesDFS(pGraph graph, int startPoint_x, int startPoint_y, int *visited) {
	vertex v;
	int flag = 0;
	for (v = 0; v < graph->vertex_num; v++) {
		if (visited[v] == 0
				&& firstJump(graph, startPoint_x, startPoint_y, v)) {
			flag = DFS(graph, v, visited);
			if (flag == 1) {
				return flag;
			}
		}
	}
	return flag;
}

/*
 * Initialize a visited array that make them all to zero
 */
void initVisited(pGraph graph, int *visited) {
	int i;
	for (i = 0; i < graph->vertex_num; i++) {
		visited[i] = 0;
	}
}

/*
 * Run method
 */
int main() {
	pGraph graph = buildGraph();
	int visited[graph->vertex_num];
	initVisited(graph, visited);
	int flag = saveJamesBFS(graph, 0, 0, visited);
	if (flag) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}
	return 0;
}

