#include<stdio.h>
void printNFor(int n){
    int i;
    for(i=1;i<=n;i++){
        printf("%d ",i);
    }
}

void printNRecursion(int n){
    if(n>0){
        printNRecursion(n-1);
        printf("%d ",n);
    }
}

void main(){
    int i;
    printf("the time using for method");
        //printNRecursion(i);
        //printf("using for implement");
        //printNFor(100000);
        printf("using for recursion");
        printNRecursion(100000);
}
