/*
 * mergeOrInsert.c
 *
 *  Created on: 2017年5月19日
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
 * Find the length of merge sort sub-sequence.
 * Algorithms thoughts:
 * we know the sequence length is 2 4 8 16,so we can let length from 2 4 8 ... n
 * 1.We judge the length whether more than 2, we check the number whether ordered between two sub-sequence. If all two sub-sequence is ordered,we will check the length whether more than four. Otherwise the length is equal two and return it.
 * 2.we let length increase no more than n ,we can get length and return it.
 *
 * @param partial A <code>elementType</code> array to store elements which has been sorted partial
 * @param n The length of the array
 * @return The length of the sub-sequence
 */
int findMergeSubSequenceLength(int partial[], int n) {
	int length, i;
	for (length = 2; length <= n; length *= 2) {
		for (i = 1; i < n / length; i += 2) {
			if (partial[i * length - 1] > partial[i * length]) {
				return length;
			}
		}
	}
	return n;
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

int main() {
	elementType source[MAX_LENGTH];
	elementType partial[MAX_LENGTH];
	int n;
	int length = 0;
	elementType *tmpA;
	scanf("%d", &n);
	getInputData(source, partial, n);
	int inserPoint = judgeMergeOrInsertion(source, partial, n);
	if (inserPoint != 0) {
		if (inserPoint < n) {
			insertion_sort_pass(partial, inserPoint);
		}
		printf("Insertion Sort\n");
	} else {
		tmpA = malloc(n * sizeof(elementType));
		length = findMergeSubSequenceLength(partial, n);
		mergerPass(partial, tmpA, n, length);
		printf("Merge Sort\n");
	}
	printArray(partial, n);
	return 0;
}
