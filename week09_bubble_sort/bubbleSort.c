/*
 * bubbleSort.c
 *
 *  Created on: 2017年5月18日
 *      Author: ygh
 */

#include <stdio.h>

typedef int elementType;
#define  MAX_LENGTH 100000

/*
 * Swap two integer number value
 */
void swap(elementType *a, elementType *b) {
	int temp = *b;
	*b = *a;
	*a = temp;
}
/*
 * A method to implement bubble sort.If the bubble sort has no any swap
 * operation at one time,indicating the array has been ordered.So we use a
 * tag to make it effective
 *@param a A integer array need to sort
 *@param n The length of the array
 */
void bubble_sort(elementType a[], int n) {
	int i, j, flag;
	for (i = n - 1; i >= 0; i--) {
		flag = 0;
		for (j = 0; j < i; j++) {
			if (a[j] > a[j + 1]) {
				swap(&a[j], &a[j + 1]);
				flag = 1;
			}
		}
		if (flag == 0) {
			break;
		}
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
	bubble_sort(a, n);
	printArray(a, n);
	return 0;
}
