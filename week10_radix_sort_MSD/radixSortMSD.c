/*
 * radixSortMSD.c
 *Implement radix sort(Most Significant Digit)
 *  Created on: 2017年5月24日
 *      Author: ygh
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 100000
#define RADIX 10
#define MAX_DIGIT 3
#define BEGIN_DIGIT 0

/*
 * Define element type the array or list store
 */
typedef int elementType;

/*
 * Define a list to store elememts from array
 */
typedef struct node *ptrToNode;
typedef struct node {
	elementType key;
	ptrToNode next;
};

/*
 * Define a bucket to point the each bucket list head and rear
 */
typedef struct headNode {
	ptrToNode head, rear;
};

/*
 *Define a bucket array to store all buckets
 */
typedef struct headNode bucket[RADIX];

/*
 * Get the current number digit by current digit needed
 * @param x The number current need to sort
 * @param d The digit current need to get
 * @return A current digit of this number
 */
int getDigit(elementType x, int d) {
	int i;
	int de;
	for (i = 0; i < d; i++) {
		de = x % RADIX;
		x = x / RADIX;
	}
	return de;
}

/*
 * Implement radix sort by MSD,we will recursive to implement it
 */
void radixSortMSD(elementType a[], int left, int right, int d) {
	int di, i, j;
	/*
	 * Define three point of the list
	 * @param p The point is used for searching
	 * @param temp The point is used for temporary store
	 * @param list The point is used for store all elements
	 */
	ptrToNode p, temp, list = NULL;
	/*
	 * Define a bucket array for all buckets
	 */
	bucket b;

	/*
	 * recursive end conditional
	 */
	if (d == 0) {
		return;
	}
	/*
	 * Initialize all bucket,let head and rear get NULL
	 */
	for (i = BEGIN_DIGIT; i < RADIX; i++) {
		b[i].head = b[i].rear = NULL;
	}

	/*
	 * Change array storing into list storing,it make the data
	 * easily to be deal with
	 */
	list = NULL;
	for (i = left; i <= right; i++) {
		temp = (ptrToNode) malloc(sizeof(struct node));
		temp->key = a[i];
		temp->next = list;
		list = temp;
	}

	p = list;
	/*
	 * Get digit from current number and deal with them
	 */
	while (p) {
		di = getDigit(p->key, d);
		temp = p;
		p = p->next;
		temp->next = NULL;
		if (b[di].head == NULL) {
			b[di].rear = temp;
			b[di].head=temp;
		} else {
			temp->next = b[di].head;
			b[di].head = temp;
		}

	}

	/*
	 * recover elements from bucket
	 */
	i = j = left;
	for (di = 0; di < RADIX; di++) {
		if (b[di].head) {
			p = b[di].head;
			while (p) {
				temp = p;
				p = p->next;
				a[j++] = temp->key;
				free(temp);
			}
			/*
			 *recursive caller this method
			 */
			radixSortMSD(a, i, j - 1, d - 1);
			i = j;
		}
	}
}

/*
 * Implement radix sort
 */
void radixSort(elementType a[], int n) {
	radixSortMSD(a, 0, n - 1, MAX_DIGIT);
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
	elementType a[MAX_LENGTH];
	int n;
	scanf("%d", &n);
	getInputData(a, n);
	radixSort(a, n);
	printArray(a, n);
	printf("just test");
	return 0;
}

