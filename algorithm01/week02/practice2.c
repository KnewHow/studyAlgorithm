#include<stdio.h>
#include<stdlib.h>
/*
Given a constant KKK and a singly linked list LLL, you are supposed to reverse the links of every KKK elements on LLL. For example, given LLL being 1→2→3→4→5→6, if K=3K = 3K=3, then you must output 3→2→1→6→5→4; if K=4K = 4K=4, you must output 4→3→2→1→5→6.
Input Specification:

Each input file contains one test case. For each case, the first line contains the address of the first node, a positive NNN (≤105\le 10^5≤10​5​​) which is the total number of nodes, and a positive KKK (≤N\le N≤N) which is the length of the sublist to be reversed. The address of a node is a 5-digit nonnegative integer, and NULL is represented by -1.

Then NNN lines follow, each describes a node in the format:

Address Data Next

where Address is the position of the node, Data is an integer, and Next is the position of the next node.
Output Specification:

For each case, output the resulting ordered linked list. Each node occupies a line, and is printed in the same format as in the input.
Sample Input:

00100 6 4
00000 4 99999
00100 1 12309
68237 6 -1
33218 3 00000
99999 5 68237
12309 2 33218

Sample Output:

00000 4 33218
33218 3 12309
12309 2 00100
00100 1 99999
99999 5 68237
68237 6 -1
*/


typedef struct node{
    int address;
    int element;
    int nextAddress;
}lis,*pList;

pList createEmptyList(int address,int element,int nextAddress){
    pList node = (pList)malloc(sizeof(lis));
    node->address-address;
    node->element=element;
    node->nextAddress=nextAddress;
    return node;
}

pList* readList(int n){
    pList arr[n];
    int i,address,element,next;
    for(i=0;i<n;i++){
        scanf("%d %d %d",&address,&element,&next);
    }
}

pList findElementByAddress(pList arr[],int length,int address){
    int i;
    for(i=0;i<length;i++){
        if(arr[i]->address==address){
            return arr[i];
        }
    }
}

void sort(int initAddress,pList arr[],int length){
    pList sortedArr[length];
    int i;
    sortedArr[0]=findElementByAddress(arr,length,initAddress);
    for(i=1;i<length;i++){
        sortedArr[i]=findElementByAddress(arr,length,sortedArr[i-1]->nextAddress);
    }

    for(i=0;i<length;i++){
        arr[i]=sortedArr[i];
    }
}

void toString(pList arr[],int length){
    int i;
    for(i=0;i<length;i++){
        printf("%d %d %d\n",arr[i]->address,arr[i]->element,arr[i]->nextAddress);
    }
}

void main(){
    int initAddress,n,k;
    //scanf("%d %d %d",&initAddress,&n,&k);
    initAddress=00100;
    n=6;
    k=4;

    pList arr[n];

    arr[0]=createEmptyList((int)00000,4,(int)33218);
    arr[1]=createEmptyList((int)33218,3,(int)12309);
    arr[2]=createEmptyList((int)12309,2,(int)00100);
    arr[3]=createEmptyList((int)00100,1,(int)99999);
    arr[4]=createEmptyList((int)99999,5,(int)68237);
    arr[5]=createEmptyList((int)68237,6,(int)-1);
    toString(arr,n);
    printf("%d",arr[0]->address);
    sort(initAddress,arr,n);
    toString(arr,n);
}
