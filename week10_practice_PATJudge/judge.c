/*
 * judge.c
 *
 *  Created on: 2017年5月24日
 *      Author: ygh
 * Algorithms thoughts:
 * 	Using bucket sort latest significant Digit
 * 	1.sort id
 * 	2.sort perfect solution
 * 	3.sort total scores
 */
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUESTION 5
#define MAX_USER_DIGIT 5
#define MAX_USER 100000

/*
 * The radix of the perfect times,it from 0 to MAX_QUESTION
 */
#define BUCKET_RADIX_PERFECT 6

/*
 * The radix of total score,the value if from 0 to 9
 */
#define BUCKET_RADIX_TOTALSCORE 10
/*
 * The score max digit
 */
#define MAX_DIGIT 6

typedef struct node {
	/*
	 * The id of the user
	 */
	int id;
	/*
	 * A integer array to record the score of
	 * each question
	 */
	int solution[MAX_QUESTION];

	/*
	 * The times about the prefer solution times
	 */
	int perfectCouner;

	/*
	 * The total score
	 */
	int totalScore;

	/*
	 * The rank of the user
	 */
	int rank;

	int showFlag;

} userArr[MAX_USER];

typedef struct node1 *ptrToSet;
typedef struct node1 {
	/*
	 * A array of node to store the user's datas
	 */
	userArr arr;
	/*
	 * A integer to implement table sort
	 */
	int table[MAX_USER];
	/*
	 * A integer array record the whole scores of the questions
	 */
	int question[MAX_QUESTION];
};

/*
 *Create empty set of users and initialize the
 *solution all to -2 standing for question no submit
 *@param n The quantity of the users
 *@param m The quantity of the question
 */
ptrToSet createEmptySet(int n, int k) {
	ptrToSet set = (ptrToSet) malloc(sizeof(struct node1));
	int i, j;
	for (i = 0; i < n; i++) {
		set->table[i] = i;
		for (j = 0; j < k; j++) {
			set->arr[i].solution[j] = -2;
			set->arr[i].perfectCouner = 0;
			set->arr[i].id = i;
			set->arr[i].showFlag = 0;
		}
	}
	return set;
}

/*
 * Insert question total scores into set
 * @param set A point to point the set of users
 * @param m The quantity of the question
 *
 */
void insertQuestionScore(ptrToSet set, int k) {
	int score, i;
	for (i = 0; i < k; i++) {
		scanf("%d", &score);
		set->question[i] = score;
	}
}

/*
 * Insert user's submit to set
 * If the score is not than before,don't update,otherwise update it
 * If the score is -1,update it into 0.
 * If current score is equal question whole score,<code>perfectCounter</code>
 * increase
 * @param set A point to point the set
 * @param m The quantity of the submit

 */
void insertUser(ptrToSet set, int m) {
	/*
	 * @param The id of user,it is a positive integer number
	 * @param The id of question,it is a positive integer number
	 * @param score The score this submit geting
	 */
	int id, qId, score, i;
	for (i = 0; i < m; i++) {
		scanf("%d %d %d", &id, &qId, &score);
		/*
		 * Because the index in array begin from zreo
		 * In order to be compatible
		 */
		id--;
		qId--;
		if (set->arr[id].solution[qId] < score) {
			set->arr[id].solution[qId] = score;
			if (score == set->question[qId]) {
				set->arr[id].perfectCouner++;
			}
		}
	}

}

/*
 * Calculate the total score
 * We don't decrease scores,if the score is negative number
 * we let it to zero and add it.But we need the negative number as
 * a flag when we print the submit result:
 * 		1.The use never submitted,print '-'
 * 		2.The user submit but don't pass compiler get zeor,but we need
 * 			print zero to console
 *		3.If the total score is zero,we don't show them
 */
void calculateTotalSource(ptrToSet set, int n, int k) {
	int i, j;
	int totalScore;
	int scorce;
	for (i = 0; i < n; i++) {
		totalScore = -1;
		for (j = 0; j < k; j++) {
			scorce = set->arr[i].solution[j];
			if (scorce < 0 && totalScore == -1) {
				totalScore = -1;
			} else if (scorce == 0 && totalScore == -1) {
				totalScore = 0;
			} else if (scorce > 0 && totalScore == -1) {
				totalScore = scorce;
			} else if(scorce > 0) {
				totalScore += scorce;
			}
		}
		set->arr[i].totalScore = totalScore;
	}
}

void calculateShowFlag(ptrToSet set, int n) {
	int i;
	for (i = 0; i < n; i++) {
		if (set->arr[i].totalScore > -1) {
			set->arr[i].showFlag = 1;
		} else {
			set->arr[i].showFlag = 0;
			set->arr[i].totalScore = 0;
		}
	}
}

typedef struct node2 *ptrToNode;
typedef struct node2 {
	/*
	 * Store the id of the user
	 */
	int key;

	/*
	 * A point to point next node
	 */
	ptrToNode next;

};

/*
 * Define a data structure for bucket head that
 * store the head point and rear point for the elements
 */
typedef struct headNode {
	ptrToNode head, rear;
};

/*
 * Define a array of headNode to store the all buckets
 */
typedef struct headNode bucket[BUCKET_RADIX_TOTALSCORE];

/*
 * radix sort by perfect times in set.The perfect
 * buckets is from 0 to <code>MAX_QUESTION</code>
 * We sort uses according to perfect times DESC
 * @param set A point to point the set
 * @param n The quantity of users
 */
