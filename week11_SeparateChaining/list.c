/*
 * list.c
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
#define MAX_TABLE_SIZE 100000

/*
 * The maximal length of the key
 */
#define MAX_KEY_LENGTH 15

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
	elementType data;
	ptrToNode next;
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
	}
	return h;
}

Index hash(elementType key, int tableSize) {
	unsigned int h = 0;
	while (*key != '\0') {
		h = (h << 5) + *key++;
	}
//	printf("hash:%d",h);
	return h % tableSize;
}

position find(hashTable h, elementType key) {
	position p;
	Index pos;
	pos = hash(key, h->tableSize);
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
		pos = hash(key, h->tableSize);
		/*
		 * Insert the new cell to the first node in right position
		 */
		newCell->next = h->heads[pos].next;
		h->heads[pos].next = newCell;
		return 0;
	} else {
		printf("the key has existed\n");
		return 0;
	}
}

/*
 * Delete a key from hash table
 */
int deleteKey(hashTable h, elementType key) {
	position p, font;
	Index pos;
	p = find(h, key);

	if (p) {
		pos = hash(key, h->tableSize);
		font = &(h->heads[pos]);
		p = font->next;
		while (p && strcmp(p->data, key)) {
			font = p;
			p = font->next;
		}
		font->next = p->next;
//		pos = hash(key, h->tableSize);
//		p = h->heads[pos].next;
//		if (p && !strcmp(p->data, key)) {
//			h->heads[pos].next = p->next;
//		} else {
//			font = p;
//			p = font->next;
//			while (p && strcmp(p->data, key)) {
//				p = p->next;
//			}
//			font->next = p->next;
//		}
		return 1;
	} else {
		printf("the key don't exist\n");
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
			printf("%s\n", p->data);
			p = p->next;
		}
		printf("\n");
	}
}

/*
 * Destroy the hash table
 */
void destroyTable(hashTable h) {
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
	char arr[6][10] = { "abcd", "efgh", "ddsds", "ueiwueiw", "iowieowie",
			"ssdksl" };
	int i;
	int arrSize = 6;
	int tableSize = 5;
	hashTable h = createEmptyTable(tableSize);
	for (i = 0; i < arrSize; i++) {
		insert(h, arr[i]);
	}
	deleteKey(h, "ddsds");
	toString(h);
	destroyTable(h);
	return 0;
}
