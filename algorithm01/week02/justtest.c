#include<stdio.h>
#include<stdlib.h>
/*使用链表来模拟堆栈，*/

//定义堆栈的链式存储
typedef struct node3{
    double element;
    struct node *next;
}integerSta,*pIntegerStack;

pIntegerStack createEmptyStack(){
    pIntegerStack stack;
    stack = (pIntegerStack)malloc(sizeof(integerSta));
    if(stack){
        stack->next=NULL;
    }
    return stack;
}

int isEmpty(pIntegerStack stack){
    if(stack->next==NULL){
        return 1;
    }else{
        return 0;
    }
}

void push(pIntegerStack stack,double element){
    pIntegerStack node = (pIntegerStack)malloc(sizeof(sta));
    node->element=element;
    node->next=stack->next;
    stack->next=node;
}

double pop(pIntegerStack stack){
    double element;
    pIntegerStack topHead;
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

void toString(pIntegerStack stack){
    pIntegerStack top = stack->next;
    printf("toString:");
    while(top!=NULL){
        printf("%f ",top->element);
        top=top->next;
    }
    printf("\n");
}

void main(){
    pIntegerStack stack = createEmptyStack();
    push(stack,1);
    push(stack,2);
    push(stack,3);
    push(stack,4);
    toString(stack);
}
