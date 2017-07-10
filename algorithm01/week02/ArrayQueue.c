#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100

//定义一个循环队列的数组存储。
typedef struct node{
    int data[MAXSIZE];
    int rear;
    int font;
}que,*pQueue;


pQueue createEmptyQueue(){
    pQueue queue;
    queue =(pQueue)malloc(sizeof(que));
    if(queue){
        queue->font=-1;
        queue->rear=-1;
    }
    return queue;
}

int isQueueFull(pQueue queue){
    return ((queue->rear+1)%MAXSIZE) == (queue->font);
}

int isQueuempty(pQueue queue){
    return queue->font == queue->rear;
}

void addQueue(pQueue queue,int element){
    if(isQueueFull(queue)){
        printf("the queue has been filled,don't allow to put other elememt\n");
    }else{
        queue->rear = (queue->rear+1)%MAXSIZE;
        queue->data[queue->rear]=element;
    }
}

int deleteQueue(pQueue queue){
    if(isQueuempty(queue)){
        printf("the queue is null,don't allow delete element from it");
        return;
    }else{
        queue->font = (queue->font+1)%MAXSIZE;
        return queue->data[queue->font];
    }
}


void toString(pQueue queue){
    int i=queue->font+1;
    while(i<=queue->rear){
        printf("%d ",queue->data[i%MAXSIZE]);
        i++;
    }
}


void main(){
    pQueue queue = createEmptyQueue();
    addQueue(queue,1);
    addQueue(queue,2);
    addQueue(queue,3);
    addQueue(queue,4);
    addQueue(queue,5);
    deleteQueue(queue);
    toString(queue);
}
