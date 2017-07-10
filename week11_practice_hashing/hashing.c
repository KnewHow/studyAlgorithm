/*
 * hashing.c
 *
 *  Created on: 2017年5月26日
 *      Author: ygh
 */
/*
 * squareSearch.c
 *
 *  Created on: 2017年5月26日
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
	int i, p = (n % 2) ? n + 2 : n + 1;
	if (n <= 2) {
		return 2;
	}
	if (n <= 3) {
		return 3;
	}
	while (p <= MAX_TABLE_SIZE) {
		for (i = (int) sqrt(p); i > 2; i--) {
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
	return key % tableSize;
}

/*
 * Create a empty hash table by table size
 */
hashTable creatrTable(int tableSize) {
	hashTable h;
	int i;
	h = (hashTable) malloc(sizeof(struct tbNode));
	h->tableSize = nextPrime(tableSize);
	h->cells = (cell *) malloc(sizeof(cell) * h->tableSize);
	for (i = 0; i < h->tableSize; i++) {
		h->cells[i].info = empty;
	}
	return h;
}

position find(hashTable h, int key) {
	position currentPos, newPos;
	/*
	 * record the conflict times
	 */
	int cNum = 0;
	newPos = currentPos = hash(key, h->tableSize);
	while (h->cells[newPos].info != empty && h->cells[newPos].data != key) {
		/*
		 * odd number conflict
		 */
		if ((++cNum) % 2) {
			newPos = currentPos + (cNum + 1) * (cNum + 1) / 4;
			while (newPos >= h->tableSize) {
				newPos = newPos % (h->tableSize);
			}
			/*
			 *even number conflict
			 */
//		} else {
//			newPos = currentPos - (cNum) * (cNum) / 4;
//			while (newPos < 0) {
//				newPos = newPos + h->tableSize;
//			}
		}
		if (cNum == h->tableSize) {
			return -1;
		}
	}
	return newPos;
}

int insert(hashTable h, elementType key) {
	position pos = find(h, key);
	if (pos == -1) {
		printf("-");
		return -1;
	}
	if (h->cells[pos].info != legitimate) {
		h->cells[pos].info = legitimate;
		printf("%d", pos);
		return pos;
	} else {
		return pos;
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
	int n, m, i;
	elementType key;
	scanf("%d %d", &m, &n);
	hashTable h = creatrTable(m);
	for (i = 0; i < n; i++) {
		scanf("%d", &key);
		insert(h, key);
		if (i != n - 1) {
			printf(" ");
		}
	}
	return 0;
}

