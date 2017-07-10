/*
 * SortwithSwap.c
 *
 *  Created on: 2017年5月25日
 *      Author: ygh
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 100000

typedef int elementType;
/*
 * Define a data structure to store data
 */
typedef struct dataNode *ptrToData;
typedef struct dataNode {
	elementType a[MAX_LENGTH];
	int table[MAX_LENGTH];
};

/*
 * Create empty array point
 */
ptrToData createEmptyData() {
	ptrToData data = (ptrToData) malloc(sizeof(struct dataNode));
	return data;
}

/*
 * Insert element to data and record the index
 * @param data A point to point the data
 * @param n The length of the arrays
 */
void insertElement(ptrToData data, int n) {
	elementType x;
	int i;
	for (i = 0; i < n; i++) {
		scanf("%d", &x);
		data->a[i] = x;
		data->table[x] = i;
	}
}

/*
 *Calculate the swap times.when we access next element by
 *circle, we let the counter increase one. If the circle contain zero,counter decrease one
 *otherwise counter increase one.
 * @param data A point to point the data
 * @param n The length of the arrays
 * @param m The counter of the multiple circle
 * @param s The counter of the single circle
 */
int calculateSwapTimes(ptrToData data, int n) {
	/*
	 * @param key  The index to record the next element by circle
	 * @param j The index the current element
	 */
	int i,key,j;
	/*
	 * record the all swap
	 */
	int counter=0;
	for (i = 0; i < n; i++) {
		if(i==data->table[i]){
			continue;
		}else{
			key = data->table[i];
			counter++;
			data->table[i]=i;
			j=key;
			while(key!=i){
				key=data->table[j];
				counter++;
				data->table[j]=j;
				j = key;
			}
			if(i==0){
				counter--;
			}else{
				counter++;
			}
		}
	}
	return counter;
}

void toString(ptrToData data, int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%d ", data->a[data->table[i]]);
	}
}

int main() {
	ptrToData data = createEmptyData();
	int n,count;
	scanf("%d", &n);
	insertElement(data, n);
	count = calculateSwapTimes(data, n);
	printf("%d",count);
	return 0;
}
