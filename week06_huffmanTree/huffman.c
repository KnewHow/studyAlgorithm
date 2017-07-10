/*
 * huffman.c
 *
 *  Created on: 2017年5月11日
 *      Author: ygh
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXELEMENT 10000
#define MINELEMENT -10001
#define MAXSIZE 1000

/*define data structure of minimum heap*/

/*the element type of minimum heap*/
typedef int elementType;

typedef struct node *pHeap;
typedef struct node {
	int *data; /*A integer array to store the element of minimum*/
	int size; /*the size of the minimum head*/
	int capacity; /*The capacity of the minimum head*/
};


typedef struct node2{
	char
};

/*Create a empty minimum heap with size*/

pHeap createEmptyMinHeap(int size) {
	pHeap heap = (pHeap) malloc(sizeof(struct node));
	heap->data = malloc((size + 1) * sizeof(elementType));
	heap->size = 0;
	heap->capacity = size;
	heap->data[0] = MINELEMENT;
	return heap;
}

/*
 * Whether the heap is empty
 */
int isHeapEmpty(pHeap heap) {
	return (heap->size == 0);
}

/*
 * Whether the heap is full
 */
int isHeapFull(pHeap heap) {
	return (heap->size == heap->capacity);
}

/*
 * Insert a element to a minimal heap and update themselves
 */
void insertElementToMinHeap(pHeap heap, elementType element) {
	int i;
	if (isHeapFull(heap)) {
		printf("the heap is full");
		return;
	} else {
		i = heap->size;
		i++;
		heap->data[i] = element;
		for (; element < heap->data[i / 2]; i = i / 2) {
			heap->data[i] = heap->data[i / 2];
		}
		heap->data[i] = element;
	}
}

/*
 * Delete a element from minimal heap
 */
elementType deleteElementFromMinHeap(pHeap heap) {
	elementType element, temp;
	int parent, child;
	if (isHeapEmpty(heap)) {
		printf("the heap is empty");
		return heap->data[0];
	} else {
		element = heap->data[1];
		temp = heap->data[heap->size--];
		/*
		 * Update the elements of the minimal heap
		 */
		for (parent = 1; parent * 2 < heap->size; parent = child) {
			child = parent * 2;
			/*
			 * Find the minimal index in sub tree
			 */
			if (child != heap->size
					&& heap->data[child + 1] < heap->data[child]) {
				child++;
			}
			/*
			 * temp is it the correct position
			 */
			if (temp <= heap->data[child]) {
				break;
			} else {
				heap->data[parent] = heap->data[child];
			}
		}
		heap->data[parent] = temp;
		return element;
	}

}

/*
 construct the max heap,the algorithem thought is same with delete method
 @param heap The binary tree who want to construct a max heap
 @param p The parent index of the tree
 */
void perdowm(pHeap heap, int index) {
	int parent, child;
	elementType temp = heap->data[index];
	for (parent = index; parent * 2 <= heap->size; parent = child) {
		child = parent * 2;
		/*
		 * Find the minimal index in sub tree
		 */
		if (child != heap->size && heap->data[child + 1] < heap->data[child]) {
			child++;
		}

		/*
		 * temp is it the correct position
		 */
		if (temp <= heap->data[child]) {
			break;
		} else {
			heap->data[parent] = heap->data[child];
		}
	}
	heap->data[parent] = temp;
}

/*
 * Build a minimal heap by integer array
 * @param arr The array provide data
 * @param length The length of the array
 * @return a minimal heap created
 */
pHeap buildMinHeap(int *arr, int length) {
	int i;
	pHeap heap = createEmptyMinHeap(length);
	for (i = 0; i < length; i++) {
		heap->data[++heap->size] = arr[i];
	}
	for (i = heap->size / 2; i > 0; i--) {
		perdowm(heap, i);
	}
	return heap;
}

/*
 print the heap
 @param heap The heap nend to print to the controal
 */
void toString(pHeap heap) {
	pHeap p = heap;
	printf("toString:");
	int i = 1;
	while (i <= p->size) {
		printf("%d ", p->data[i]);
		i++;
	}
	printf("\n");
}

int main() {
	int i, arr[10];
	int length = 10;
	int capatity = 30;
	//pHeap heap = createEmptyMinHeap(30);

	for (i = 10; i > 0; i--) {
		arr[10 - i] = i;
	}
	//printf("build a binary tree,not heap\t");
	//toString(heap);
	pHeap heap = buildMinHeap(arr, length);
	printf("constructor a binary into a heap\t");
	toString(heap);
//	pHeap heap = createEmptyMinHeap(30);
	/*for (; i <= 20; i++) {
	 insertElementToMinHeap(heap, i);
	 }
	 printf("test insert method\t");
	 toString(heap);
	 printf("delete max element%d\n", deleteElementFromMinHeap(heap));
	 toString(heap);
	 printf("delete max element%d\n", deleteElementFromMinHeap(heap));
	 toString(heap);
	 printf("delete max element%d\n", deleteElementFromMinHeap(heap));
	 toString(heap);
	 printf("delete max element%d\n", deleteElementFromMinHeap(heap));
	 toString(heap);
	 //testBuildHeap();*/
	printf("just test");
	return 0;
}

