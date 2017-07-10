#include<stdio.h>
#include<stdlib.h>
#define MAXDATA 65536

typedef int elementType;

typedef struct heapStruct *maxHeap;
struct heapStruct{
    elementType *elementArray;/*定义存储元素的数组*/
    int size;/*堆当前元素的个数*/
    int capacity;/*堆的最大容量*/

};

/*
    create a heap appointed maxsize
    @param maxSize The max size of the max heap
    @return a initialized empty heap.
*/
maxHeap createEmptyHeap(int maxSize){
    maxHeap heap = (maxHeap)malloc(sizeof(struct heapStruct));
    /*把数组元素空间分配出来*/
    heap->elementArray = malloc(sizeof((maxSize+1)*sizeof(elementType)));
    heap->size=0;
    heap->capacity = maxSize;
    /*define the max value as 哨兵, we will make update easy*/
    heap->elementArray[0]=MAXDATA;
    return heap;
}

/*
Judge the heap whether is full.
@param heap The heap need to judge
@return 1 will be returned if the heap is full, otherwise will return 0
*/
int isHeapFull(maxHeap heap){
    return (heap->size==heap->capacity);
}

/*
Judge the heap whether is emppty.
@param heap The heap need to judge
@return 1 will be returned if the heap is empty, otherwise will return 0
*/
int isHeapEmpty(maxHeap heap){
    return (heap->size==0);
}






/*insert element to heap,we will update it if necessary
@param heap The heap exsit
@param element The element need to insert
*/
void insertHeap(maxHeap heap,elementType element){
    int i;
    if(isHeapFull(heap)){
        printf("the heap is full\n");
        return;
    }
    i = ++heap->size;
    heap->elementArray[i]=element;
    for( ; heap->elementArray[i/2]<element;i=i/2){
        heap->elementArray[i]=heap->elementArray[i/2];
    }
    heap->elementArray[i]= element;
}


void toString(maxHeap heap){

}

void main(){
    printf("just test");
    //return 0;
}

