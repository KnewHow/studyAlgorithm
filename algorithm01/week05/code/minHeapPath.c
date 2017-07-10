#include<stdio.h>
#include<stdlib.h>
#define MAXELEMENT 10000
#define MINELEMENT -10001
#define MAXSIZE 1000

typedef int elementType;
/*
define a data constructor of min heap
*/
typedef struct node{
    elementType *data;/*a array to store element*/
    int size;/*the size of the heap*/
    int capacity;/*the capacity of the heap*/
}hea,*pHeap;

/**/
pHeap createEmptyMinHeap(int size){
    pHeap heap = (pHeap)malloc(sizeof(hea));
    heap->data= malloc((size+1)*sizeof(elementType));
    heap->size=0;
    heap->capacity=size;
    heap->data[0]=MINELEMENT;
    return heap;
}

int isMinHeapEmpty(pHeap heap){
    return (heap->size==0);
}

int isMinHeapFull(pHeap heap){
    return (heap->size==heap->capacity);
}

void insertToMinHeap(pHeap heap,elementType element){
    int i;
    if(isMinHeapFull(heap)){
        printf("the heap is full");
        return;
    }

    heap->data[++heap->size]=element;
    i = heap->size;
    for(;element<heap->data[i/2];i=i/2){
        heap->data[i]=heap->data[i/2];
    }
    heap->data[i]=element;
}


void printPath(pHeap heap,int index){
    int i=index;
    while(i>0){
        //printf("%d ",heap->data[i]);

        if(i==1){
            printf("%d",heap->data[i]);
        }else{
            printf("%d ",heap->data[i]);
        }
         i= i/2;
    }
    printf("\n");
}


int main(){
    int n,m,i,ele,index;
    scanf("%d %d",&n,&m);
    pHeap heap = createEmptyMinHeap(n);
    for(i=0;i<n;i++){
        scanf("%d",&ele);
        insertToMinHeap(heap,ele);
    }
    for(i=0;i<m;i++){
        scanf("%d",&index);
        printPath(heap,index);
    }
    return 0;
}
