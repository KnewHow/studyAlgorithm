/*
 * shellSort.c
 *
 *  Created on: 2017年5月18日
 *      Author: ygh
 */

#include <stdio.h>
#include <math.h>

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

int getSedgewickStep(int *step, int n) {
	int i, v1, v2, counter = 0;
	i = 0;
	for (i = 0; i < n; i++) {
		v1 = 9 * pow(4, i) - 9 * pow(2, i) + 1;
		if (v1 > 0 && v1 < n) {
			step[counter++] = v1;
		}
		v2 = pow(4, i) - 3 * pow(2, i) + 1;
		if (v2 > 0 && v2 < n) {
			step[counter++] = v2;
		}
		if (v1 > n && v2 > n) {
			break;
		}
	}
	return counter;
}

/*
 * A method to implement bubble sort.If the bubble sort has no any swap
 * operation at one time,indicating the array has been ordered.So we use a
 * tag to make it effective
 *@param a A integer array need to sort
 *@param n The length of the array
 */
void bubble_sort(int a[], int n) {
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
 * Implement base shell sort
 *@param a A integer array need to sort
 *@param n The length of the array
 */
void shell_sort_expand_Sedgewick(elementType a[], int n) {
	int i, j, d, counter, step;
	elementType temp;
	int sequence[] = { 1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, 8929,
			16001, 6289, 64769 };
	counter = 13;
	/*int sequence[n / 2];
	 counter = getSedgewickStep(sequence, n);
	 bubble_sort(sequence, counter);*/
	/*printArray(sequence, counter);
	 return;*/
	for (d = 0; d < counter && sequence[d] < n; d++) {
		step = sequence[d];
		for (i = step; i < n; i++) {
			temp = a[i];
			for (j = i; j >= step && a[j - step] > temp; j -= step) {
				a[j] = a[j - step];
			}
			a[j] = temp;
		}
	}

}

/*
 * Implement base shell sort
 *@param a A integer array need to sort
 *@param n The length of the array
 */
void shell_sort_expand_Sedgewick2(elementType a[], int n) {
	int i, j, d, counter, step;
	elementType temp;
	int sequence[n / 2];
	counter = getSedgewickStep(sequence, n);
	bubble_sort(sequence, counter);
	for (d = 0; d < counter && sequence[d] < n; d++) {
		step = sequence[d];
		for (i = step; i < n; i++) {
			temp = a[i];
			for (j = i; j >= step && a[j - step] > temp; j -= step) {
				a[j] = a[j - step];
			}
			a[j] = temp;
		}
	}

}

/*
 * Implement base shell sort
 *@param a A integer array need to sort
 *@param n The length of the array
 */
void shell_sort_base(elementType a[], int n) {
	int i, j, d;
	elementType temp;
	for (d = n / 2; d > 0; d = d / 2) {
		for (i = d; i < n; i++) {
			temp = a[i];
			for (j = i; j >= d && a[j - d] > temp; j -= d) {
				a[j] = a[j - d];
			}
			a[j] = temp;
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
	shell_sort_expand_Sedgewick2(a, n);
	printArray(a, n);
	return 0;
}

