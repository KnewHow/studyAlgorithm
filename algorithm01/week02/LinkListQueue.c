#include<stdio.h>
#include<stdlib.h>



//定义一个存在队列元素的链表
typedef struct node1{
    int element;
    struct node1 *next;
}lis,*pList;

//定义队列的链式存储，使用font指向头部，rear指向尾部
typedef struct node2{
    struct node1 *font;
    struct node1 *rear;
}que,*pQueue;


pList createEmptyList(){

    pList list;
    list = (pList)malloc(sizeof(lis));
    if(list){
        list->next=NULL;
    }
    return list;
}
pQueue createEmptyQueue(){

    pQueue queue;
    queue = (pQueue)malloc(sizeof(que));
    if(queue){
        queue->font=NULL;
        queue->rear=NULL;
    }
    return queue;
}

int isQueueEmpty(pQueue queue){
    return (queue->font==NULL);
}

void addQueue(pQueue queue,int element){
    if(isQueueEmpty(queue)){
        pList list = createEmptyList();
        list->element = element;
        queue->font=list;
        queue->rear=list;
    }else{
        pList list = (pList)malloc(sizeof(lis));
        list->element=element;
        list->next = queue->rear->next;
        queue->rear->next = list;
        queue->rear=list;
    }

}

int deleteQueue(pQueue queue){
    if(isQueueEmpty(queue)){
        printf("the queue is empty,don't allow delete element from it");
        return;
    }
    pList node = queue->font;
    int element = node->element;
    if(queue->font==queue->rear){
        queue->font = queue->rear = NULL;
    }else{
        queue->font = queue->font->next;
    }
    free(node);
    return element;
}

void toString(pQueue queue){
    pList p = queue->font;
    while(p!=NULL){
        printf("%d ",p->element);
        p = p->next;
    }
}

void main(){
    pQueue queue = createEmptyQueue();
    addQueue(queue,1);
    addQueue(queue,2);
    addQueue(queue,3);
    addQueue(queue,4);
    addQueue(queue,5);
    addQueue(queue,6);
    deleteQueue(queue);
    toString(queue);
}
