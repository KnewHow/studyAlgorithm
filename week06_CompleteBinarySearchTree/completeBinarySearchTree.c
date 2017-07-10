/*
 * completeBinarySearchTree.c
 *
 *  Created on: 2017年5月10日
 *      Author: ygh
 */

/*
 * Algorithm thoughts:
 * 1.We use the array to store the complete binary search tree
 * 2.We will sort the data ascending given in form of a integer array
 * 3.We can get a binary tree sub left nodes and sub right nodes by calculating
 * 4.The root element index in given data array is startIndex + left nodes
 * 5.Call same method for sub left tree and sub right tree recursive
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * Give a tree with n nodes,calculate how many left nodes it has
 * @param n The total nodes the tree has.
 * @return A integer number of the left tree nodes
 */
int calculateLeftTreeLength(int n) {
	int h, x, l;
	h = log2(n + 1);
	x = n + 1 - pow(2, h);
	if (x > pow(2, h - 1)) {
		x = pow(2, h - 1);
	}
	l = pow(2, h - 1) - 1 + x;
	return l;
}

/*
 * A function to put the input array elements to complete
 * the initialized condition is (0,n-1,0,tree[],array[])
 * binary search tree
 * @param aLeft The complete binary search tree data start index in input array
 * @param aLeft The complete binary search tree data end index in input array
 * @param tRoot The index of the complete binary search tree root
 * @param tree A array to store complete binary search tree.
 * @param array A array store the input data and has been sorted ascending
 */
void solve(int aLeft, int aRight, int tRoot, int *tree, int *array) {
	/*
	 * n:the total nodes of the tree
	 * letfLength:the nodes of the sub left nodes
	 * leftRoot:the index of the sub left root in the tree
	 * rightRoot:the index of the sub right root in the tree
	 */
	int n, leftLength, leftRoot, rightRoot;
	/*
	 * Get the all nodes of the tree
	 */
	n = aRight - aLeft + 1;
	if(n==0){
		return;
	}
	leftLength = calculateLeftTreeLength(n);
	tree[tRoot] = array[aLeft + leftLength];
	leftRoot = tRoot * 2 + 1;
	rightRoot = leftRoot + 1;
	solve(aLeft, aLeft + leftLength - 1, leftRoot, tree, array);
	solve(aLeft + leftLength + 1, aRight, rightRoot, tree, array);
}

void getInputData(int length, int *array) {
	int data, i;
	for (i = 0; i < length; i++) {
		scanf("%d", &data);
		array[i] = data;
	}
}

void levelSearch(int *tree, int length) {
	int i;
	for (i = 0; i < length; i++) {
		if (i == length - 1) {
			printf("%d", tree[i]);
		} else {
			printf("%d ", tree[i]);
		}
	}
}

/*
 * A method to compare tow integer number
 */
int compare(const void *a, const void *b) {
	return *(int*) a - *(int*) b;
}

int main() {
	int maxLength = 1000;
	int array[maxLength];
	int tree[maxLength];
	int n;
	scanf("%d", &n);
	getInputData(n, array);
	qsort(array, n, sizeof(int), compare);
	solve(0, n - 1, 0, tree, array);
	levelSearch(tree, n);
	return 0;
}

