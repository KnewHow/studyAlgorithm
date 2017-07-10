/*
 * account.c
 *
 *  Created on: 2017年5月27日
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
#define MAX_KEY_LENGTH 10

/*
 * The maximal length of the key
 */
#define MAX_PASS_LENGTH 16

#define REQUEST_DIGIT 6
/*
 * The type of the key
 */
typedef char elementType[MAX_KEY_LENGTH + 1];
/*
 *The type of the password
 */
typedef char passwordType[MAX_PASS_LENGTH + 1];

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
	passwordType password;
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
		h->heads[i].password[0] = '\0';
		h->heads[i].next = NULL;
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
		newCell->next = h->heads[pos].next;
		h->heads[pos].next = newCell;
		return 0;
	} else {
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
			p = p->next;
		}
		printf("\n");
	}
}

void login(hashTable h, elementType key, passwordType password) {
	position p;
	p = find(h, key);
	/*
	 * If not find the key,enable insert
	 */
	if (!p) {
		printf("ERROR: Not Exist\n");
	} else if (p && !strcmp(p->password, password)) {
		printf("Login: OK\n");
	} else {
		printf("ERROR: Wrong PW\n");
	}
}

void apply(hashTable h, elementType key, passwordType password) {

	position p, newCell;
	Index pos;
	p = find(h, key);
	/*
	 * If not find the key,enable insert
	 */
	if (!p) {
		newCell = (position) malloc(sizeof(struct lNode));
		strcpy(newCell->data, key);
		strcpy(newCell->password, password);
		pos = hash(atoi(key + MAX_KEY_LENGTH - REQUEST_DIGIT), h->tableSize);
		/*
		 * Insert the new cell to the first node in right position
		 */
		newCell->next = h->heads[pos].next;
		h->heads[pos].next = newCell;
		printf("New: OK\n");
	} else {
		printf("ERROR: Exist\n");
	}
}

/*
 * Find the max counter and print
 */
void scanAndOutPut(hashTable h, int n) {
	char command;
	elementType account;
	passwordType password;
	int i;
	getchar();
	for (i = 0; i < n; i++) {
		scanf("%c", &command);
		scanf("%s", account);
		scanf("%s", password);
//		printf("%c %s %s\n",command,account,password);
		if (command == 'L') {
			login(h, account, password);
		}
		if (command == 'N') {
			apply(h, account, password);
		}
		getchar();
	}
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
	int n;
	scanf("%d", &n);
	hashTable h = createEmptyTable(n * 2);
	scanAndOutPut(h, n);
	destoryTable(h);
	return 0;
}

