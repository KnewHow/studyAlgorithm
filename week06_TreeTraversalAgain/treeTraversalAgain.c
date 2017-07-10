/*
 * treeTraversalAgain.c
 *
 *  Created on: 2017年5月11日
 *      Author: ygh
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Algorithm thoughts:
 * We can get prefer order traversal result by push operation and get inner  order traversal result by pop operation.
 * Then we can use those two result to get the post order traversal result.
 We know the prefer order traversal result first element is the root element in this binary tree.
 Then we  search this element in inner order result,we use this element as the separation,
 left elements is the sub left elements,right elements is the sub right elements.
 Then we recursive call this method, finally we will get the post order result.
 */

/*===============define a data structure of a stack and some operation======================*/
typedef int elementType;
typedef struct node *pStack;
typedef struct node {
	elementType element;
	struct node * next;
};

pStack createEmptyStack() {
	pStack stack = (pStack) malloc(sizeof(struct node));
	stack->next = NULL;
	return stack;
}

int isStackEmpty(pStack stack) {
	return (stack->next == NULL);
}

void push(pStack stack, elementType elemet) {
	pStack node = (pStack) malloc(sizeof(struct node));
	node->element = elemet;
	node->next = stack->next;
	stack->next = node;
}

elementType pop(pStack stack) {
	if (isStackEmpty(stack)) {
		printf("the stack is empty");
		return -1;
	} else {
		pStack node = stack->next;
		elementType element = node->element;
		stack->next = node->next;
		free(node);
		return element;
	}

}

/*
 * A method to implement transfer prefer order result and inner order result
 * into post order result. We use the integer array to store the elements
 * @param preL The tree or sub tree start index in prefer order result array
 * @param inL The tree or sub tree start index in the inner order result array
 * @param postL The tree or sub tree start index in the post order result array
 * @param n The total nodes in this tree
 * @param pre The integer array to store the prefer order result
 * @param in  The integer array to store the inner order result
 * @param post The integer array to store the post order result
 */
void solve(int preL, int inL, int postL, int n, int *pre, int *in, int *post) {
	int root, i, leftLength, rightLength;
	if (n == 0) {
		return;
	}

	if (n == 1) {
		post[postL] = pre[preL];
		return;
	}

	root = pre[preL];
	post[postL + n - 1] = root;

	for (i = 0; i < n; i++) {
		if (in[inL + i] == root) {
			break;
		}
	}
	leftLength = i;
	rightLength = n - i - 1;
	solve(preL + 1, inL, postL, leftLength, pre, in, post);
	solve(preL + leftLength + 1, inL + leftLength + 1, postL + leftLength,
			rightLength, pre, in, post);

}

/*
 * A method to get input data
 * @param n The total nodes of the tree
 * @param pre A integer array to store the prefer order data,it is null for first.
 * @param pre A integer array to store the inner order data,it is null for first.
 */
void getInputData(int n, int *pre, int *in) {
	int i, data, p = 0, q = 0;
	char str[3];
	pStack stack = createEmptyStack();
	for (i = 0; i < 2 * n; i++) {
		scanf("%s", str);
		if (strcmp(str, "Push") == 0) {
			scanf("%d", &data);
			push(stack, data);
			pre[p] = data;
			p++;
		}

		if (strcmp(str, "Pop") == 0) {
			data = pop(stack);
			in[q] = data;
			q++;
		}
	}

}

/*
 * Print a array
 */
void printArray(int n, int *array) {
	int i;
	for (i = 0; i < n; i++) {
		if (i == n - 1) {
			printf("%d", array[i]);
		} else {
			printf("%d ", array[i]);
		}
	}
}

/*
 * Just a execute method
 */
int main() {
	int n;
	scanf("%d", &n);
	int pre[n];
	int in[n];
	int post[n];
	getInputData(n, pre, in);
	solve(0, 0, 0, n, pre, in, post);
	printArray(n, post);
	return 0;
}
