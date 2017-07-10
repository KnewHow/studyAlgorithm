/*
 * countAge.c
 *
 *  Created on: 2017年5月24日
 *      Author: ygh
 */

#include <stdio.h>
#include <stdlib.h>
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
 * Merge sub-sequence to original array.
 * @param a original <code>elementType</code> array to store the elements
 * @param tmpA temporary  <code>elementType</code> array to store the temporary elements
 * @param l The start index of left sub-sequence
 * @param r The start index of left sub-sequence
 * @param rightEnd The end index of left sub-sequence
 */
void merge(elementType a[], elementType tmpA[], int l, int r, int rightEnd) {
	/*
	 * lefeEnd is the r-1,the sub-sequence is adjacent
	 */
	int leftEnd = r - 1;
	/*
	 * tmp is the counter of the <code>tmpA</code>
	 * we should let <code>tmpA</code> index corresponding original array
	 */
	int tmp = l;
	/*
	 * Record the quantity of the all elements
	 */
	int numElements = rightEnd - l + 1;
	int i;
	while (l <= leftEnd && r <= rightEnd) {
		if (a[l] <= a[r]) {
			tmpA[tmp++] = a[l++];
		} else {
			tmpA[tmp++] = a[r++];
		}
	}
	while (l <= leftEnd) {
		tmpA[tmp++] = a[l++];
	}
	while (r <= rightEnd) {
		tmpA[tmp++] = a[r++];
	}

	/*
	 * Put <code>tmpA</code> elements into the original array
	 */
	for (i = 0; i < numElements; i++, rightEnd--) {
		a[rightEnd] = tmpA[rightEnd];
	}
}

/*
 * Implement the merge sort
 * @param a original <code>elementType</code> array to store the elements
 * @param tmpA temporary  <code>elementType</code> array to store the temporary elements
 * @param l The start index of the array which need to sort
 * @param rightEnd The end index of the array which need to sort
 */
void mergetSortRecursive(elementType a[], elementType tmpA[], int l,
		int rightEnd) {
	int center;
	if (l < rightEnd) {
		center = (l + rightEnd) / 2;
		mergetSortRecursive(a, tmpA, l, center);
		mergetSortRecursive(a, tmpA, center + 1, rightEnd);
		merge(a, tmpA, l, center + 1, rightEnd);
	}
}

/*
 * Implement merge sort
 * @param a A integer array need to sort
 * @param n The length of the array
 */
void merger_sortRecursive(elementType a[], int n) {
	elementType *tmpA;
	tmpA = malloc(n * sizeof(elementType));
	if (tmpA != NULL) {
		mergetSortRecursive(a, tmpA, 0, n - 1);
		free(tmpA);
	} else {
		printf("no enough space to apply for temporary array");
	}
}

/*
 *merge ordered sub-sequence
 * @param a original <code>elementType</code> array to store the elements
 * @param tmpA temporary  <code>elementType</code> array to store the temporary elements
 * @param n The length of the a
 * @param the ordered current sub-sequence length
 */
void mergerPass(elementType a[], elementType tmpA[], int n, int lenth) {
	int i, j;
	/*
	 * The loop will stop when meet the last two ordered sub-sequence
	 * The rest may be two sub-sequence of one sub-sequence
	 */
	for (i = 0; i <= n - 2 * lenth; i += lenth * 2) {
		merge(a, tmpA, i, i + lenth, i + 2 * lenth - 1);
	}
	/*
	 *If the rest of is two sub-sequence
	 */
	if (i + lenth < n) {
		merge(a, tmpA, i, i + lenth, n - 1);
	} else {
		for (j = i; j < n; j++)
			tmpA[j] = a[j];
	}
}

/*
 * Use loop method to implement the merge sort
 * @param a A integer array need to sort
 * @param n The length of the array
 */
void merger_SortLoop(elementType a[], int n) {
	int length;
	elementType *tmpA;
	length = 1;
	tmpA = malloc(n * sizeof(elementType));
	if (tmpA != NULL) {
		while (length < n) {
			/*
			 * merge ordered sub-sequence into <code>tmpA</code>
			 */
			mergerPass(a, tmpA, n, length);
			length *= 2;
			/*
			 * merge ordered sub-sequence from <code>tmpA</code> into <code>a</code>
			 */
			mergerPass(tmpA, a, n, length);
			length *= 2;
		}
		free(tmpA);
	} else {
		printf("no enough to apply for temporary array");
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

/*
 * Count age and print them to console
 */
void countAge(elementType a[], int n) {
	int i;
	int key = a[0];
	int counter = 1;
	for (i = 1; i < n; i++) {
		if (a[i] == key) {
			counter++;
		} else {
			printf("%d:%d\n",key,counter);
			key = a[i];
			counter=1;
		}
	}
	printf("%d:%d\n",key,counter);
}

int main() {
	int a[MAX_LENGTH];
	int n;
	scanf("%d", &n);
	getInputData(a, n);
	merger_SortLoop(a, n);
	countAge(a, n);
	return 0;
}

