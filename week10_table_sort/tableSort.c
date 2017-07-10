/*
 * tableSort.c
 *
 *  Created on: 2017年5月22日
 *      Author: ygh
 */
#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 100

typedef int contentType;

typedef struct node element;
typedef struct node {
	char key;
	contentType content;
} data[MAX_LENGTH];

typedef struct node1 *ptrTable;
typedef struct node1 {
	data d;
	int table[MAX_LENGTH];
};

/*
 * Create a empty table to store data
 * @param n The length of the table
 * @return ptrTable A point of structure of the table
 */
ptrTable createEmptyTable(int n) {
	ptrTable table = (ptrTable) malloc(sizeof(struct node1));
	int i;
	for (i = 0; i < n; i++) {
		table->table[i] = i;
	}
	return table;
}

/*
 * Insert a data to table
 * @param table A point of structure of the table
 * @param index The index of the element inserted
 * @param key The key of the element inserted
 * @param content The content of the element inserted
 */
void insertData(ptrTable table, int index, char key, contentType content) {
	table->d[index].content = content;
	table->d[index].key = key;
}

/*
 * Implement table sort.
 * Algorithms thoughts:
 * 1.Because the data in <code>data</code> is too large,So we don't swap them
 * 2.We use a table to record the data position,at the first time,the table's value is
 * 	equal the index in the <code>data</code>
 * 3. we sort data by key and record the sorted position by the table
 * 4.When we need to access the table sorted,we just access data[table[i]]
 *
 * @param table A point of structure of the table
 * @param n The length of the table
 */
void tableSort(ptrTable table, int n) {
	int i, j;
	char key;
	int t;
	for (i = 1; i < n; i++) {
		key = table->d[i].key;
		t = table->table[i];
		for (j = i; j > 0 && table->d[table->table[j - 1]].key > key; j--) {
			table->table[j] = table->table[j - 1];
		}
		table->table[j] = t;
	}
}

/*
 * Implement the data physical sort according the table
 * @param table A point of structure of the table
 * @param n The length of the table
 *
 */
void physicalSort(ptrTable table, int n) {
	int i, j;
	int t;
	element temp;
	for (i = 0; i < n; i++) {
		if (table->table[i] != i) {
			temp = table->d[i];
			t = table->table[i];
			table->d[i] = table->d[t];
			table->table[i] = i;
			j = t;
			while (t != i) {
				t = table->table[j];
				if (t == i) {
					break;
				}
				table->d[j] = table->d[t];
				table->table[j] = j;
				j = t;
			}
			table->d[j] = temp;
			table->table[j] = j;
		} else {
			continue;
		}
	}
}

/*
 * Print the table's content to console
 * @param table A point of structure of the table
 * @param n The length of the table
 */
void toStringTale(ptrTable table, int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("key:%c,content:%d\n", table->d[table->table[i]].key,
				table->d[table->table[i]].content);
	}
}

int main() {
	char arr[] = "fdcagbhe";
	int i;
	int n = 8;
	ptrTable table = createEmptyTable(n);
	for (i = 0; i < n; i++) {
		insertData(table, i, arr[i], i);
	}
	tableSort(table, n);
	//toStringTale(table, n);
	physicalSort(table, n);
	toStringTale(table, n);
	return 0;
}
