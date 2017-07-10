/*
 * statistic.c
 *
 *  Created on: 2017年5月26日
 *      Author: ygh
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
 * The max size of the table
 */
#define MAX_TABLE_SIZE 1000000

/*
 * The maximal length of the key
 */
#define MAX_KEY_LENGTH 11

#define REQUEST_DIGIT 5
/*
 * The type of the key
 */
typedef char elementType[MAX_KEY_LENGTH + 1];

/*
 * The type of the index
 */
typedef int Index;

/*
 * Define a list to store the data
 */
typedef struct lNode *ptrToNode;
typedef struct lNode {
	/*
	 * Store the phone number
	 */
	elementType data;
	ptrToNode next;
	/*
	 * record the use phone talk times
	 */
	int counter;
};
typedef ptrToNode position;
typedef ptrToNode list;

/*
 * Define a hash table
 */
typedef struct tbLNode *hashTable;
typedef struct tbLNode {
	int tableSize;
	/*
	 * A array to point the list head
	 */
	list heads;
};

/*
 * Get a prime number greater than N but no more than
 * <code>MAX_TABLE_SIZE</code> and return it
 */
int nextPrime(int n) {
	int i, p = (n % 2) == 0 ? n + 1 : n + 2;
	while (p < MAX_TABLE_SIZE) {
		for (i = sqrt(p); i > 2; i--) {
			if (!(p % i)) {
				break;
			}
		}
		/*
		 * Find the prime number
		 */
		if (i == 2) {
			break;
		} else {
			p = p + 2;
		}
	}
	return p;
}

hashTable createEmptyTable(int tableSize) {
	hashTable h;
	int i;
	h = (hashTable) malloc(sizeof(struct tbLNode));
	/*
	 * Guarantee the table size is a ood number
	 */
	h->tableSize = nextPrime(tableSize);
	h->heads = (list) malloc(sizeof(struct lNode) * h->tableSize);
	/*
	 * Initialize head node
	 */
	for (i = 0; i < h->tableSize; i++) {
		h->heads[i].data[0] = '\0';
		h->heads[i].next = NULL;
		h->heads[i].counter = 0;
	}
	return h;
}

/*
 * Calculate hash value
 */
Index hash(int key, int tableSize) {
	return key % tableSize;
}

position find(hashTable h, elementType key) {
	position p;
	Index pos;
	pos = hash(atoi(key + MAX_KEY_LENGTH - REQUEST_DIGIT), h->tableSize);
	p = h->heads[pos].next;
	while (p && strcmp(p->data, key)) {
		p = p->next;
	}
	return p;
}

int insert(hashTable h, elementType key) {
	position p, newCell;
	Index pos;
	p = find(h, key);
	/*
	 * If not find the key,enable insert
	 */
	if (!p) {
		newCell = (position) malloc(sizeof(struct lNode));
		strcpy(newCell->data, key);
		pos = hash(atoi(key + MAX_KEY_LENGTH - REQUEST_DIGIT), h->tableSize);
		/*
		 * Insert the new cell to the first node in right position
		 */
		newCell->counter = 1;
		newCell->next = h->heads[pos].next;
		h->heads[pos].next = newCell;
		return 0;
	} else {
		p->counter++;
		return 0;
	}
}

void toString(hashTable h) {
	int i;
	position p;
	for (i = 0; i < h->tableSize; i++) {
		p = h->heads[i].next;
		printf("index:%d\n", i);
		while (p) {
			printf("%s %d\n", p->data, p->counter);
			p = p->next;
		}
		printf("\n");
	}
}

/*
 * Find the max counter and print
 */
void scanAndOutPut(hashTable h) {
	int i, maxCnt = 0, pCnt = 0;
	elementType minPhone;
	list ptr;
	minPhone[0] = '\0';
	for (i = 0; i < h->tableSize; i++) {
		ptr = h->heads[i].next;
		while (ptr) {
			if (ptr->counter > maxCnt) {
				maxCnt = ptr->counter;
				strcpy(minPhone, ptr->data);
				pCnt = 1;
			} else if (ptr->counter == maxCnt) {
				if (strcmp(minPhone, ptr->data) > 0) {
					strcpy(minPhone, ptr->data);
				}
				pCnt++;
			}
			ptr = ptr->next;
		}
	}
	printf("%s %d", minPhone, maxCnt);
	if (pCnt > 1) {
		printf(" %d", pCnt);
	}
	printf("\n");
}

void destoryTable(hashTable h) {
	Index i;
	position p, temp;

	for (i = 0; i < h->tableSize; i++) {
		p = h->heads[i].next;
		while (p) {
			temp = p->next;
			free(p);
			p = temp;
		}
	}
	free(h->heads);
	free(h);
}

int main() {
	int n, i;
	elementType key;
	scanf("%d", &n);
	hashTable h = createEmptyTable(n * 2);
	for (i = 0; i < n; i++) {
		scanf("%s", key);
		insert(h, key);
		scanf("%s", key);
		insert(h, key);
	}
	scanAndOutPut(h);
	destoryTable(h);
	return 0;
}
