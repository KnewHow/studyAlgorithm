/*
 * kruskal.c
 *
 *  Created on: 2017年5月15日
 *      Author: ygh
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 10001 /*define the max number of the vertex*/
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
			e->v1--;
			e->v2--;
			insertEdgeToLink(graph, e, isOrdered);
		}
	}

	return graph;
}

/*----------------------define collection and some operator of graph's nodes-----------------------------*/

/*
 * The element of collection
 */
typedef vertex elementType;

/*
 * The index of root element,we use it as the collection name
 */
typedef vertex setName;

/*
 * A array to store the collection,we set the
 * first index is 0
 */
typedef elementType setType[MAX_VERTEX_NUM];

/*
 * Initialize collection
 * @param A <code>elementType</code> array to store the collections,maybe
 * many collection will be stored in this array
 * @param n The length of the collection
 */
void initializeVSet(setType s, int n) {
	elementType x;
	for (x = 0; x < n; x++) {
		s[x] = -1;
	}
}

/*
 * Union two collections which is showed by root element.We will union smaller collection
 * to greater collection and we will update the quantity for greater collection
 * @param s A <code>elementType</code> array to store the collections,maybe
 * many collection will be stored in this array
 * @param root1 The root element of the first collection
 * @param root2 The root element of the second collection
 */
void unionCollection(setType s, setName root1, setName root2) {
	/*
	 * If root2's quantity greater than root1
	 */
	if (s[root2] < s[root1]) {
		s[root2] += s[root1];
		s[root1] = root2;
	} else {
		s[root1] += s[root2];
		s[root2] = root1;
	}
}

/*
 * Find the element in which collection and use the root element
 * to represent this collection and return it.In this method,we will compress path
 * @param s A <code>elementType</code> array to store the collections,maybe
 * many collection will be stored in this array
 * @param x The element we find which collection it in.
 */
setName find(setType s, elementType x) {
	if (s[x] < 0) {
		return x;
	} else {
		/*
		 *compress path
		 */
		return s[x] = find(s, s[x]);
	}
}

/*
 * Check v1 and v1 whether is belong to a same collection. If not union these
 * two collection,otherwise do nothing.
 * @param vSet A <code>elementType</code> array to store the collections,maybe
 * many collection will be stored in this array
 * @param v1 The index of node in the graph,also the element is the collection.
 * @param v2 The index of node in the graph,also the element is the collection.
 * @return If the two element is belong same collection,union them and return 1
 * else do nothing and return 0;
 */
int checkCircle(setType vSet, vertex v1, vertex v2) {
	setName root1 = find(vSet, v1);
	setName root2 = find(vSet, v2);
	if (root1 == root2) {
		return 0;
	} else {
		unionCollection(vSet, root1, root2);
		return 1;
	}
}

/*-------------define the minimal heap of edge-------------------*/

/*
 * Update the tree whose root element index is p into minimal heap,we use the edgs's
 * weight as the to construct the minimal heap.
 *
 * @param eset A array of edge to store the heap,because the edge is point variable
 * So the eSet is a edge type array,you can compare it with <code>int* arr</code>
 * @param The index of the root element.
 * @param n The length of the heap,the max index is n-1 in this case. And
 * this heap index is start from zero.
 */
void percDowm(edge eSet, int p, int n) {
	int parent, child;
	struct eNode x;

	x = eSet[p];
	for (parent = p; (parent * 2 + 1) < n; parent = child) {
		/*
		 * Because the first index if from zero,so the left child
		 * is parent*2+1
		 */
		child = parent * 2 + 1;
		/*
		 * Find smaller weigh between the left child and right child
		 */
		if ((child != n - 1) && eSet[child].weight > eSet[child + 1].weight) {
			child++;
		}
		if (x.weight <= eSet[child].weight) {
			break;
		} else {
			eSet[parent] = eSet[child];
		}
	}
	eSet[parent] = x;
}

/*
 * Initialize eSet heap and update it to be the minimal heap
 * @param graph A graph which is stored by adjacent list
 * @param eSet A array of the edge as the minimal heap
 */
