/*
 * InsertionOrHeap.c
 *dsds
 *dsds
 *  Created on: 2017年5月20日
 *      Author: ygh
 */
#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 100
#define MAX_VALUE 65535
typedef int elementType;

/*
 *Get the input data from the command line
 *@param source A <code>elementType</code> array to store the original data
 *@param partical A <code>elementType</code> array to store elements which has been sorted partial
 *@param n The length of the array
 */
void getInputData(elementType source[], elementType partial[], int n) {
	int i;
	elementType x;
	for (i = 0; i < n; i++) {
		scanf("%d", &x);
		source[i] = x;
	}

	for (i = 0; i < n; i++) {
		scanf("%d", &x);
		partial[i] = x;
	}
}

/*
 * Print the array to console
 * @param a A integer array need to sort
 * @param n The length of the array
 */
void printArray(elementType a[], int n) {
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

/*
 * Judge which sorting method the system has used.If it is the insertion merge,return the index
 * of the next insert point.Otherwise return zero
 * @param source A <code>elementType</code> array to store the original data
 * @param partical A <code>elementType</code> array to store elements which has been sorted partial
 * @param n The length of the array
 */
int judgeMergeOrInsertion(elementType source[], elementType partial[], int n) {
	int i;
	int min = partial[0];
	int insertPoint;
	for (i = 1; i < n; i++) {
		insertPoint = i;
		if (partial[i] >= min) {
			min = partial[i];
		} else {
			break;
		}
	}
	for (; i < n; i++) {
		if (partial[i] != source[i]) {
			return 0;
		}
	}
	return insertPoint;
}

/*
 * Execute one time insertion sort from insertPoint
 * @param partial A <code>elementType</code> array to store elements which has been sorted partial
 * @param inserPoint The index of next point
 */
void insertion_sort_pass(elementType partial[], int inserPoint) {
	int i;
	int x = partial[inserPoint];
	for (i = inserPoint; i > 0; i--) {
		if (x < partial[i - 1]) {
			partial[i] = partial[i - 1];
		} else {
			break;
		}
	}
	partial[i] = x;
}

/*
 * Swap two integer number
 */
void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

/*
 * We know,in the heap sort,we get the maximal value from heap,the heap size will
 * decrease each time,So the last elements is the bigger and ordered.
 * We can according to this to find the size of the current heap.
 * @param partial A <code>elementType</code> array to store elements which has been sorted partial
 * @param inserPoint The index of next point
 */
int getSizeOfHeap(int partial[], int n) {
	int max = partial[0];
	int i;
	for (i = n - 1; i >= 0; i--) {
		if (partial[i] < max) {
			return i;
		}
	}
	return 0;
}

/*
 * Update the element of tree make the tree to be a maximal heap
 * @param partial A <code>elementType</code> array to store the elements
 * @param p The index of the element need to update
 * @param n The length of the array
 */
void percDowm(elementType partial[], int p, int n) {
	int parent, child = 0;
	elementType x = partial[p];
	for (parent = p; (parent * 2 + 1) < n; parent = child) {
		child = parent * 2 + 1;
		if ((child != n - 1) && (partial[child] < partial[child + 1])) {
			child++;
		}
		if (x >= partial[child]) {
			break;
		} else {
			partial[parent] = partial[child];
		}
	}
	partial[parent] = x;
}

/*
 * Execute heap sort one time
 * @param partial A <code>elementType</code> array to store elements
 * which has been sorted partial
 * @param size The size of the current heap
 */
void heapSortPass(int partial[], int size) {
	swap(&partial[0], &partial[size]);
	percDowm(partial, 0, size);
}

int main() {
	elementType source[MAX_LENGTH];
	elementType partial[MAX_LENGTH];
	int n;
	int size = 0;
	scanf("%d", &n);
	getInputData(source, partial, n);
	int inserPoint = judgeMergeOrInsertion(source, partial, n);
	if (inserPoint != 0) {
		if (inserPoint < n) {
			insertion_sort_pass(partial, inserPoint);
		}
		printf("Insertion Sort\n");
	} else {
		printf("Heap Sort\n");
		size = getSizeOfHeap(partial, n);
		heapSortPass(partial, size);
	}
	printArray(partial, n);
	return 0;
}
