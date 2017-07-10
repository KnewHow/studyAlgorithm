/*
 * insertionSort.c
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
 * Implement insertion sort.
 *@param a A integer array need to sort
 *@param n The length of the array
 */
void insertion_sort(elementType a[], int n) {
	int i, j;
	elementType temp;
	for (i = 1; i < n; i++) {
		temp = a[i];
		for (j = i; j > 0 && a[j - 1] > temp; j--) {
			a[j] = a[j - 1];
		}
		a[j] = temp;
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
	insertion_sort(a, n);
	printArray(a, n);
	return 0;
}
