/*
 * save.c
 *
 *  Created on: 2017年5月13日
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
	node1Element x; /*The x-coordinate of the point*/
	node1Element y; /*The y-coordinate of the point*/
} point[MAX_LENGTH];

/*
 * Define a data structure to store a graph
 */
typedef struct node2 *pGraph;
typedef struct node2 {
	int vertex_num; /*The quantity of the all points*/
	int maxDistance; /*The max distance the James can jump*/
	point collection; /*A structure array to store the points*/
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
	if (x >= 0 && y >= 0) {
		distance = calculateDtoSafe(x, y, 50, 50);
	}
	if (x >= 0 && y <= 0) {
		distance = calculateDtoSafe(x, y, 50, -50);
	}

	if (x <= 0 && y >= 0) {
		distance = calculateDtoSafe(x, y, -50, 50);
	}

	if (x <= 0 && y <= 0) {
		distance = calculateDtoSafe(x, y, -50, -50);
	}

	if (distance <= graph->maxDistance) {
		return 1;
	} else {
		return 0;
	}
}

/*
 * Judge the point that whether the James Bond can jump into river bank
 * @param graph A graph to stored all points' collection
 * @param point The index of point in the points' collection
 * @return 1 will be return if James Bond can jump into river bank, otherwise
 * return 0
 */
int getLastDistance(pGraph graph, vertex point) {
	int x, y, distance = 0;
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

	return distance;
}

/*
 * Whether the James can jump over from source to destination
 */
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
 * Adjust the point whether is in the pool(-50=<x=<50 and -50=<y=<50)
 */
int isInner(pGraph graph, vertex v) {
	int x = graph->collection[v].x;
	int y = graph->collection[v].x;
	if (x >= -50 && x <= 50 && y >= -50 && y <= 50) {
		return 1;
	} else {
		return 0;
	}
}

/*
 Breadth first search and find whether having a safe path to reach river bank
 @param graph The graph stored by the adjacent table
 @param startPoint The point we start search
 @param dist A integer to store the edges from source to destination
 @param path A integer to store the index of last vertex which is shortest to pass current point
 @param safePoint A integer array to store the safe points
 */
int unWeight(pGraph graph, vertex startPoint, int *dist, int *past,
		int *safePoint) {
	dist[startPoint] = 1;
	/*
	 * The point index in the graph's points' collection
	 */
	vertex w, v;
	int counter = 0;
	pQueue queue = createEmptyQueue();
	addQueue(queue, startPoint);
	if (isSafe(graph, startPoint)) {
		safePoint[counter] = startPoint;
		counter++;
	}
	while (!isQueueEmpty(queue)) {
		w = deleteEleFromQueue(queue);
		for (v = 0; v < graph->vertex_num; v++) {
			if (dist[v] == -1 && isJump(graph, v, w) && isInner(graph, v)) {

				if (isSafe(graph, v)) {
					safePoint[counter] = v;
					counter++;
				}

				dist[v] = dist[w] + 1;
				past[v] = w;
				addQueue(queue, v);
			}
		}
	}
	return counter;
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
 * Find a minimal distance safe point from the a series safe points
 * @param graph A graph to store point
 * @param digt A integer array to store edges from source point to destination point
 * @param safePoints A integer array to store the index of the safe point in graph
 * @param length The length of the safe point array
 */
int findShortestSafePoint(pGraph graph, int *digt, int *safePoints, int length) {
	int i, safeIndex, p;
	double minDistance = 65536, distance;
	int shortestPoint;
	for (i = 0; i < length; i++) {
		safeIndex = safePoints[i];
		p = digt[safeIndex];
		distance = getLastDistance(graph, safeIndex) + graph->maxDistance * p;
		if (distance < minDistance) {
			minDistance = distance;
			shortestPoint = safeIndex;
		}
	}
	return shortestPoint;
}

/*============================define a stack and some relative operators=============*/
typedef int stackElement;
typedef struct nodeStack {
	stackElement element;
	struct nodeStack *next;
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

/*
 * Search a path to destination with a path recorded array
 * @param graph The graph to store the point
 * @param path A integer array to store the index of last vertex which is shortest to pass current point
 * @param length The length of the path
 * @param destination The index of the destination in graph
 *
 */
void findPath(pGraph graph, int *path, int length, int destination) {
	pStack stack = createEmptyStack();
	vertex v;
	int times = 0;
	int index = destination;
	push(stack, index);
	while (v != -1) {
		v = path[index];
		push(stack, v);
		times++;
		index = v;
	}

	pop(stack);
	printf("%d\n", times + 1);
	while (!isEmpty(stack)) {
		stackElement element = pop(stack);
		printf("%d %d\n", graph->collection[element].x,
				graph->collection[element].y);
	}
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

/*
 * Is a safe path reaching bank and find the shortest path.Use no-weight
 * searching shortest method. We let first jump separate because we consider the
 * source is have radius is really,in order to update program in the future.
 * So we find source adjacent points and let them to search safe path.
 * We calculate the shortest safe point from each adjacent points searching result and store
 * them is <code>shortPoints</code>,when all adjacent points search finishing,we calculate the
 * shortest point from <code>shortPoints</code>.And print the path using stack.
 *
 *@param graph The graph to store points collection and some information
 *@param startPoint_x The x-coordinate of the start point
 *@param startPoint_y The x-coordinate of the start point
 *@param v The index of the point in the graph's collection
 *@param dist A integer to store the edges from source to destination
 *@param path A integer to store the index of last vertex which is shortest to pass current point
 */
void saveJamesBFS(pGraph graph, int startPoint_x, int startPoint_y, int *dist,
		int *path) {
	vertex v;
	int safePoint[graph->vertex_num];
	int shortestIndex = 0;
	/*
	 *store the shortest safe point from adjacent point result
	 */
	int shortPoints[graph->vertex_num];
	int counter = 0;
	int length = 0;
	int destination;
	for (v = 0; v < graph->vertex_num; v++) {
		if (dist[v] == -1 && firstJump(graph, startPoint_x, startPoint_y, v)) {
			fullArray(safePoint, graph->vertex_num, -1);
			length = unWeight(graph, v, dist, path, safePoint);
			if (length != 0) {
				shortestIndex = findShortestSafePoint(graph, dist, safePoint,
						length);
				shortPoints[counter] = shortestIndex;
				counter++;
			}
		}
	}
	if (counter == 0) {
		printf("0");
	} else {
		/*
		 *calculate the shortest safe point from the some shorter safe point
		 */
		destination = findShortestSafePoint(graph, dist, shortPoints, counter);
		findPath(graph, path, graph->vertex_num, destination);
	}
}

/*
 * Run method
 */
int main() {
	pGraph graph = buildGraph();
	if (graph->maxDistance >= 25) {
		printf("1");
		return 0;
	} else {
		int dist[graph->vertex_num];
		int path[graph->vertex_num];
		fullArray(dist, graph->vertex_num, -1);
		fullArray(path, graph->vertex_num, -1);
		saveJamesBFS(graph, 0, 0, dist, path);
		return 0;
	}

}

