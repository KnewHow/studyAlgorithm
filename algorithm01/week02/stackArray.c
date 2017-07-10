#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100

typedef struct node{
    int data[MAXSIZE];
    int top;
}sta,*pStack;

pStack createEmptyStack(){
    pStack stack;
    stack = (pStack)malloc(sizeof(sta));
    if(stack){
        stack->top=-1;
    }
    return stack;
}

int isFull(pStack stack){
    if(stack->top==MAXSIZE-1){
        return 1;
    }else{
        return 0;
    }
}

int isEmpty(pStack stack){
    if(stack->top==-1){
        return 1;
    }else{
        return 0;
    }
}

void push(pStack stack,int element){
    if(isFull(stack)){
        printf("stack has been filled\n");
        return;
    }else{
        stack->data[++(stack->top)]=element;
    }
}

int pop(pStack stack){
    if(isEmpty(stack)){
        printf("the stack is empry");
        return NULL;
    }else{
        return stack->data[(stack->top)--];
    }
}

int getTopElement(pStack stack){
    if(isEmpty(stack)){
        printf("the stack is empry");
        return NULL;
    }else{
        return stack->data[(stack->top)];
    }
}

void toString(pStack stack){
    if(isEmpty(stack)){
        printf("the stack is empry");
        return NULL;
    }else{
        int index= stack->top;
        printf("toString:");
        while(index>=0){
            printf("%d ",stack->data[index]);
            index--;
        }
        printf("\n");
    }
}

void main(){
    pStack stack = createEmptyStack();
    push(stack,1);
    push(stack,2);
    push(stack,3);
    printf("pop:%d\n",pop(stack));
    toString(stack);
}
