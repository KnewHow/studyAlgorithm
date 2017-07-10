/*
 * quickSort.c
 *
 *  Created on: 2017年5月20日
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
 * Implement insertion sort.
 *@param a A <code>elementType</code> array need to sort
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
 *Get the pivot by get the median amount three number
 */
elementType getPivotByMedian3(elementType a[], int left, int right) {
	int center = (left + right) / 2;
	/*
	 * Let a[left]<= a[center] <= a[right]
	 */
	if (a[left] > a[center]) {
		swap(&a[left], &a[center]);
	}

	if (a[left] > a[right]) {
		swap(&a[left], &a[right]);
	}

	if (a[center] > a[right]) {
		swap(&a[center], &a[right]);
	}

	/*
	 * We has known the a[right] greater than a[center]
	 * so we swap the a[center] and a[right-1],so we just
	 * consider from a[left+1] to a[right-2] when we divide sub-set
	 */
	swap(&a[center], &a[right - 1]);
	return a[right - 1];

}

elementType getPivotByRandom(elementType a[], int left, int right) {
	int index = rand() % (right - left + 1) + left;
	return index;
}

/*
 * Implement quick sort,we get the pivot by the middle of three numbers
 * @param a A <code>elementType</code> array need to sort
 * @param left The starting index of sub-set
 * @param right The finishing index of sub-set
 * @param A cutoff to determine how many numbers rest we will
 * use the insertion sort.
 */
void qSort(elementType a[], int left, int right, int cutoff) {
	int low, high;
	elementType pivot;
	if (cutoff <= right - left) {
		pivot = getPivotByMedian3(a, left, right);
		low = left;
		high = right - 1;
		while (1) {
			while (a[++low] < pivot)
				;
			while (a[--high] > pivot)
				;
			if (low < high) {
				swap(&a[low], &a[high]);
			} else {
				break;
			}
		}
		swap(&a[low], &a[right - 1]);
		qSort(a, left, low - 1, cutoff);
		qSort(a, low + 1, right, cutoff);

	} else {
		insertion_sort(a + left, right - left + 1);
	}
}

/*
 * Implement quick sort,we get the pivot by the middle of three numbers
 * @param a A <code>elementType</code> array need to sort
 * @param left The starting index of sub-set
 * @param right The finishing index of sub-set
 * @param A cutoff to determine how many numbers rest we will
 * use the insertion sort.
 */
void qSortByRandom(elementType a[], int left, int right, int cutoff) {
	int low, high, index;
	elementType pivot;
	if (cutoff <= right - left) {
		index = getPivotByRandom(a, left, right);
		swap(&a[left], &a[index]);
		pivot = a[left];
		low = left;
		high = right;
		while (low < high) {
			while (low < high && a[high] >= pivot) {
				high--;
			}
			a[low] = a[high];
			while (low < high && a[low] <= pivot) {
				low++;
			}
			a[high] = a[low];
		}
		a[low] = pivot;
		qSortByRandom(a, left, low - 1, cutoff);
		qSortByRandom(a, low + 1, right, cutoff);
	} else {
		insertion_sort(a + left, right - left + 1);
	}
}

/*
 * Implement quick sort,we get the pivot by the middle of three numbers
 * @param a A <code>elementType</code> array need to sort
 * @param left The starting index of sub-set
 * @param right The finishing index of sub-set
 * @param A cutoff to determine how many numbers rest we will
 * use the insertion sort.
 */
void qSortByFirstNum(elementType a[], int left, int right, int cutoff) {
	int low, high;
	elementType pivot;
	if (cutoff <= right - left) {
		pivot = a[left];
		low = left;
		high = right;
		while (low < high) {
			while (low < high && a[high] >= pivot) {
				high--;
			}
			a[low] = a[high];
			while (low < high && a[low] <= pivot) {
				low++;
			}
			a[high] = a[low];
		}
		a[low] = pivot;
		qSortByFirstNum(a, left, low - 1, cutoff);
		qSortByFirstNum(a, low + 1, right, cutoff);
	} else {
		insertion_sort(a + left, right - left + 1);
	}
}

/*
 * Implement sort unitized interface
 * @param a A <code>elementType</code> array need to sort
 * @param n The length of the array
 */
void quickSort(elementType a[], int n) {
//	qSort(a, 0, n - 1, 100);
//	qSortByRandom(a, 0, n - 1, 100);
	qSortByFirstNum(a, 0, n - 1, 2);
}



int main() {
	int a[MAX_LENGTH];
	int n;
	scanf("%d", &n);
	getInputData(a, n);
	quickSort(a, n);
	printArray(a, n);
	return 0;
}

