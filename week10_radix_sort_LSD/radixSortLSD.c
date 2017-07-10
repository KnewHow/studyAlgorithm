/*
 * radixSortLSD.c
 * Implement radix sort of Least Significant Digit
 *
 *  Created on: 2017年5月23日
 *      Author: ygh
 */
#include <stdio.h>
#include <stdlib.h>

#define  MAX_LENGTH 10000

/*
 *The quantity of the the keys of element
 *For example 0-9999 have four keys
 */
#define MAX_DIGIT 6
/*
 *The quantity of the bucket.In this case ,we sort integer number
 *So the buckets is from 0 to 9
 */
#define RADIX 10

#define BEGIN_DIGIT 0

/*
 * The type of the element type
 */
typedef int elementType;

/*
 * Define a data structure for bucket node
 */
typedef struct node *ptrToNode;
typedef struct node {
	/*
	 * The element type the bucket node store
	 */
	elementType key;
	/*
	 * A next point to point next element
	 */
	ptrToNode next;

};

/*
 * Define a data structure for bucket head that
 * store the head point and rear point for the elements
 */
typedef struct headNode {
	ptrToNode head, rear;
};

/*
 * Define a array of headNode to store the all buckets
 */
typedef struct headNode bucket[RADIX];

/*
 * Get the digit by the current number and current needed digit
 * @param x The current number
 * @param d The current digit
 * @return The digit needed
 */
int getDigit(elementType x, int d) {
	int i;
	int di;
	for (i = 0; i < d; i++) {
		di = x % RADIX;
		x = x / RADIX;
	}
	return di;
}

void LSDRadixSort(elementType a[], int n) {
	int d, di, i;
	/*
	 * Define a bucket array to store all buckets
	 */
	bucket b;

	/*
	 * Define three node point
	 * @param temp Store temporary node
	 * @param p A node point will be used when search
	 * @param list A node point to build elements list and recovery
	 * elements from finished sort
	 */
	ptrToNode temp, p, list;

	/*
	 * Initialize each bucket head and rear into NULL
	 */
	for (i = BEGIN_DIGIT; i < RADIX; i++) {
		b[i].head = b[i].rear = NULL;
	}

	/*
	 * Change array elements into list elements,but it is DESC
	 */
	for (i = 0; i < n; i++) {
		temp = (ptrToNode) malloc(sizeof(struct node));
		temp->key = a[i];
		temp->next = list;
		list = temp;
	}

	/*
	 * Do radix sort
	 */
	for (d = 1; d <= MAX_DIGIT; d++) {
		p = list;
		while (p) {
			di = getDigit(p->key, d);
			if (di < 0) {
				di = di * (-1);
			}
			/*
			 * Delete this element from the list
			 */
			temp = p;
			p = p->next;
			temp->next = NULL;
			if (b[di].head == NULL) {
				b[di].head = b[di].rear = temp;
			} else {
				b[di].rear->next = temp;
				b[di].rear = temp;
			}
		}

		/*
		 * Recover the elements has been deal with,using
		 * the list to point the head
		 */
		list = NULL;
		for (di = RADIX - 1; di >= BEGIN_DIGIT; di--) {
			if (b[di].head) {
				b[di].rear->next = list;
				list = b[di].head;
				/*
				 * Clear the head and rear
				 */
				b[di].rear = b[di].head = NULL;
			}
		}
	}

	/*
	 * Put sorted list data to array
	 */
	for (i = 0; i < n; i++) {
		temp = list;
		list = list->next;
		a[i] = temp->key;
		free(temp);
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
 * Separate a array into positive array and negative array
 * @param a A array store the positive number or negative number
 * @param n The length of the a
 * @param pL The length of the positive array
 * @param pL The length of the negative array
 */
void separate(elementType *a, int n, int *pL, int *nL,
		elementType positiveArr[], elementType negativeArr[]) {
	int i;
	for (i = 0; i < n; i++) {
		if (a[i] < 0) {
			negativeArr[(*nL)++] = a[i];
		} else {
			positiveArr[(*pL)++] = a[i];
		}
	}
}

/*
 * Implement radix sort
 */
void radixSort(elementType a[], int n) {
	int positiveArr[MAX_LENGTH];
	int negativeArr[MAX_LENGTH];
	int pL = 0, nL = 0, i, j;
	separate(a, n, &pL, &nL, positiveArr, negativeArr);
	LSDRadixSort(positiveArr, pL);
	LSDRadixSort(negativeArr, nL);
	i = nL - 1;
	j = 0;
	while (i >= 0) {
		a[j] = negativeArr[i];
		i--;
		j++;
	}
	i = 0;
	while (i < pL) {
		a[j] = positiveArr[i];
		i++;
		j++;
	}

}

int main() {
	elementType a[MAX_LENGTH];
	int n;
	scanf("%d", &n);
	getInputData(a, n);
	radixSort(a, n);
	printArray(a, n);
	return 0;
}