void initializeESet(adjacentTableGraph graph, edge eSet) {
	vertex v;
	ptrToAdjNode w;
	int counter = 0;
	for (v = 0; v < graph->vertex_number; v++) {
		for (w = graph->g[v].head; w; w = w->next) {
			/*
			 * expect for put same edge to it,we only
			 * put <v1,v2> to it.
			 */
			if (v < w->adjVerx) {
				eSet[counter].v1 = v;
				eSet[counter].v2 = w->adjVerx;
				eSet[counter].weight = w->weight;
				counter++;
			}

		}
	}
	/*
	 * Initialize the minimal heap
	 */
	for (counter = graph->edge_nunber / 2; counter >= 0; counter--) {
		percDowm(eSet, counter, graph->edge_nunber);
	}
}

/*
 * Get minimal edge from the minimal weight heap
 * @param eset A array of edge to store the heap,because the edge is point variable
 * So the eSet is a edge type array,you can compare it with <code>int* arr</code>
 * @param The current size of the minimal heap
 * @return The index of the minimal edge in this heap(array)
 */
int getEdge(edge eSet, int currentSize) {
	if (currentSize == 0) {
		return currentSize - 1;
	}
	struct eNode temp = eSet[currentSize - 1];
	eSet[currentSize - 1] = eSet[0];
	eSet[0] = temp;
	percDowm(eSet, 0, currentSize - 1);
	return currentSize - 1;
}

/*
 * Implement the kruskal algorithms to find the minimal created tree
 * Algorithms thought:we choose the minimal edge from graph but don't
 * construct a circle each time. Until we choose the V-1 edges. The V
 * is equal with the quantity of the graph's vertex
 * In this program,we will use a counter to record the quantity of edges
 * At last of this method,if we check the quantity of the edge is less than
 * V-1, it indicates the graph is not collected,so -1 will be return,otherwise we will return
 * the minimal created tree total weight.
 * @param graph A graph which is stored by adjacent list
 * @param mst A A graph which is stored by adjacent list to store the minimal created tree
 * @return If the graph is collected,the weight of the minimal created tree
 * will be return, otherwise return -1
 */
int kruskal(adjacentTableGraph graph, adjacentTableGraph mst) {
	/*
	 * totalWeight is to record the total weight
	 * of the minimal created tree
	 */
	weightType totalWeight;
	/*
	 * eCounter is to record the quantity of edges which has been
	 * insert the <code>mst<code>
	 *
	 * nextEdge is to record the next minimal edge in the minimal heap
	 */
	int eCounter, nextEdge;

	/*
	 *A set of the vertex to store the vertex and implement
	 *some operation such as union find and so on
	 */
	setType vSet;

	/*
	 * A array of edge to as the minimal heap to store the egdes
	 */
	edge eSet;

	/*
	 * Initialize some variables
	 */
	initializeVSet(vSet, graph->vertex_number);
	eSet = (edge) malloc((sizeof(struct eNode)) * (graph->edge_nunber));
	initializeESet(graph, eSet);
//	mst = createLGraph(graph->vertex_number);
	totalWeight = 0;
	eCounter = 0;
	nextEdge = graph->edge_nunber;
	while (eCounter < graph->vertex_number - 1) {
		nextEdge = getEdge(eSet, nextEdge);
		if (nextEdge < 0) {
			break;
		}
		/*
		 * Check whether a circle between two vertex
		 */
		if (checkCircle(vSet, eSet[nextEdge].v1, eSet[nextEdge].v2)) {
			insertEdgeToLink(mst, eSet + nextEdge, 0);
			totalWeight += eSet[nextEdge].weight;
			eCounter++;
		}
	}
	if (eCounter < graph->vertex_number - 1) {
		totalWeight = -1;
	}
	return totalWeight;
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
	adjacentTableGraph graph = buildLGraph(0);
	adjacentTableGraph mst = createLGraph(graph->vertex_number);
	vertex visited[graph->vertex_number];
	weightType totalWeight = kruskal(graph, mst);
	printf("totalWeight:%d\n", totalWeight);
	initVisited(graph->vertex_number, visited);
	DFS(mst, 0, visited);
	return 0;
}