void radixSortByPerfectTimes(ptrToSet set, int n) {
	int di, i;
	ptrToNode temp, list;
	bucket b;
	/*
	 * Initialize each bucket head and rear into NULL
	 */
	for (i = 0; i < BUCKET_RADIX_PERFECT; i++) {
		b[i].rear = b[i].head = NULL;
	}
	for (i = 0; i < n; i++) {
		di = set->arr[i].perfectCouner;
		temp = (ptrToNode) malloc(sizeof(struct node2));
		temp->key = set->arr[i].id;
		temp->next = NULL;
		if (b[di].head == NULL) {
			b[di].head = b[di].rear = temp;
		} else {
			b[di].rear->next = temp;
			b[di].rear = temp;
		}
	}

	/*
	 * Recover the elements has been deal with,using
	 * the list to point the head
	 */
	list = NULL;
	for (i = 0; i < BUCKET_RADIX_PERFECT; i++) {
		if (b[i].head) {
			b[i].rear->next = list;
			list = b[i].head;
		}
		b[i].head = b[i].rear = NULL;
	}

	/*
	 * Set sorted sequence to table
	 */
	for (i = 0; i < n; i++) {
		temp = list;
		list = list->next;
		set->table[i] = temp->key;
		free(temp);
	}
}

/*
 * Get the digit by the current number and current needed digit
 * @param x The current number
 * @param d The current digit
 * @return The digit needed
 */
int getDigit(int x, int d) {
	int i;
	int di;
	for (i = 0; i < d; i++) {
		di = x % BUCKET_RADIX_TOTALSCORE;
		x = x / BUCKET_RADIX_TOTALSCORE;
	}
	return di;
}

/*
 * Radix sort by total score
 * @param set A point to point the set
 * @param n The quantity of users
 */
void radixSortByTotalScore(ptrToSet set, int n) {
	int di, d, i, j;
	ptrToNode temp, list;
	bucket b;
	/*
	 * Initialize each bucket head and rear into NULL
	 */
	for (i = 0; i < BUCKET_RADIX_TOTALSCORE; i++) {
		b[i].rear = b[i].head = NULL;
	}
	for (d = 1; d <= MAX_DIGIT; d++) {
		for (j = 0; j < n; j++) {
			di = getDigit(set->arr[set->table[j]].totalScore, d);
			temp = (ptrToNode) malloc(sizeof(struct node2));
			temp->key = set->table[j];
			temp->next = NULL;
			if (b[di].head == NULL) {
				b[di].head = b[di].rear = temp;
			} else {
				b[di].rear->next = temp;
				b[di].rear = temp;
			}
		}

		/*
		 * Recover the elements has been deal with,using
		 * the list to point the head
		 */
		list = NULL;
		for (i = 0; i < BUCKET_RADIX_TOTALSCORE; i++) {
			if (b[i].head) {
				b[i].rear->next = list;
				list = b[i].head;
			}
			b[i].head = b[i].rear = NULL;
		}

		/*
		 * Set sorted sequence to table
		 */
		for (i = 0; i < n; i++) {
			temp = list;
			list = list->next;
			set->table[i] = temp->key;
			free(temp);
		}

	}
}

/*
 * Calculate the rank
 */
void calculateRank(ptrToSet set, int n) {
	int rank = 1;
	int totalScore = set->arr[set->table[0]].totalScore;
	int i;
	set->arr[set->table[0]].rank = rank;
	for (i = 1; i < n; i++) {
		if (set->arr[set->table[i]].totalScore == totalScore) {
			set->arr[set->table[i]].rank = rank;
		} else {
			rank = i + 1;
			totalScore = set->arr[set->table[i]].totalScore;
			set->arr[set->table[i]].rank = rank;
		}
	}
}

/*
 * Print the content of the set->table[i]
 */
void toStingTable(ptrToSet set, int n) {
	int i;
	printf("table:");
	for (i = 0; i < n; i++) {
		printf("%d ", set->table[i]);
	}
}

/*
 * Get the digit of a number to print format
 */
int getDiditumber(int num) {
	int counter = 0;
	while (num != 0) {
		num = num / 10;
		counter++;
	}
	return counter;
}

/*
 * Print data to console
 */
void toString(ptrToSet set, int n, int k) {
	int i, j;
	int digit;
	for (i = 0; i < n; i++) {
		if (set->arr[set->table[i]].showFlag == 0) {
			continue;
		}
		printf("%d ", set->arr[set->table[i]].rank);
		digit = getDiditumber(set->arr[set->table[i]].id + 1);
		for (j = 0; j < (MAX_USER_DIGIT - digit); j++) {
			printf("0");
		}
		printf("%d ", set->arr[set->table[i]].id + 1);
		printf("%d ", set->arr[set->table[i]].totalScore);
		for (j = 0; j < k; j++) {
			if (set->arr[set->table[i]].solution[j] ==-2) {
				printf("-");
			} else if(set->arr[set->table[i]].solution[j] ==-1){
				printf("0");
			}else{
				printf("%d",set->arr[set->table[i]].solution[j]);
			}
			if (j == k - 1) {

			} else {

				printf(" ");
			}
		}
		printf("\n");
	}
}

int main() {
	int n, k, m;
	scanf("%d %d %d", &n, &k, &m);
	ptrToSet set = createEmptySet(MAX_USER, k);
	insertQuestionScore(set, k);
	insertUser(set, m);
	n = MAX_USER;
//	toString(set, n, k);
	calculateTotalSource(set, n, k);
	calculateShowFlag(set, n);
	radixSortByPerfectTimes(set, n);
	radixSortByTotalScore(set, n);
	calculateRank(set, n);
	toString(set, n, k);
	return 0;
}
