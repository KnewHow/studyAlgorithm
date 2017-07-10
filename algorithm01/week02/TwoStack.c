#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100

typedef struct node{
    int data[MAXSIZE];
    int top;
    int bottom;
}sta,*pStack;

pStack createEmptyStack(){
    pStack stack;
    stack=(pStack)malloc(sizeof(sta));
    if(stack){
        stack->top=-1;
        stack->bottom=MAXSIZE;
    }
    return stack;
}


int isFull(pStack stack){
    if(stack->bottom-stack->top==1){
        return 1;
    }
    return 0;
}

int isEmpty(pStack stack){
    if(stack->top==-1 && stack->bottom==MAXSIZE){
        return 1;
    }else{
        return 0;
    }
}

void push(pStack stack,int element,int tag){
    if(isFull(stack)){
        printf("the stack is full,don't push %d into stack\n",element);
    }else{
        if(tag==1){
            stack->data[++(stack->top)]=element;
        }else{
            stack->data[--(stack->bottom)]=element;
        }
    }
}

int pop(pStack stack,int tag){
    if(isEmpty(stack)){
        printf("the stack is empty,don't pop element from stack");
    }else{
        if(tag==1){
            return stack->data[(stack->top)--];
        }else{
            return stack->data[(stack->bottom)++];
        }
    }
}

int getStackTopElement(pStack stack,int tag){
    if(tag==1){
        return stack->data[stack->top];
    }else{
        return stack->data[stack->bottom];
    }
}

void toString(pStack stack){
    int top = stack->top;
    int bottom = stack->bottom;
    printf("toString:\n");
    printf("top:");
    while(top>=0){
        printf("%d ",stack->data[top]);
        top--;
    }
    printf("\n");

    printf("bottom:");
    while(bottom<=MAXSIZE-1){
        printf("%d ",stack->data[bottom]);
        bottom++;
    }
    printf("\n");
}

void main(){
    pStack stack = createEmptyStack();
    push(stack,1,1);
    push(stack,2,1);
    push(stack,3,1);
    push(stack,4,2);
    push(stack,5,2);
    push(stack,6,2);
    pop(stack,1);
    pop(stack,2);
    toString(stack);
}
