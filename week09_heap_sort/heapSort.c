/*
 * heapSort.c
 *
 *  Created on: 2017年5月18日
 *      Author: ygh
 */

#include <stdio.h>

#define  MAX_LENGTH 100000
typedef int elementType;

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

/*
 * Get input data from command
 */
void getInputData(elementType *a, int n) {
	int i;
	elementType x;
	for (i = 0; i < n; i++) {
		scanf("%d", &x);
		a[i] = x;
	}
}

int main() {
	int a[MAX_LENGTH];
	int n;
	scanf("%d", &n);
	getInputData(a, n);
	heap_sort(a, n);
	printArray(a, n);
	return 0;
}

