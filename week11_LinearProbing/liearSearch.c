/*
 * liearSearch.c
 *
 *  Created on: 2017年5月25日
 *      Author: ygh
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
 * The max size of the table
 */
#define MAX_TABLE_SIZE 100000
/*
 * The type of the element
 */
typedef int elementType;

/*
 * The type of the hash address
 */
typedef int index;

/*
 * The data position is same as the hash address
 */
typedef index position;

/*
 * The status type of the element
 * @param legitimate The element is this position is legitimate
 * @param empty The element is this position is empty
 * @param deleted The element is this position has been deleted
 */
typedef enum {
	legitimate, empty, deleted
} entryType;

/*
 * Define the node of the hash table
 */
typedef struct hashEntry cell;
typedef struct hashEntry {
	/*
	 * A space to store the element
	 */
	elementType data;
	/*
	 * a variable to show the element status
	 */
	entryType info;
};

/*
 * Define a hash table
 */
typedef struct tbNode *hashTable;
typedef struct tbNode {
	/*
	 * The size of the hash table
	 */
	int tableSize;
	/*
	 * A array to store all nodes
	 */
	cell *cells;
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

/*
 * A hash method to find the element position
 */
index hash(elementType key, int tableSize) {
	int a = nextPrime((tableSize + 3) / 2);
	return key % a;
}

/*
 * Create a empty hash table by table size
 */
hashTable creatrTable(int tableSize) {
	hashTable h;
	int i;
	h = (hashTable) malloc(sizeof(struct tbNode));
	h->tableSize = tableSize;
	h->cells = (cell *) malloc(sizeof(cell) * h->tableSize);
	for (i = 0; i < h->tableSize; i++) {
		h->cells[i].info = empty;
	}
	return h;
}

/*
 * Find the element by the key
 */
position find(hashTable h, elementType key) {
	position currentPosition, newPosition, d = 0;
	newPosition = currentPosition = hash(key, h->tableSize);
	/*
	 * If the current position is not empty and the element is not equal key
	 */
	while (h->cells[newPosition].info != empty
			&& h->cells[newPosition].data != key) {
		newPosition = currentPosition + (++d);
		while (newPosition > h->tableSize) {
			newPosition = newPosition % h->tableSize;
		}
		if (d == h->tableSize) {
			return -1;
		}
	}
	/*
	 * Return a position whose data maybe empty or equal key
	 */
	return newPosition;
}

/*
 * Insert a element into hash table
 */
int insert(hashTable h, elementType key) {
	position pos = find(h, key);
	if (pos == -1) {
		printf("the table has been filled");
		return 0;
	}
	if (h->cells[pos].info != legitimate) {
		h->cells[pos].data = key;
		h->cells[pos].info = legitimate;
		return 1;
	} else {
		printf("the key has existed");
		return 0;
	}
}

int delete(hashTable h, elementType key) {
	position pos = find(h, key);
	if (h->cells[pos].info == legitimate) {
		h->cells[pos].info = deleted;
		return 1;
	} else {
		printf("the key is don't set in this set");
		return 0;
	}
}

void toString(hashTable h) {
	int i;
	printf("toString:\n");
	for (i = 0; i < h->tableSize; i++) {
		if (h->cells[i].info == legitimate) {
			printf("index:%d,value:%d\n", i, h->cells[i].data);
		}
	}
}

int main() {
	int tableSize = 13;
	elementType a[] = { 47, 7, 29, 11, 9, 84, 54, 20, 30, 2, 3, 4, 5 };
	int arrSize = 13;
	hashTable h = creatrTable(tableSize);
	int i;
	for (i = 0; i < arrSize; i++) {
		insert(h, a[i]);
	}
//	insert(h, 2);
//	insert(h, 3);
	delete(h, 47);
//	insert(h, 10);
	toString(h);

	printf("just test");
	return 0;
}
