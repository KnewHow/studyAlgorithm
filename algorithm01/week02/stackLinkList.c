#include<stdio.h>
#include<stdlib.h>
/*使用链表来模拟堆栈，*/

//定义堆栈的链式存储
typedef struct node{
    int element;
    struct node *next;
}sta,*pStack;

pStack createEmptyStack(){
    pStack stack;
    stack = (pStack)malloc(sizeof(sta));
    if(stack){
        stack->next=NULL;
    }
    return stack;
}

int isEmpty(pStack stack){
    if(stack->next==NULL){
        return 1;
    }else{
        return 0;
    }
}

void push(pStack stack,int element){
    pStack node = (pStack)malloc(sizeof(sta));
    node->element=element;
    node->next=stack->next;
    stack->next=node;
}

int pop(pStack stack){
    int element;
    pStack topHead;
    if(isEmpty(stack)){
        printf("the stack is empty,can not pop");
        return NULL;
    }else{
        topHead = stack->next;
        stack->next = topHead->next;
        element = topHead->element;
        free(topHead);
        return element;
    }
}

void toString(pStack stack){
    pStack top = stack->next;
    printf("toString:");
    while(top!=NULL){
        printf("%d ",top->element);
        top=top->next;
    }
    printf("\n");
}

void main(){
    pStack stack = createEmptyStack();
    push(stack,1);
    push(stack,2);
    push(stack,3);
    push(stack,4);
    toString(stack);
}
