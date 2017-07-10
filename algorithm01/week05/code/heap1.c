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
    heap->elementArray = (elementType *)malloc((maxSize+1)*sizeof(elementType));
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

elementType deleteMax(maxHeap heap){
    int parent,child;
    elementType maxElement,temp;
    if(isHeapEmpty(heap)){
        printf("the heap has bean empty\n");
        return;
    }
    /*取出最大元素*/
    maxElement = heap->elementArray[1];
    temp=heap->elementArray[heap->size--];
    for(parent=1;parent*2<heap->size;parent=child){
        child = parent*2;
        /*
        child!=heap->size:indicate the heap has a right child
        heap->elementArray[child]<heap->elementArray[child+1]:the value of right greater than the value of left
        the code of IF is to find the index of the bigger value of left child and right child
        */
        if((child!=heap->size)&& heap->elementArray[child]<heap->elementArray[child+1]){
            child++;/*get the right child index*/
        }
        if(temp>=heap->elementArray[child]){
            break;/*temp find a suitable station*/
        }else{
            /*move bigger element to parent station*/
            heap->elementArray[parent]=heap->elementArray[child];
        }
    }

    heap->elementArray[parent]=temp;
    return maxElement;
}


/*
print the heap
@param heap The heap nend to print to the controal
*/
void toString(maxHeap heap){
    maxHeap p = heap;
    printf("toString:");
    int i=1;
    while(i<=p->size){
        printf("%d ",p->elementArray[i]);
        i++;
    }
    printf("\n");
}


/*
    construct the max heap,the algorithem thought is same with delete method
    @param heap The binary tree who want to construct a max heap
    @param p The parent index of the tree
*/
void percDown(maxHeap heap,int p){
    elementType temp=heap->elementArray[p];
    int parent,child;
    for(parent=p;parent*2<=heap->size;parent=child){
        child = parent *2;
        if((child!=heap->size) && heap->elementArray[child]<heap->elementArray[child+1]){
            child++;
        }
        if(temp>=heap->elementArray[child]){
            break;
        }else{
            heap->elementArray[parent]=heap->elementArray[child];
        }
    }
    heap->elementArray[parent]=temp;
}

/*
make a binary tree to be a heap
@param heap The binary tree need to transfer into heap
*/
void buildMaxHeap(maxHeap heap){
    int i;
    /*
    maxHeap heap = createEmptyHeap(10);
    maxHeap heap = createEmptyHeap(10);
    printf("lala,%d\n",length);
    for(i=1;i<=length;i++){
        heap->elementArray[++heap->size]=a[i-1];
    }
    */
    for(i=heap->size/2;i>0;i--){
        percDown(heap,i);
    }

}

/*
void testBuildHeap(){
    int i;
    maxHeap heap2 = createEmptyHeap(10);
    for(i=1;i<=10;i++){
        heap2->elementArray[++heap2->size]=i;
    }
    toString(heap2);
    buildMaxHeap(heap2);
    toString(heap2);
}
*/
int main(){

    int i,arr[10];
    maxHeap heap = createEmptyHeap(30);

    for(i=1;i<=10;i++){
        heap->elementArray[++heap->size]=i;
    }
    printf("build a bianray tree,not heap\t");
    toString(heap);
    buildMaxHeap(heap);
    printf("constructor a binary into a heap\t");
    toString(heap);
    for(;i<=20;i++){
        insertHeap(heap,i);
    }
    printf("test insert method\t");
    toString(heap);
    printf("delete max element%d\n",deleteMax(heap));
    toString(heap);
    printf("delete max element%d\n",deleteMax(heap));
    toString(heap);
    printf("delete max element%d\n",deleteMax(heap));
    toString(heap);
    printf("delete max element%d\n",deleteMax(heap));
    toString(heap);
    //testBuildHeap();
    printf("just test");
    return 0;
}
